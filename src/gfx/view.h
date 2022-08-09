#pragma once

#include "base.h"

struct view_mode_s {
	int w, h;
	int refresh_rate;
};

struct view_i {
	vector_t<view_mode_s> view_modes;
	
	virtual void init(int width, int height, cstring_t& title) = 0;

	// Retreive the dimensions of the view window.
	virtual vec2 size() = 0;
};

extern view_i* view;


// For now, just SDL2
#include "view_sdl2.h"

/*#if defined(USE_SFML)
 #include "view_sfml.h"
#endif

#if defined(USE_D3D)
 #include "view_d3d.h"
#endif*/

