#ifndef parser_hpp__
#define parser_hpp__

#include "global.h"

#include <vector>
#include <string>
#include <map>

stringList parseDir(std::string);

bool parse(std::string);

/* separe une string selon un delimiteur */
stringList split(std::string,char);
/* lit un fichier texte ligne par ligne et stocke chaque ligne as a std::string in a std::vector */
stringList parseFile(std::string);
/* split the string with the ' ' delimiter */
stringList getWords(std::string);
/* supprime un char de la std::string */
void removeChar(std::string&,char);

bool containsChar(std::string str, std::string c);

class Scene;
Scene* createScene(std::string);


#endif // parser_hpp__
