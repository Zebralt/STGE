#include "mk.h"

using namespace mk;

int mk_main(int argc, char** argv) {

  MarkdownToHtml mth;

  if (argc == 2) { // only interpreting the file .md
    std::string path(argv[1]);
    std::string sa = mth.mdToHtml(parseFile(path));
    PRINT(sa);
  }
  else if (argc > 3) {
    // ./a.out file.md -style style.css
    // ./a.out file.md -s style.css
    // ./a.out -s style.css file.md
    // ./a.out -style style.css file.md

    std::vector<std::string> strs;
    for (int i = 1; i < argc; i++) strs.push_back(std::string(argv[i]));
    std::string path;
    std::string stylepath;
    for (int i = 0;i < strs.size(); i++) {
      if (strs[i] == "-style" || strs[i] == "-s" && i < strs.size() - 1) {
        stylepath = strs[i+1];
        if (i == 0) path = strs[2];
        else path = strs[0];
        break;
      }
    }

    if (stylepath != "" && path != "") {
      LL("css=" << stylepath);
      LL("md=" << path);
      LL("");
      std::map<std::string, std::vector<std::string>> styles = parseStyleFile(stylepath);
      mth.setStyles(styles);
      LL("----------------------");
      std::string output = mth.mdToHtml(parseFile(path));
      LL("----------------------");
      PRINT(output);
    }
    else {
      LL("No the right parameters.");
    }
  }
  return 0;
}
