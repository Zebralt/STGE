#include <iostream>

enum BUFFER_TYPE { NONE, CHUNK, PARAGRAPH, TEXT, ITALIC, STRONG, TITLE1, TITLE2, TITLE3, TITLE4, TITLE5, TITLE6, HYPERLINK, IMAGE, QUOTE, CODESAMPLE, CODEBLOCK };

struct Buffer {
  std::string content;
  BUFFER_TYPE type;

  std::vector<Buffer> children;

  Buffer() {}

  Buffer(std::string str) {
    content = str;
  }

  void addChild(Buffer b) {
    children.push_back(b);
  }

  std::string toHtml() {

    std::string subcontent = "";

    for (auto& child : children) {
      subcontent += child.toHtml();
    }

    switch(type) {
    case NONE: default: return "";
    case CHUNK: case TEXT: return content;
    case PARAGRAPH: return subcontent;
    case ITALIC: return markup(subcontent, "i");
    case STRONG: return markup(subcontent, "b");
    case IMAGE: return markup("","");
    case HYPERLINK: return markup("","");
    }

  }

};

std::string sublines(std::vector<std::string>& content, std::size_t pos, std::size_t offset) {
  if (pos >= content.size()) return "";

  std::string result;

  for (int i = pos; i < pos + offset && i < content.size(); i++) {

  }

  return result;

}

bool onlyThoseChars(const std::string& str, const std::string& tc) {
  for (auto& c : str) {
    bool match = false;
    for (auto& tt : tc) {
      if (c == tt) {
        match = true;
      }
    }
    if (!match) {
      return false;
    }
  }
  return true;
}

bool onlyThoseChars(const std::string& str, const std::vector<char>& tc) {
  std::string ccc;
  for (auto& c : tc) {
    ccc += c;
  }
  return onlyThoseChars(str, ccc);
}

bool onlySpaces(const std::string& str) {
  return onlyThisChar(str," ");
}

Buffer bufferize(const std::string& text) {
  Buffer root;

  // 1. separate by empty lines
  // 2. separate titles and paragraphs
  // 3. separate code blocks and paragraphs

  // 4. Figure paragraphs content

  std::vector<std::string> lines = into_lines(text);

  bool in = false;

  Buffer head;

  int start = 0, i = 0, length = 0;
  for (auto& line : lines) {

    if (in && (!line.length() || onlySpaces(line))) {
      // close the current buffer and open a new one
      root.addChild(Buffer(sublines(lines, start, length), BUFFER_TYPE::CHUNK));

      start = i;
      length = 0;
      in = false;
    }

    i++; length++;
  }

  return root;
}

std::string convertToHtml(const std::string& text) {

  Buffer main = bufferize(text);
  return main.toHtml();

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

std::string markupSingle(const std::string& tag, const std::string& metadata) {
  return "<" + tag + (metadata != "" ? " " + metadata + " " : "") + "\\/>\n";
}

std::string markup(const std::string& content, const std::string& markup, const std::string& metadata) {
  //LL(markup << ":" << content);
//  if (markup == "codeblock") markup = "p";
//  metadata += " class=\"codeblock\"";
  return "<" + markup + (metadata != "" ? " " + metadata + " " : "") + ">\n" + (content) + "\n</" + markup + ">\n";
}

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
