#ifndef markdown_handler_h
#define markdown_handler_h

#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <string>

#define MKVERBOSE 0
#define STYLE_STYLE 0
#define TAB_LENGTH 4 // tab <=> TAB_LENGTH spaces

#define PRINT(sstr) std::cout << sstr << std::endl
#define LL(sstr) if (MKVERBOSE) PRINT(sstr)
#define SS(x) dynamic_cast< std::ostringstream & >((std::ostringstream().seekp(0, std::ios_base::cur) << x)).str()
#define STYLE(str) ( str != "" && STYLE_STYLE ? " style='" + str + "'" : "")

namespace mk {

std::string markup(const std::string& content, const std::string& markup, const std::string& metadata = "");
std::string markupSingle(const std::string& tag, const std::string& metadata = "");
std::string replacematch(const std::string&, const std::string&);
std::vector<std::string> split(const std::string& s, const char&);
std::map<std::string, std::vector<std::string>> parseStyleFile(const std::string&);
std::vector<std::string> parseFile(const std::string& filepath);
std::string filterContent(const std::string& str);

class MarkdownToHtml {
public:

    MarkdownToHtml();
    ~MarkdownToHtml();

    std::string fromFile(const std::string& path);
    std::string fromFile(const std::string& path, const std::string& stylepath);
    std::string convertToHtml(const std::string& str);
    std::string convertToHtml(const std::string& str, const std::string& stylefilepath);

    std::string mdToHtml(const std::string&);
    std::string mdToHtml(const std::vector<std::string>& lines);

    void test() {
        std::cout << "testtesttesttest" << std::endl;
    }

    std::string filterContent(const std::string& str);

    void setStyles(const std::map<std::string, std::vector<std::string>>& styles);
    void setStyles(const std::map<std::string, std::string>& styles);
    void setStyle(const std::string& tag, const std::string& style);

    std::string rewriteStyles();

    struct Style {
      std::string html;
      std::string body = "width:800px; margin: 0 auto";

      std::string h1 = "";
      std::string h2;
      std::string h3;
      std::string h4;
      std::string h5;
      std::string h6;

      std::string p;
      std::string a;
      std::string bold;
      std::string italic;
      std::string codeblock = "display: block; padding:5px; background-color: #eeeeee; border-radius: 20; border; 1px solid black; font-family: Courier New; font-size: 13px";
      std::string code = "border-radius: 10; background-color: lightgray; font-family: Courier; font-size: 14px;";
      std::string hr;
      std::string quote = "padding:5; padding-left:15; background-color: lightgray; font-family: sans-serif";
      std::string ul;
      std::string ol;
      std::string li;

      std::string img = "margin: 0 auto; display: block";

    } styles;

    std::string* recognizeStyle(const std::string& name);
};

} // mk

#endif // markdown_handler_h
