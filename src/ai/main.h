#pragma once

#include "http.h"
#include "map/map.h"
#include "net.h"
#include "thread.h"

extern bool use_console;
extern bool use_gui;
extern bool use_http;

void proc_args(int argc, char** argv);
void proc_cmds(const char* text);
void exec_file(const char* path);
void exec_file(FILE* file);
