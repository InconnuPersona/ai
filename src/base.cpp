#include "base.h"

#include <cstring>

#ifdef _WIN32
 
#else
 #include <fcntl.h>
#endif

bool aabb_s::in(vec2 pos) {
 return
   pos.x > min.x && pos.y > min.x &&
   pos.x < max.x && pos.y < max.x;
}

arg_s::arg_s() {
 set("");
}

arg_s::arg_s(const char* n_text) {
 set(n_text);
}

void arg_s::set(cstring_t& n_text) {
 text = n_text;
 last = 0;
}

string_t arg_s::til_next(char c) {
 size_t i, last;
 
 if (text.empty()) {
  return "";
 }
 
 last = this->last;
 
 for (i = last; i < text.length(); i++) {
  if (text[i] == c) {
   break;
  }
 }
 
 if (i + 1 < text.length()) {
  this->last = i + 1;
 }
 else {
  this->last = text.length();
 }
 
 return text.substr(last, i - last);
}

date_s date_s::operator++(int) {
 day++;
 
 if (day > 30) {
  day -= 30;
  month++;
 }
 
 if (month > 12) {
  month -= 12;
  year++;
 }
 
 return *this;
}

date_s::operator string_t() {
 std::stringstream stream;
 
 stream << "cycle " << year << " lune " << month << " day " << day;
 
 return stream.str();
}

bool line_s::next(cstring_t& text, int* index) {
 int i;
 int prev;
 
 if (!args.empty()) {
  args.clear();
 }
 
 i = prev = *index;
 
 while (true) {
  if (!text[i]) {
   if (prev != i) {
	args.push_back(text.substr(prev, i - prev));
   }
   
   *index = i;
   
   return false;
  }
  else if (text[i] == '\n' || text[i] == '\r') {
   if (prev != i) {
	args.push_back(text.substr(prev, i - prev));
	
	prev = i;
   }
   
   // isspace skips all whitespace characters
   while (isspace(text[i])) {
	i++;
   }
   
   if (text[i] == '#') {
	goto comment; // Woo-wee, comment blocks.
   }
   
   break;
  }
  else if (isspace(text[i])) {
   if (prev != i) {
	args.push_back(text.substr(prev, i - prev));
	
	prev = i;
   }
   
   prev++;
  }
  else if (text[i] == '#') {
   
  comment:
   while (text[i] && (text[i] != '\n' && text[i] != '\r')) {
	i++;
   }
   
   while (isspace(text[i])) {
	i++;
   }
   
   if (text[i] == '#') {
	goto comment; // We go again.
   }
   
   prev = i;
   
   if (size() > 0) {
    break;
   }
  }
  
  i++;
 }

 
 *index = i;
 
 return true;
}

int line_s::size() {
 return (int) args.size();
}

line_s line_s::split(cstring_t& text, cstring_t& delim) {
 line_s line;
 char* token;
 
 char* c_text;
 
 c_text = new char[text.length() + 1];
 
 std::strncpy(c_text, text.c_str(), text.length());
 
 c_text[text.length()] = '\0';
 
 while ((token = std::strtok(c_text, delim.c_str())) != NULL) {
  line.args.push_back(token);
 }
 
 return line;
}

string_t& line_s::operator[](size_t i) {
 if (i < 0 || i >= args.size()) {
  ERROR("line %i; invalid index %i", number, (int) i);
 }
 
 return args[i];
}

void vers_s::print() {
 printf(PROJ_NAME " version %i.%i-%x\n", major, minor, build);
}

void set_nonblock(int file) {
#ifdef _WIN32
 int noblock = 1;
 
 //ioctl(file, FIONBIO, &noblock);
#else
 int flags;
 
 flags = fcntl(file, F_GETFL, 0);
 
 fcntl(file, F_SETFL, flags | O_NONBLOCK);
#endif
}
