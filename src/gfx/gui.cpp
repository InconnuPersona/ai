#define GFX_IMPLEMENTATION

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "gui.h"

IN_NAMESPACE(gfx);

view_i* gfx::view;
draw_i* gfx::draw;
gui_i* gfx::gui;

vector_t<gui_i*> gui_ifaces;

gui_i::gui_i(gui_e type) : type(type) {
	

	gui_ifaces.push_back(this);
}

/*void gui_i::init() {
	// Close view and draw APIs.
	//draw.close();
	//view.close();

	//count++;
}*/

void gui_i::close() {
	//draw.close();
	//view.close();
}

void init_gui(cstring_t& iface, view_mode_s mode) {
	
	if (gui) {
		//ERROR("GUI already initialized.");
		// Close the previous GUI and initialize a new GUI

		return;
	}

	//std::transform(iface.begin, iface.end, iface.begin, tolower);

#ifdef USE_SDL2
	if (iface == "sdl2render") {
		gui = new gui_sdl2_render();
	}
#endif
	else {
		ERROR("GUI interface not supported.")
	}

	gui->init(mode);
}
