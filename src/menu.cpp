#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "menu.h"

vector_t<menu_i*> menu_i::options;

menu_i::menu_i() : name(name) {
 for (auto& menu : menu.options) {
  if (name == menu.name) {
   ERROR("menu %s already defined.", name.c_str());
  }
 }
 
 menu.options.push_back(this);
}

void menu_i::init() {
 if (count) {
  ERROR("attempted to initialize menu while another was already set.");
 }
 
 // Close view and draw APIs.
 draw.close();
 view.close();
 
 count++;
}

void menu_i::close() {
 draw.close();
 view.close();
 
 count--;
}

