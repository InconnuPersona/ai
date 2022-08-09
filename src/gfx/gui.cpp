#define GFX_IMPLEMENTATION

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "view.h"
#include "draw.h"
#include "gui.h"

vector_t<gui_i*> gui_ifaces;

gui_i::gui_i(gui_e type) : type(type) {
	

	gui_ifaces.push_back(this);
}

void gui_i::init() {
	// Close view and draw APIs.
	//draw.close();
	//view.close();

	//count++;
}

void gui_i::close() {
	//draw.close();
	//view.close();
}

gui_s::gui_s() {
	iface = 0;
}

void gui_s::init(gui_i* iface) {
	if (!iface) {
		ERROR("e");
	}


}

void init_gui(gui_i* iface) {

	if (gui) {
		//ERROR("GUI already initialized.");
		// Close the previous GUI and initialize a new GUI

		return;
	}

	gui = new gui_s();

	gui->init(iface);
}
