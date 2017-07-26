#include "textgame.h"
#include "parser.hpp"
#include "scene.h"

#include <algorithm>

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

bool TextGame::load(const std::string& filepath) {
    stringList elems = split(filepath, '.');
    if (elems.size() && elems[elems.size()-1] == GAME_FILE_EXTENSION) {
        return loadFromGameFile(filepath);
    }
    else {
        return loadFromDirectory(filepath);
    }
}

bool TextGame::loadFromDirectory(const std::string& filepath) {
    stringList filelist = parseDir(filepath);
    if (std::find(filelist.begin(), filelist.end(), "config.ini") == filelist.end()) {
        println("Error : couldn't find " << filepath << "/config.ini");
        return false;
    }

    std::map<std::string, stringList> files;
    for (uint i=0;i<filelist.size();i++) {
        println("Parsing " << filepath << "/" << filelist[i]);
        files[filelist[i]] = parseFile(filepath+"/"+filelist[i]);
    }
    bool b = (files.find("config.ini") != files.end() ? parseConfigurationFile(files["config.ini"]) : false);

    /// SPECIAL CASES
    ///

    {
        stringList unneededFiles = {"readme.md", "config.ini", "values.bo"};
        fileMap::const_iterator it;
        for (uint i=0;i < unneededFiles.size(); i++) {
            it = files.find(unneededFiles[i]);
            if (it != files.end()) files.erase(it);
        }
    }

    b &= parseScenes(files);
    return b;
}

bool TextGame::parseConfigurationFile(const stringList& content) {
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
                if      (line == "General") status =  PARSING_GENERAL;
                else if (line == "Values") status =   PARSING_VALUES;
                else if (line == "Items") status =    PARSING_ITEMS;
                else status = 0;
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
//                self.title = QString(val.c_str());
                self.title = val;
            }
            else if (name == "author") {
//                self.author = QString(val.c_str());
                  self.author = val;
            }
            else if (name == "version") {
//                self.version = QString(val.c_str());
                  self.version = val;
            }
            else if (name == "date") {
//                self.date = QString(val.c_str());
                  self.date =  val;
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
bool TextGame::parseScenes(const fileMap& files) {
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

bool TextGame::loadFromGameFile(const std::string& filepath) {
//    filepath = "";
    return false;
}

bool TextGame::loadSavedGame(const std::string& filepath) {
//    filepath = "";

    return false;
}

bool TextGame::saveGame(const std::string& path) {
//    path = "";

    return false;
}

bool TextGame::save() {
    // figure a filepath to save
    std::string filepath = "";
    return saveGame(filepath);
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

void TextGame::proceed(const std::string& choice) {
    println(choice); {
        Choice& c = current_scene->pick(choice);
        println(c);
        current_scene = scenes[c.dest];
    }
    update();
}

void TextGame::proceed(const int& choice) {
  Choice& c = current_scene->pick(choice);
  println(c);
  current_scene = scenes[c.dest];

  update();
}

void TextGame::update() {
    if (!current_scene) {
        std::cout << "scene is empty ..." << std::endl;
        title = "NO_SCENE";
        previous_scene_text = scene_text;
        scene_text = "There is no scene here";
        choices.clear();
        status = DEAD_END;
    }
    else {
//        title = QString(current_scene->getTitle().c_str());
        scene_title = current_scene->getTitle();
//        emit sceneTitleChanged();
        previous_scene_text = scene_text;
//        emit previousSceneChanged();
        scene_text = current_scene->getText();
//        emit sceneChanged();
        choices.clear();
        std::vector<Choice>& scene_choices = current_scene->getChoices();
        for (uint i=0; i<scene_choices.size(); i++) {
//            choices << QString(scene_choices[i].name.c_str());
            choices.push_back(scene_choices[i].name);
        }
        if (!scene_choices.size()) {
            choices.push_back(" > ");
        }
//        emit choicesChanged();

    }
    scene_counter++;
}

void TextGame::initialize() {
    if (scenes.find(first_scene) != scenes.end()) current_scene = scenes[first_scene];
    if (current_scene) {
//        println(current_scene->getText());
        scene_text = current_scene->getText();
//        scene_text = QString(current_scene->getText().c_str());
        std::vector<Choice>& scene_choices = current_scene->getChoices();
        for (uint i=0; i<scene_choices.size(); i++) {
//            choices << QString(scene_choices[i].name.c_str());
            choices.push_back(scene_choices[i].name);
        }
        scene_counter = 0;
//        scene_title = QString(current_scene->getTitle().c_str());
        scene_title = current_scene->getTitle();
        println("initializing game");
    }
//    emit choicesChanged();
//    emit sceneChanged();
//    emit previousSceneChanged();
//    emit sceneTitleChanged();
}

//void TextGame::generateDoc() {
//    std::ofstream
//    LOGDOC(ss, "#" << title);
//    LOG("by " << author);
//    LOG("v" << version << " released on " << date);
//    LOG("")
//}

void TextGame::display() {
  println("title=" << title);
  if (author.length()) println("by " << author);
  println("version=" << version << "; " << date);
  println("This game contains " << scenes.size() << " scenes.");
}

void TextGame::scene() {
  println("scene=" << scene_title);
  println("\n" << scene_text);
  println("\n");
  int i = 0;
  for (auto& a : choices) {
    println(i++ << ". " << a);
  }
}

bool TextGame::running() {
  return status == RUNNING;
}
