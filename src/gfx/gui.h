#pragma once

#include "draw.h"

#include "nuklear.h"

namespace gfx {

	enum gui_e {
		GUI_SDL2_RENDER = 0,
		GUI_SDL2_OPENGL,
		GUI_SDL2_VULKAN,
		GUI_SFML_RENDER,
		GUI_SFML_OPENGL,
		GUI_WIN32_D3D9,
	};

	struct vertex_s {
		vec2 pos;
		vec2 uv;
		color_s color;
	};

	struct gui_i : public nk_context {
		static const nk_draw_vertex_layout_element vertex_layout[];

		gui_e type;

		vector_t<view_mode_s> view_modes;

		nk_buffer commands;
		nk_convert_config config;
		nk_font_atlas font_atlas;

		nk_draw_null_texture null_texture;

		gui_i(gui_e type);

		virtual void init(view_mode_s& mode) = 0;
		virtual void close();
		virtual void font_stash();
		virtual void render(bool antialias);

		virtual void input(double time);

		//void click();
		//void drag();
		//void scroll();
	};

	extern vector_t<gui_i*> gui_ifaces;
	extern gui_i* gui;

	void init_gui(cstring_t& iface, view_mode_s mode);

	#ifdef USE_SDL2
	 #if defined(USE_OPENGL)
	  #include "gui_sdl2_gl3.h"
	 #elif defined(USE_VULKAN)
	  #include "gui_sdl2_vulkan.h"
	 #else
	  #include "gui_sdl2_render.h"
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

}
