
#include "parser.hpp"
#include "textgame.h"
#include "scene.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <dirent.h>

/// PARSER FLAGS

#define GET_ACTION(str) (str == "MOVE"?MOVE:str == "ATTACK"?ATTACK:IDLE)

stringList parseDir(std::string dirpath) {
    stringList filelist;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirpath.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (!strcmp(".", ent->d_name)) continue;
            if (!strcmp("..", ent->d_name)) continue;
            filelist.push_back(std::string(ent->d_name));
        }
        closedir (dir);
    } else {
    }
    return filelist;
}

typedef unsigned int uint;

stringList getWords(std::string text) {
    stringList content;
    std::stringstream tstream(text);
    std::string word;
    while(tstream >> word) {
        content.push_back(word);
    }
    return content;
}

stringList split(std::string text, char delimiter) {
    stringList content;
    std::stringstream tstream(text);
    std::string word;
    while(std::getline(tstream,word,delimiter)) {
        content.push_back(word);
    }
    return content;
}

stringList parseFile(std::string filepath) {
    std::ifstream myfile;
    myfile.open(filepath.c_str(), std::ifstream::in);
    stringList content;
    std::string line;
    while (!myfile.eof() && std::getline(myfile,line)) {
        content.push_back(line);
    }
    myfile.close();
    return content;
}

void removeChar(std::string& str, char a) {
    std::string output; output.reserve(str.length());
    for (uint i=0; i<str.length(); i++) {
        if (str[i] != a) output += str[i];
    }
    str = output;
}

bool containsChar(std::string str, std::string c) {
    for (uint i=0;i<c.size();i++) {
        for (uint j=0;j<str.size();j++) {
            if (str[j] == c[i]) return true;
        }
    }
    return false;
}

Scene* createScene(std::string filepath) {
    Scene* sc = new Scene(filepath);
    return sc;
}
