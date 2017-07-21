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

    Triplet() {

    }

    Triplet(std::string name, std::string dest, std::string requirement)
    : name(name), dest(dest), requirement(requirement) {
    }

    Triplet(const Triplet& tri) {
        name = tri.name;
        dest = tri.dest;
        requirement = tri.requirement;
    }

    Triplet& operator=(const Triplet& tri) {
        if (this != &tri) {
            this->dest = tri.dest;
            this->name = tri.name;
            this->requirement = tri.requirement;
        }
        return *this;
    }

} Choice, Dependency, Action;

class Scene {
public:
    Scene();
    Scene(const stringList& content);
    Scene(const std::string& filepath);

    // load scene from file
    void loadFromFile(const std::string& path);

    // load scene from text
    void fromText(const stringList&);


    void setText(const std::string& t) {
        text = t;
    }

    // cout text and choices
    void display();

    // pick a choice
    Choice& pick(uint i);
    Choice& pick(const std::string& str);
    void addChoice(const Choice& ch);
    void addDependency(const Dependency& de);
    void addAction(const Action& ac);

    /// default choice
    Choice next;

    std::string getText() { return text; }
    std::string getTitle() { return title; }
    std::string getAuthor() { return author; }
    std::vector<Choice>& getChoices() { return choices; }

    void setNext(const std::string& );

private:
    std::vector<Dependency> dependencies;
    std::vector<Choice> choices;
    std::vector<Action> actions;
    std::string text;
    std::string title;
    std::string author;
};

#endif // SCENE_H
