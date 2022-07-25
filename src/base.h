#pragma once

#include "types.h"

#include <sstream>
#include <string>
//#include <multimap>
#include <math.h>

#define elif else if

#define PROJ_NAME "annexatio imperii"
#define ERROR(...) { printf("%s: ", __FUNCTION__); printf(__VA_ARGS__); printf("\n"); exit(1); }
#define NOID 0

struct aabb_s {
 vec2 min, max;
 
 bool in(vec2 pos);
};

struct color_s {
 byte_t r, g, b, a;
 
 //
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

// A system is merely a component in charge of other components.
struct syst_s : public comp_s {
 //hashmap_s<comp_s::id_t, comp_s*> e;
};

struct arg_s {
 string_t text;
 int last;
 
 arg_s();
 arg_s(const char* n_text);
 
 void set(cstring_r n_text);
 string_t til_next(char c = '\0');
};

struct line_s {
 int number;
 vector_t<string_t> args;
 
 int size();
 bool next(cstring_r text, int* index);
 
 static line_s split(cstring_r text, cstring_r delim);
 
 string_t& operator[](size_t i);
};

struct vers_s {
 int major;
 int minor;
 int build;
 
 void print();
};

extern date_s date;
extern tag_s tag_self;
extern vers_s version;

void set_nonblock(int file);
