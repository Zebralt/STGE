#include "qtparser.h"

#include <QFileInfo>
#include <QFile>
#include <QTextStream>

namespace qrc {

QString qstr_parseFile(const std::string& path) {
  QString tump;
  QFile file(QString(path.c_str()));
  if (file.open(QFile::ReadOnly)) {
    QTextStream qts(&file);
    tump = qts.readAll();
    file.close();
  }
  else {
    std::cout << "didn't open : " << path << std::endl;
    std::cout << "Error opening file: " << strerror(errno) << std::endl;
  }
  return tump;
}

#define CAPUT(sstr) println(sstr.toStdString())

std::string figurePath(const std::string& file) {
  QFileInfo fi(QString(file.c_str()));

  CAPUT(fi.absoluteFilePath());
  CAPUT(fi.absolutePath());

}

stringList parseDir(const std::string& qrcPath) {

}

} // qrc
