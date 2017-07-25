#ifndef TEXTGAME_H
#define TEXTGAME_H

#include "global.h"

struct Sample {
    std::string str;
    int i;
    float f;
};

struct Item {
    std::string identifier;
    std::string name;

};

class Scene;
class TextGameController;

class TextGame {

public:
    TextGame();

    ///
    /// INTERNAL FUNCTIONS
    ///

    /// \brief load from GAME_FILE_EXTENSION file
    bool loadFromGameFile(const std::string& filepath);

    /// \brief redirect to either above or below function
    bool load(const std::string& filepath);

    // load a directory and search for adequate files in it
    bool loadFromDirectory(const std::string& path);

    // parse cfg file content
    bool parseConfigurationFile(const stringList& content);

    // parse Scene files
    bool parseScenes(const fileMap& files);

    bool loadSavedGame(const std::string& path);
    bool saveGame(const std::string& path);

    bool save();

    void proceed(const std::string& choice);

    void initialize();

    void update();

private:
    std::string title;
    std::string version;
    std::string date;
    std::string author;
    std::string first_scene;

    std::string scene_text;
    std::string scene_title;
    std::string previous_scene_text;
    std::vector<std::string> choices;
    int scene_counter;

    Scene* current_scene = nullptr;

    std::map<std::string, Scene*> scenes;
    std::map<std::string, bool> values; // all values ?
    std::map<std::string, std::string> items; // all items ?

    struct GameData {
        std::vector<Item> inventory; // player inventory
        std::map<std::string, Sample> stats; // player stats
        std::map<std::string, bool> values;
    } data;

    TextGame& self = *this;

    friend class TextGameController;
};


#endif // TEXTGAME_H
