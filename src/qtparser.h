#ifndef QTPARSER_H
#define QTPARSER_H

#include <vector>
#include <string>

#include "global.h"

#include <QString>

namespace qrc {

  QString qstr_parseFile(const std::string& path);
  stringList parseDir(const std::string& qrcPath);
  std::string figurePath(const std::string& file);


}

#endif // QTPARSER_H
