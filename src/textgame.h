#ifndef TEXTGAME_H
#define TEXTGAME_H

#include "global.h"

#define DEAD_END 0
#define RUNNING  1

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

    void proceed(const int& choice);

    void initialize();

    void update();

    void display();

    void scene();

    bool running();

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

    short status = RUNNING;

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

/////////////
///
///
///
///

class Value {
  std::string name;
  std::string type;

  union {
    char* str;
    int i;
    float f;
  } data;
};

class Item {
  int id;
  std::string name;
  std::string code;

  std::vector<Value> stats;
};

class DataCategory {
  int id;
  std::string name;

  std::vector<std::string, Value> items;

};

class MockTextGame {
public:
  MockTextGame();

  bool loadGame(std::string);
  bool loadPlayerData(std::string);
  bool savePlayerData(std::string);

  bool proceed(std::string);
  bool proceed(int);

  void update();

private:

  /// GAME DATA

  std::vector<std::string, Item> item_registry;
  std::vector<std::string, Value> game_values;

  std::vector<std::string, ItemModel> item_models;

  /// PLAYER DATA
  ///
  std::vector<std::string, DataCategory> categories;

  std::vector<Item, int> inventory;

  std::vector<Slot, Item> equipment;

  std::vector<std::string, Value> player_values;

};


#endif // TEXTGAME_H
