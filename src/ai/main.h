#pragma once

#include "map/map.h"
#include "net.h"

extern bool use_console;
extern bool use_gui;

void input(int time);

void proc_args(int argc, char** argv);
void proc_cmds(const char* text);
void exec_file(const char* path);
void exec_file(FILE* file);
