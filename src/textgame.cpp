#include "textgame.h"
#include "parser.hpp"
#include "scene.h"

/// CONSTRUCTOR

TextGame::TextGame()
{
    if (load("D:/textgame_data")) {
        println("Game was successfully loaded");
    }
    else {
        println("Couldn't load game");
    }
}

///
/// INTERNAL FUNCTIONS
///

bool TextGame::load(std::string filepath) {
    stringList elems = split(filepath, '.');
    if (elems.size() && elems[elems.size()-1] == GAME_FILE_EXTENSION) {
        return loadFromGameFile(filepath);
    }
    else {
        return loadFromDirectory(filepath);
    }
}

bool TextGame::loadFromDirectory(std::string filepath) {
    stringList filelist = parseDir(filepath);
    if (std::find(filelist.begin(), filelist.end(), "config.ini") == filelist.end()) {
        println("Error : couldn't find " << filepath << "/config.ini");
        return false;
    }
    std::map<std::string, stringList> file;
    for (uint i=0;i<filelist.size();i++) {
        println("Parsing " << filepath << "/" << filelist[i]);
        file[filelist[i]] = parseFile(filepath+"/"+filelist[i]);
    }
    bool b = (file.find("config.ini") != file.end() ? parseConfigurationFile(file["config.ini"]) : false);

    /// SPECIAL CASES
    ///

    {
        stringList unneededFiles = {"readme.md", "config.ini", "values.bo"};
        fileMap::const_iterator it;
        for (uint i=0;i < unneededFiles.size(); i++) {
            it = file.find(unneededFiles[i]);
            if (it != file.end()) file.erase(it);
        }
    }

    b &= parseScenes(file);
    return b;
}

bool TextGame::parseConfigurationFile(stringList& content) {
    int status = 0;
    for (uint i = 0; i<content.size(); i++) {
        std::string line = content[i];
        if (line.empty()) continue;
        removeChar(line,'\n');
        removeChar(line,'\t');
        switch(line[0]) {
            case '[':
                removeChar(line, '[');
                removeChar(line, ']');
                if (line == "General") status = PARSING_GENERAL;
                else if (line == "Values") status = PARSING_VALUES;
                else if (line == "Items") status = PARSING_ITEMS;
                continue;
                break;
            case '#':
            case ';':
            case ' ':
                continue;
                break;
            default:break;
        }
        ///////////////////////////////////////////
        if (status == PARSING_GENERAL) {
            stringList elems = split(line, '=');
            std::string name = elems[0];
            std::string val = elems[1];
            if (name == "title") {
                self.title = QString(val.c_str());
            }
            else if (name == "author") {
                self.author = QString(val.c_str());
            }
            else if (name == "version") {
                self.version = QString(val.c_str());
            }
            else if (name == "date") {
                self.date = QString(val.c_str());
            }
            else if (name == "first") {
                self.first_scene = val;
            }
        }
        ///////////////////////////////////////////
        if (status == PARSING_VALUES) {
            stringList elems = split(line, ' ');
            std::string name = elems[0];
            std::string value;
            if (elems.size() > 1) value = elems[1];
            values[name] = (elems.size() > 1 ? (value == "0" ? 0 : 1) : 0);
        }
        ///////////////////////////////////////////
        ///
        ///////////////////////////////////////////
        if (status == PARSING_ITEMS) {
            stringList elems = split(line, '=');
            std::string id = elems[0];
            std::string name = elems[1];
            items[id] = name;
        }
    }

    return true;
}
bool TextGame::parseScenes(fileMap& files) {
    for (fileMap::const_iterator it = files.begin(); it != files.end(); ++it) {
        std::string file_name = it->first;
        stringList file_content = it->second;
        stringList elems = split(file_name, '.');
        if (!elems.size() || elems[elems.size()-1] != SCENE_FILE_EXTENSION) {
            println("couldn't load file " << file_name);
            continue;
        }
        scenes[file_name] = new Scene(file_content);
    }
    return true;
}

bool TextGame::loadFromGameFile(std::string filepath) {
    filepath = "";
    return false;
}

bool TextGame::in_loadSavedGame(std::string filepath) {
    filepath = "";

    return false;
}

bool TextGame::in_saveGame(std::string path) {
    path = "";

    return false;
}

bool TextGame::in_save() {
    // figure a filepath to save
    std::string filepath = "";
    return in_saveGame(filepath);
}

/*int input() {
    int i;
    std::cin >> i;
    return i;
}

void TextGame::run() {
    Scene* current_dialog = scenes[first_scene];
    while (current_dialog) {
        current_dialog->display();
        int chosen = input();
        if (chosen < 0) {
            current_dialog = NULL;
            std::cout << "negative input." << std::endl;
        }
        else current_dialog = scenes[current_dialog->pick(chosen)];
        std::cout << "next=" << std::hex << current_dialog << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
    }
}*/

///
/// EXPOSED FUNCTIONS
///

void TextGame::loadSavedGame(QString filepath) {
    in_loadSavedGame(filepath.toStdString());
}

void TextGame::saveGame(QString filepath) {
    in_saveGame(filepath.toStdString());
}

void TextGame::save() {
    in_save();
}

/*
 *
void Game::run() {
    Scene* current_dialog = scenes[first_scene];
    while (current_dialog) {
        current_dialog->display();
        int chosen = input();
        if (chosen < 0) {
            current_dialog = NULL;
            std::cout << "negative input." << std::endl;
        }
        else current_dialog = scenes[current_dialog->pick(chosen)];
        std::cout << "next=" << std::hex << current_dialog << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
    }
}*/

void TextGame::proceed(QString choice) {
    println(choice.toStdString()); {
        Choice c = current_scene->pick(choice.toStdString());
        println(c);
        current_scene = scenes[c.dest];
    }
    update();
}

void TextGame::update() {
    if (!current_scene) {
        std::cout << "scene is empty ..." << std::endl;
        title = "NO_SCENE";
        previous_scene_text = scene_text;
        scene_text = "There is no scene here";
        choices.clear();
    }
    else {
        title = QString(current_scene->getTitle().c_str());
        emit sceneTitleChanged();
        std::cout << "title:" << title.toStdString() << std::endl;
        previous_scene_text = scene_text;
        emit previousSceneChanged();
        scene_text = QString(current_scene->getText().c_str());
        emit sceneChanged();
        choices.clear();
        std::vector<Choice>& scene_choices = current_scene->getChoices();
        for (uint i=0; i<scene_choices.size(); i++) {
            choices << QString(scene_choices[i].name.c_str());
        }
        if (!scene_choices.size()) {
           choices << "Next";
        }
        emit choicesChanged();

    }
    scene_counter++;
}

void TextGame::initialize() {
    current_scene = scenes[first_scene];
    if (current_scene) {
        println(current_scene->getText());
        scene_text = QString(current_scene->getText().c_str());
        std::vector<Choice>& scene_choices = current_scene->getChoices();
        for (uint i=0; i<scene_choices.size(); i++) {
            choices << QString(scene_choices[i].name.c_str());
        }
        scene_counter = 0;
        scene_title = QString(current_scene->getTitle().c_str());
        println("initializing game");
    }
    emit choicesChanged();
    emit sceneChanged();
    emit previousSceneChanged();
    emit sceneTitleChanged();
}
