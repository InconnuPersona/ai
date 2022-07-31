#pragma once

#include "draw.h"

#include "nuklear.h"

struct vertex_s {
 vec2 pos;
 vec2 uv;
 color_s color;
};

struct menu_i {
 static int count = 0;
 
 string_t name;
 
 menu_i(string_t name);
 
 virtual void init();
 virtual void close();
 virtual void font_stash_begin(nk_font_atlas** atlas);
 virtual void font_stash_end();
 virtual void render(bool antialias);
 
 void click();
 void drag();
 void scroll();
};

struct menu_s {
 vector_t<menu_i*> options;
 
 menu_i* iface;
 
 nk_context context;
 nk_buffer cmds;
 nk_font_atlas atlas;
 
 nk_draw_null_texture null;
 
 // font_texture
};

extern menu_s menu;

#if defined(USE_SDL2)
 #ifdef USE_OPENGL
  #include "nuklear_gl3.h"
 #else
  #include "nuklear_sdl2_renderer.h"
 #endif
#endif

#if defined(USE_SFML)
 #ifdef USE_OPENGL
  #include "nuklear_gl3.h"
 #endif
#endif

#if defined(USE_D3D)
 #include "nuklear_d3d9.h"
#endif
