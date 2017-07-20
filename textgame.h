#ifndef TEXTGAME_H
#define TEXTGAME_H

#include "global.h"

#include <QOBject>

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

class TextGame : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString author MEMBER author)
    Q_PROPERTY(QString date MEMBER date)
    Q_PROPERTY(QString version MEMBER version)
    Q_PROPERTY(QString scene_title MEMBER scene_title NOTIFY sceneTitleChanged)
    Q_PROPERTY(QString scene MEMBER scene_text NOTIFY sceneChanged)
    Q_PROPERTY(QString previous_scene MEMBER previous_scene_text NOTIFY previousSceneChanged)
    Q_PROPERTY(QStringList choices MEMBER choices NOTIFY choicesChanged)
    Q_PROPERTY(int count MEMBER scene_counter)
public:
    TextGame();

    ///
    /// INTERNAL FUNCTIONS
    ///

    // load from GAME_FILE_EXTENSION file
    bool loadFromGameFile(std::string filepath);

    // redirect to either above or below function
    bool load(std::string filepath);

    // load a directory and search for adequate files in it
    bool loadFromDirectory(std::string path);

    // parse cfg file content
    bool parseConfigurationFile(stringList& content);

    // parse Scene files
    bool parseScenes(fileMap& files);

    bool in_loadSavedGame(std::string path);
    bool in_saveGame(std::string path);

    bool in_save();

    ///
    /// EXPOSED FUNCTIONS
    ///

    Q_INVOKABLE void loadSavedGame(QString path);
    Q_INVOKABLE void saveGame(QString path);
    Q_INVOKABLE void save();

    Q_INVOKABLE void proceed(QString choice);

    Q_INVOKABLE void initialize();

    void update();

signals:
    void sceneChanged();
    void previousSceneChanged();
    void sceneTitleChanged();
    void choicesChanged();

private:
    QString title;
    QString version;
    QString date;
    QString author;
    std::string first_scene;

    QString scene_text;
    QString scene_title;
    QString previous_scene_text;
    QStringList choices;
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
};

#endif // TEXTGAME_H
