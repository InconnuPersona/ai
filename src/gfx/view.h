#pragma once

struct view_i {
 
 
 
 // x is width, y is height
 virtual vec2 size();
};

extern view_i* view;

// SDL2 is the first option.
#if defined(USE_SDL2)
 #include "view_sdl2.h"
#endif

#if defined(USE_SFML)
 #include "view_sfml.h"
#endif

#if defined(USE_D3D)
 #include "view_d3d.h"
#endif

