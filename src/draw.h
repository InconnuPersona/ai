#pragma once




#if defined(USE_SDL2)
 #ifdef USE_OPENGL
  #include "draw_gl3.h"
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
