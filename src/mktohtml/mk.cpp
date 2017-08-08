#include "mk.h"

namespace mk {

MarkdownToHtml::MarkdownToHtml() {

}

MarkdownToHtml::~MarkdownToHtml() {

}

std::vector<std::string> parseFile(const std::string& filepath) {
  std::ifstream myfile;
  myfile.open(filepath.c_str(), std::ifstream::in);
  std::vector<std::string> content;
  std::string line;
  if (myfile.is_open()) {
      while (!myfile.eof() && std::getline(myfile,line)) {
        content.push_back(line);
      }
      myfile.close();
  }
  else {
      LL("Couldn't open file at " << filepath);
  }
  return content;
}

std::string replacematch(const std::string& str, const std::string& aa) {
  std::string in = str;
  std::string out = str;
  std::regex greg("("+aa+")");
  std::smatch s;
  while(std::regex_search(out,s,greg)) {
    for (auto& x : s) {LL(x); break;}
    out = s.suffix().str();
    LL(":" << out);
  }
  in = std::regex_replace(in,greg,"-BBB-");
  return in;
}

///// check for *, **, _ and so on
//std::string filterContent(const std::string& str) {
//  std::string output = str;

//  std::regex _it_regex("_(.*?)_");
//  std::regex it_regex("\\*(.*?)\\*");
//  std::regex bold_regex("\\*\\*(.*?)\\*\\*");
//  std::regex _bold_regex("__(.*?)__");

//  std::string bold_str =  markup("$1","b");
//  std::string it_str =  markup("$1","i");

//  output = std::regex_replace(output,bold_regex,bold_str);
//  output = std::regex_replace(output, it_regex, it_str);
//  output = std::regex_replace(output, _bold_regex, bold_str);
//  output = std::regex_replace(output, _it_regex,it_str);

//  // code

//  std::regex code_regex("`(.*?)`");

//  output = std::regex_replace(output, code_regex, markup("$1","code"));

//  // images

//  std::regex img_regex("!\\[(.*?)\\]\\((.*?)\\)");

//  output = std::regex_replace(output, img_regex, markupSingle("img","src='$2' alt=\"$1\""));

//  // hyper links

////  std::regex link_regex("\\[(.*?)\\]\\((.*?)\\)");

////  output = std::regex_replace(output, link_regex, markup("$1","a","href='$2'"));

////  LL(output << " <- " << str);

//  return output;
//}

std::string markupSingle(const std::string& tag, const std::string& metadata) {
  return "<" + tag + (metadata != "" ? " " + metadata + " " : "") + "\\/>\n";
}

std::string markup(const std::string& content, const std::string& markup, const std::string& metadata) {
  //LL(markup << ":" << content);
//  if (markup == "codeblock") markup = "p";
//  metadata += " class=\"codeblock\"";
  return "<" + markup + (metadata != "" ? " " + metadata + " " : "") + ">\n" + (content) + "\n</" + markup + ">\n";
}

std::vector<std::string> into_lines(const std::string& str) {
    std::stringstream ss(str);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(ss,line,'\n')) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> split(const std::string& line, const char& delimiter) {
  std::vector<std::string> elements;
  std::stringstream ss(line);
  std::string word;
  while (std::getline(ss,word,delimiter)) {
    elements.push_back(word);
  }
  return elements;
}

#define end_register if (buffer.length()) output += markup((buffer_container != "codeblock"?filterContent(buffer):buffer),buffer_container, STYLE(*recognizeStyle(buffer_container))), buffer = "", buffer_container = "";
#define close_list if (list_buffer.length()) output += markup(list_buffer,list_type,STYLE(*recognizeStyle(list_type))), list_buffer = "", list_it = 0, list_type = "";
#define is_number(a) (a>=48 && a <= 57) // a : char
#define a_z(a) (a>=93 && a<93+26)
#define A_Z(a) (a>=65 && a<65+26)

std::string MarkdownToHtml::mdToHtml(const std::string& text) {
  std::vector<std::string> lines = into_lines(text);
  return mdToHtml(lines);
}

int is_olist_element(const std::string& line) {
  std::vector<std::string> elems = split(line, '.');
  if (!elems.size()) return 0;
  for (auto& c : elems[0]) if (!is_number(c)) return 0;
  return std::stoi(elems[0]);
}

char is_title_bar(const std::string& line) {
  char c = '=';
  unsigned int it = 0;
  for (unsigned int i = 0; i < line.length() && c == line[i]; i++, it++);
  if (it > 2 && it == line.length()) {
    return c;
  }

  c = '-';
  it = 0;
  for (unsigned int i = 0; i < line.length() && c == line[i]; i++, it++);
  if (it > 2 && it == line.length()) {
    return c;
  }
  return false;
}

int has_tab(const std::string& str) {
  int i = 0;
  for (;i<str.length() && str[i] == ' ';i++);
//  std::cout << "str= " << str << ":i=" << i << std::endl;
  return (i >= 3) ? i : 0;

}

std::string MarkdownToHtml::mdToHtml(const std::vector<std::string>& lines) {
  std::string output;
  std::string buffer;
  std::string buffer_container;
  std::string list_buffer;
  std::string list_type;
  int list_it = 0;
  std::string previous_line = "";

  for (auto& line : lines) {
    if (line.length()) {
      if (line[0] == '#') {
        end_register;
        // Title

        // figuring which h
        unsigned int rank = 1;
        while(line[rank] == '#' && rank < line.length()) rank++;
        std::string content; // = substr(line - '###"...'')
        content = line.substr(rank, line.length() - rank);

        if (rank > 6) rank = 6;
        std::string str = "h" + std::to_string(rank);
        output += markup(content, str, STYLE(*recognizeStyle(str)));
//        std::cout << "title:" << line << std::endl;
      }

      // title
      // ================= // or -----------------------
      else if (char c = is_title_bar(line)) {
        buffer_container = "";
        buffer = "";

        // hr
        if (c == '-' && line.length() == 3) {
          output += "<hr/>";
//          std::cout << "line:" << line << std::endl;
        }
        else {
          std::string str = (c == '=' ? "h1" : c == '-' ? "h2" : "h3");
          output += markup(previous_line, str, STYLE(*recognizeStyle(str)));
//          std::cout << "title:" << previous_line << std::endl;
        }

      }

      else if (int rank = has_tab(line)) {
//        std::cout  << "rank=" << std::to_string(rank) << ":" << line << std::endl;
//        int rank = 4; //(has_tab(line) ? 4 : line[0] == '\t' ? 1 : 0);
        //while (rank < line.length() && (line[rank] == '\t' || line[rank] == ' ')) rank++;
        if (rank < line.length() - 1 && line[rank+1] == '*') {
          // nested list
          buffer += "NESTED LIST : " + line + "<br/>\n";
        }
        else if (rank >= 4) {
          // Code
          if (buffer_container != "codeblock") {
            end_register;
            buffer_container = "codeblock";
          }
          for (int i=0; i<rank; i++) buffer += "&emsp;";
          buffer += line + "<br/>\n";
//          std::cout << "codeblock:" << line << std::endl;
        }
      }

      else if (line[0] == '-' || line[0] == '*') {
        end_register;
        // Unordered list
        if (list_type != "ul") {
          close_list;
          list_type = "ul";
          LL("changed to ul");
        }
        list_buffer += markup(line.substr(1,line.length()-1),"li", STYLE(styles.li));
//        std::cout << "uli:" << line << std::endl;
      }

      else if (int rank = is_olist_element(line)) {
        end_register;
        // Ordered list
        if (list_type != "ol") {
          close_list;
          list_type = "ol";
        }
        if (rank != list_it + 1) {
          LL("false order: got " << rank << ", expected " << list_it + 1);
          close_list;
          list_it = rank - 1;

        }
        list_buffer += markup(line.substr(2,line.length()-1),"li", STYLE(styles.li));
        list_it++;
//        std::cout << "oli:" << line << std::endl;
      }

      // quote
      else if (line[0] == '>') {
        close_list;
        if (buffer_container != "quote") {
          end_register;
          buffer_container = "quote";
        }
        buffer += line.substr(1,line.length() - 1) + "\n";
//        std::cout << "quote:" << buffer_container << ":" << line << std::endl;
      }

      else {
        // Plain text
        close_list;
        if (buffer_container == "codeblock" && !has_tab(line)) {
//          std::cout << "what ? " << has_tab(line) << std::endl;
          end_register;
        }
        if (buffer_container == "") buffer_container = "p";
        buffer += line + (buffer_container == "codeblock" ? "<br/>" : "") + "\n";
//        std::cout << "plain text:" << buffer_container << ":" << line << "(" << line.length() << ")" << std::endl;
      }
    }
    else {
      // Empty line
//      if (buffer_container.length() && buffer_container != "codeblock") {
//        end_register;
//      }
//      else if (buffer_container == "codeblock") {
//        buffer += "<br/>\n";
//      }
      end_register;
      close_list;
    }
    previous_line = line;
  }
  if (buffer.length()) end_register;

  output = markup("<meta charset='UTF-8'/>", "head") + output;

  if (!STYLE_STYLE) {
    output += "\n" + markup(rewriteStyles(), "style");
  }

  return markup(output,"html", STYLE(styles.html));
}

/// This will simply parse as following :
/// [item]->[style]
/// CSS Sample:
///
/// [item] {
///   color: #AAAEEE
///   font: Courier
/// }
///
/// [style] = all the properties concatenated in one string:
/// [property]; [property]; ...

#define SYNTAX_ERROR LL("Syntax error at line " << it)

std::map<std::string, std::vector<std::string>> parseStyleFile(const std::string& filepath) {
  LL("LOADING STYLES");
  LL("----------------------");
  std::map<std::string, std::vector<std::string>> styles;
  std::string elem = "";
  bool open = false;
  std::vector<std::string> lines = parseFile(filepath);
  int it = 0;
  for (auto& line : lines) {
    std::vector<std::string> elems = split(line, ' ');
    if (elems.size() > 1 && elems[elems.size() - 1] == "{") {
      // open bracket
      if (open) {
        SYNTAX_ERROR;
        return styles;
      }
      open = true;
      elem = elems[0];
    }
    else if (elems.size() && elems[0] == "}") {
      // close bracket
      if (!open) {
        SYNTAX_ERROR;
        return styles;
      }
      open = false;
      if (elem != "") {
        elem = "";
      }
    }

    else {
      if (open && elem != "") {
        std::string property = "";
        for (auto& e : elems) {
          property += e;
        }
        std::vector<std::string> ee = split(property, '\t');
        property = "";
        for (auto& e : ee) {
          property += e;
        }
        styles[elem].push_back(property);
      }
    }

    it++;
 }

  for (auto& style : styles) {
    LL(style.first << ":");
    for (auto& s : style.second) {
      LL("\t" << s);
    }
  }


  return styles;
}

std::string agglutinate(const std::vector<std::string>& strs) {
  std::string re = "";
  for (auto& str : strs) {
    re += str + "; ";
  }
  return re;
}

std::string MarkdownToHtml::fromFile(const std::string& path) {
    std::string result = mdToHtml(parseFile(path));
    LL("hello ??? >>> " << result);
    return result;
}

std::string MarkdownToHtml::fromFile(const std::string& path, const std::string &stylepath) {
    std::map<std::string, std::vector<std::string>> styles = parseStyleFile(stylepath);
    setStyles(styles);
    return mdToHtml(parseFile(path));
}

std::string MarkdownToHtml::convertToHtml(const std::string& str) {
    std::string result = mdToHtml(str);

    return result;
}

std::string MarkdownToHtml::convertToHtml(const std::string& str, const std::string& stylefile) {
    std::map<std::string, std::vector<std::string>> styles = parseStyleFile(stylefile);
    setStyles(styles);
    std::string result = mdToHtml(str);

    return result;
}

void MarkdownToHtml::setStyles(const std::map<std::string, std::vector<std::string>>& styles) {
  std::map<std::string, std::string> styles_agglu;
  for (const auto& pair : styles) {
    styles_agglu[pair.first] = agglutinate(pair.second);
  }
  setStyles(styles_agglu);
}

void MarkdownToHtml::setStyles(const std::map<std::string, std::string>& styles) {
  for (auto& style : styles) {
    setStyle(style.first, style.second);
  }
}

void MarkdownToHtml::setStyle(const std::string& tag, const std::string& style) {
  std::string* p_str =  recognizeStyle(tag);
  if (p_str) {
    *p_str = style;
  }
}

std::string* MarkdownToHtml::recognizeStyle(const std::string& name) {
  if (name == "html") return &styles.html;
  if (name == "body") return &styles.body;

  if (name == "h1") return &styles.h1;
  if (name == "h2") return &styles.h2;
  if (name == "h3") return &styles.h3;
  if (name == "h4") return &styles.h4;
  if (name == "h5") return &styles.h5;
  if (name == "h6") return &styles.h6;

  if (name == "p") return &styles.p;
  if (name == "a") return &styles.a;
  if (name == "bold") return &styles.bold;
  if (name == "italic") return &styles.italic;
  if (name == "codeblock") return &styles.codeblock;
  if (name == "code") return &styles.code;
  if (name == "hr") return &styles.hr;
  if (name == "quote") return &styles.quote;
  if (name == "ul") return &styles.ul;
  if (name == "ol") return &styles.ol;
  if (name == "li") return &styles.li;

  if  (name =="img") return &styles.img;

  return nullptr;
}

std::string MarkdownToHtml::filterContent(const std::string& str) {
  std::string output = str;

  std::regex _it_regex("_(.*?)_");
  std::regex it_regex("\\*(.*?)\\*");
  std::regex bold_regex("\\*\\*(.*?)\\*\\*");
  std::regex _bold_regex("__(.*?)__");

  std::string bold_str =  markup("$1","b","style=" + STYLE(styles.bold));
  std::string it_str =  markup("$1","i","style=" + STYLE(styles.italic));

  output = std::regex_replace(output,bold_regex,bold_str);
  output = std::regex_replace(output, it_regex, it_str);
  output = std::regex_replace(output, _bold_regex, bold_str);
  output = std::regex_replace(output, _it_regex,it_str);

  // code

  std::regex code_regex("\\u0060(.*?)\\u0060");

  output = std::regex_replace(output, code_regex, markup("$1","code",STYLE(styles.code)));

    // images

    std::regex img_regex("!\\[(.*?)\\]\\((.*?)\\)");

    output = std::regex_replace(output, img_regex, markupSingle("img","src='$2' alt=\"$1\"" + STYLE(styles.img)));

  // hyper links

  std::regex link_regex("\\[(.*?)\\]\\((.*?)\\)");

  output = std::regex_replace(output, link_regex, markup("$1","a","href='$2'" + STYLE(styles.a)));

//  LL(output << " <- " << str);

  return output;
}

std::string WRITEDOWN(std::string p, std::string str) { return p  + " {\n\t" + str + "\n}\n"; }

#define WRITEUP(p, str) result += (str != "" ? WRITEDOWN(p, str) : "")

std::string MarkdownToHtml::rewriteStyles() {
  std::string result = "";

  WRITEUP("html", styles.html);
  WRITEUP("body", styles.body);

  WRITEUP("h1",styles.h1);
  WRITEUP("h2",styles.h2);
  WRITEUP("h3",styles.h3);
  WRITEUP("h4",styles.h4);
  WRITEUP("h5",styles.h5);
  WRITEUP("h6",styles.h6);

  WRITEUP("p",styles.p);
  WRITEUP("a",styles.a);
  WRITEUP("b",styles.bold);
  WRITEUP("i",styles.italic);
  WRITEUP("codeblock",styles.codeblock);
  WRITEUP("code",styles.code);
  WRITEUP("hr",styles.hr);
  WRITEUP("quote",styles.quote);
  WRITEUP("ul",styles.ul);
  WRITEUP("ol",styles.ol);
  WRITEUP("li",styles.li);

  WRITEUP("img", styles.img);

  return result;
}

} // mk;
