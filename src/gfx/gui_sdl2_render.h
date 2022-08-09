#pragma once

struct gui_sdl2_render : gui_i {
	gui_sdl2_render();
};

#ifdef GFX_IMPLEMENTATION

gui_sdl2_render::gui_sdl2_render() : gui_i(GUI_SDL2_RENDER) {

}

#endif

