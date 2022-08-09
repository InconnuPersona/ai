#pragma once

#include "types.h"

#include <math.h>

#include <sstream>
#include <string>

#define elif else if

#define PROJ_NAME "annexatio imperii"
#define ERROR(...) { printf("%s: ", __FUNCTION__); printf(__VA_ARGS__); printf("\n"); exit(1); }
#define NOID 0

#undef API
#define API extern

struct aabb_s {
 vec2 min, max;
 
 bool in(vec2 pos);
};

struct color_s {
 byte_t r, g, b, a;
};

struct date_s {
 int year;
 short month;
 short day;
 
 date_s operator++(int);
 
 operator string_t();
};

// Component/gameobj_s
struct comp_s {
 typedef int id_t;
 
 id_t id;
 
};

// Entity
struct ent_s {
 typedef int id_t;
 
 
 id_t id;
 
 // The population/government class.
 int rank;
};

struct arg_s {
 string_t text;
 int last;
 
 arg_s();
 arg_s(const char* n_text);
 
 void set(cstring_t& n_text);
 string_t til_next(char c = '\0');
};

struct line_s {
 int number;
 vector_t<string_t> args;
 
 int size();
 bool next(cstring_t& text, int* index);
 
 static line_s split(cstring_t& text, cstring_t& delim);
 
 string_t& operator[](size_t i);
};

struct vers_s {
 int major;
 int minor;
 int build;
 
 void print();
};

extern date_s date;
extern vers_s version;

void set_nonblock(int file);

namespace eco {
}

namespace gfx {
}

namespace map {
}
