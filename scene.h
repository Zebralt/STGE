#ifndef SCENE_H
#define SCENE_H

#include "global.h"

#include <string>

class Requirement {
public:
    Requirement(std::string);
    Requirement(bool* b);

    bool ok();
private:
    std::string text;
    bool* requir;

};

typedef struct Triplet {
    std::string name;
    std::string dest;
    std::string requirement;

    friend std::ostream& operator<<(std::ostream& o, const Triplet& r);

} Choice, Dependency, Action;

class Scene {
public:
    Scene();
    Scene(stringList&);
    Scene(std::string filepath);

    // load scene from file
    void loadFromFile(std::string);

    // load scene from text
    void fromText(stringList&);


    void setText(std::string t) {
        text = t;
    }

    // cout text and choices
    void display();

    // pick a choice
    Choice& pick(uint i);
    Choice& pick(std::string str);
    void addChoice(Choice);
    void addDependency(Dependency);
    void addAction(Action);
    Choice next;

    std::string getText() { return text; }
    std::string getTitle() { return title; }
    std::string getAuthor() { return author; }
    std::vector<Choice>& getChoices() { return choices; }

    void setNext(std::string);

private:
    std::vector<Dependency> dependencies;
    std::vector<Choice> choices;
    std::vector<Action> actions;
    std::string text;
    std::string title;
    std::string author;
};

#endif // SCENE_H
