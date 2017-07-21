#include "scene.h"
#include "parser.hpp"

Scene::Scene() {

}

Scene::Scene(const stringList& sl) {
    fromText(sl);
}

Scene::Scene(const std::string& fp) {
    loadFromFile(fp);
}

void Scene::loadFromFile(const std::string& fp) {
    stringList content = parseFile(fp);
    fromText(content);
}

void Scene::display() {
    println(text << std::endl);
    if (!choices.size()) println("Enter any key to continue.");
    else
    for (uint i=0;i<choices.size();i++) {
        println(i+1 << ": " << choices[i]);
    }
}

Choice& Scene::pick(uint i) {
    i--;
    // si aucun choix particulier
    if (!choices.size()) {
        return next;
    }
    if (i < 0 || i >= choices.size()) return next;
    else {
        return choices[i];
    }
}

Choice& Scene::pick(const std::string& str) {
    for (uint i=0; i<choices.size(); i++) {
        if (choices[i].name == str) {
            return choices[i];
        }
    }
    return next;
}

void Scene::setNext(const std::string& path) {
    next.dest = path;
}

//void Scene::add(std::string tx, Scene* nex, Requirement* r = nullptr) {
//    choices.push_back(tx);
//    choices.push_back(nex);
//}


void Scene::addChoice(const Choice& c) {
    println(title << "->new choice : " << c.name);
    Choice d(c);
    choices.push_back(d);
}

void Scene::addDependency(const Dependency& den) {
    println(title << "->new dep : " << den.name);
    Dependency pen(den);
    dependencies.push_back(pen);
}

void Scene::addAction(const Action& a) {

    Action act(a);

    actions.push_back(act);
}

Requirement decodeRequirement(std::string str) {
    /*/stringList words = getWords(str);
    stringList elems = getWords(str);
    if (words[0] == "if") {
        elems = split(line, ':');
        std::string bool_name = getWords(elems[0])[1];
        // create requirement
        elems = getWords(elems[1]);
    }
    else if (words[0] == "have") {
        elems = split(line, ':');
        std::string item_name = getWords(elems[0])[1];
        // create requirement
        elems = getWords(elems[1]);
    }
    else if (words[0] == "is") {
        elems = split(line, ':');
        std::string state_name = getWords(elems[0])[1];
        // create requirement
        elems = getWords(elems[1]);
    }*/
}

void Scene::fromText(const stringList& content) {
    int status = 0;
    for (int i = 0; i<content.size(); i++) {
        std::string line = content[i];
        if (line.empty()) continue;
        removeChar(line,'\n');
        removeChar(line,'\t');
        switch(line[0]) {
            case '[':
                removeChar(line, '[');
                removeChar(line, ']');
                if      (line == "General") status =      PARSING_GENERAL;
                else if (line == "Content") status =      PARSING_CONTENT;
                else if (line == "Dependencies") status = PARSING_DEPENDENCIES;
                else if (line == "Choices") status =      PARSING_CHOICES;
                else if (line == "Actions") status =      PARSING_ACTIONS;
                else status = 0;
                continue;
                break;
            case '#':
            case ';':
                continue;
                break;
            default:break;
        }

        if (status == PARSING_GENERAL) {
            stringList elems = split(line, '=');
            std::string name = elems[0];
            std::string val = elems[1];
            if (name == "title") {
                this->title = val;
            }
            else if (name == "author") {
                this->author = val;
            }
        }

        if (status == PARSING_CONTENT) {
            this->text += line + '\n';
        }

        if (status == PARSING_DEPENDENCIES) {
            if (containsChar(line, ":")) {
                stringList elems = split(line, ':');
                std::string requirement = elems[0];
                stringList rval = getWords(elems[1]);
                std::string dest = rval[0];
                addDependency(Dependency("", dest, requirement));
            }
            else {
                addDependency(Dependency("", line, ""));
            }
        }

        if (status == PARSING_CHOICES) {
            // that works
            if (containsChar(line, ":=")) {
                stringList elems = split(line, ':');
                std::string requirement = elems[0];
                stringList rval = getWords(elems[1]);
                std::string choice_name = rval[0];
                std::string filepath = rval[1];
                addChoice(Choice(choice_name, filepath, requirement));
            }

            else {
                stringList elems = getWords(line);
                if (elems.size() == 1) {
                    // Next
                    setNext(elems[0]);
                }
                else if (elems.size() > 1) {
                    std::string name = elems[0];
                    std::string filename = elems[1];
                    addChoice(Choice(name, filename, ""));
                }
            }
        }

        if (status == PARSING_ACTIONS) {
            if (containsChar(line, ":")) {
                stringList elems = split(line, ':');
                std::string requirement = elems[0];
                std::string dest = elems[1];
                addAction(Action("", dest, requirement));
            }
            else {
                addAction(Action("", line, ""));
            }
        }
    }
}


std::ostream& operator<<(std::ostream& o, const Triplet& r) {
    o << "[name=" << r.name << ", dest=" << r.dest << ", requirement=" << r.requirement << "]";
    return o;
}
