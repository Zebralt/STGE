#ifndef GLOBAL_H
#define GLOBAL_H

#define PARSING_GENERAL         1
#define PARSING_CONTENT         2
#define PARSING_DEPENDENCIES    3
#define PARSING_CHOICES         4
#define PARSING_ACTIONS         5
#define PARSING_RESOURCES       6

/// CONFIG FILES

#define PARSING_VALUES          15
#define PARSING_ITEMS           16
#define PARSING_SCENE_CONFIG    17

#define GAME_FILE_EXTENSION     "tg"
#define SCENE_FILE_EXTENSION    "sc"

#include <iostream>

#define println(sstr) std::cout << sstr << std::endl

/// TYPEDEFS
///
///

#include <vector>
#include <string>
#include <map>

typedef unsigned int uint;

typedef std::vector<std::string> stringList;
typedef std::map<std::string, stringList> fileMap;
#endif // GLOBAL_H
