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

	struct gui_font_s {
		struct nk_font_atlas* atlas;
		struct nk_font* handle;
		float size;

		gui_font_s(float size);
	};

	struct gui_i : public nk_context {
		typedef void (*quit_f)(gui_i* gui);

	protected:
		const float default_font_size = 12.f;
		
		static const nk_draw_vertex_layout_element vertex_layout[];
		
		gui_e type;

		vector_t<view_mode_s> view_modes;

		nk_buffer commands;
		float font_scale;

		nk_draw_null_texture null_texture;
		
		gui_font_s* default_font;

		view_sdl2* view;
		draw_sdl2* draw;
		
	public:
		gui_i(gui_e type);

		virtual void init(view_mode_s& mode) = 0;
		virtual void close() = 0;
		virtual void render(bool antialias) = 0;

		virtual gui_font_s* load_font(cstring_t& path, float size, struct nk_font_config& config);

		void set_font(gui_font_s* font);

		virtual void poll_input(double time) = 0;

		//void click();
		//void drag();
		//void scroll();

	protected:
		void finish(view_i* view, draw_i* draw);

		virtual void font_stash_begin(gui_font_s* font);
		virtual void font_stash_end(gui_font_s* font) = 0;
	};

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
