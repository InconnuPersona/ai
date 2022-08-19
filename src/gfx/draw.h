#pragma once

#include "view.h"
#include "image.h"

namespace gfx {
	struct draw_i {
		//int load_texture(image_s& image);


	};

	extern draw_i* draw;

	#if defined(USE_SDL2)
	 #ifdef USE_OPENGL
	  #include "draw_gl3.h"
	 #else
	  #include "draw_sdl2.h"
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