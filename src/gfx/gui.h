#pragma once

#include "draw.h"

#include "nuklear.h"

enum gui_e {
	GUI_SDL2_RENDER = 0,
	GUI_SDL2_OPENGL,
	GUI_SDL2_VULKAN,
	GUI_SFML_RENDER,
	GUI_SFML_OPENGL,
	GUI_WINDOWS_D3D9,
};

struct vertex_s {
	vec2 pos;
	vec2 uv;
	color_s color;
};

struct gui_i {
 gui_e type;
 
 gui_i(gui_e type);
 
 virtual void init();
 virtual void close();
 //virtual void font_stash_begin(nk_font_atlas** atlas);
 virtual void font_stash_end();
 virtual void render(bool antialias);
 
 void click();
 void drag();
 void scroll();
};

struct gui_s {
 
 gui_i* iface;
 
 nk_context context;
 nk_buffer cmds;
 //nk_font_atlas atlas;
 
 nk_draw_null_texture null;
 
 // font_texture

 gui_s();

 void init(gui_i* type);
};

extern vector_t<gui_i*> gui_ifaces;
extern gui_s* gui;

void init_gui(gui_i* type);

#include "gui_sdl2_render.h"

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
