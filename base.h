#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SZ sizeof(char)
#define KILOBYTE_SZ (1024 * BYTE_SZ)
#define MEGABYTE_SZ (1024 * KILOBYTE_SZ)

#ifndef NULL
#define NULL ((void*) 0)
#endif

#define MAKE_LINK(Structure) struct Structure##_s* next
#define LINK_NEXT(New, Old) { New->next = Old; Old = New; }
#define NEW(Structure) (Structure*) calloc(1, sizeof(Structure))

#ifdef GAME_DEBUG
#define ENABLE_DEBUG 2
#else 
#define ENABLE_DEBUG 0
#endif

#define clog(Level, ...) { printf(__VA_ARGS__); printf("\n"); }
#define cerr(Level, ...)
#define cdbg(...)
#define cout(...) { printf(__VA_ARGS__); printf("\n"); }

#define ERROR_FATAL 0
#define ERROR_SIMPLE 0

enum {
 LOG_MESSAGE = 0,
 LOG_ERROR = 1,
 LOG_DEBUG = 2,
};

#define LOG_MSG LOG_MESSAGE
#define LOG_ERR LOG_ERROR
#define LOG_DBG LOG_DEBUG

typedef enum
boolean_e {
 false = 0,
 true = 1
} boolean_t;

typedef unsigned char byte;
typedef unsigned int uint;

typedef char* string_t;

typedef union
vector2f_u {
 float elements[2];
 float x, y;
} vector2f_t;

typedef union
vector3f_u {
 float elements[3];
 float x, y, z;
} vector3f_t;

typedef union
color_u {
 uint elements[4];
 uint r, g, b, a;
} color_t;

typedef union
float_color_u {
 float elements[4];
 float r, g, b, a;
} float_color_t;

typedef struct {
 int length;
 byte* pointer;
} memory_t;

typedef uint reference_t;
typedef byte* pointer_t;

float current_time();
void delay(float seconds);

int load_file(string_t file, string_t* text);

void print_no_ws(char* pointer);
