#pragma once

#include "base.h"

// Defined to be a default fallback in case no other
// systems are available or selected.
// Undefine to disable it.
#define USE_SDL2

namespace gfx {
	struct view_mode_s {
		int w, h;
		int refresh_rate;
	};

	struct view_i {
		vector_t<view_mode_s> view_modes;

		virtual void open(int width, int height, cstring_t& title, bool fullscreen, int display) = 0;

		virtual void close() = 0;

		// Retreive a list of view modes for the window.
		virtual void get_view_modes(vector_t<view_mode_s>& modes) = 0;

		// Retreive the dimensions of the view window.
		virtual vec2 size() = 0;
	};

	extern view_i* view;

	#if defined(USE_SDL2)
	 #include "view_sdl2.h"
	#endif
	
	#if defined(USE_SFML)
	 #include "view_sfml.h"
	#endif
	
	#if defined(USE_D3D)
	 #include "view_d3d.h"
	#endif
}