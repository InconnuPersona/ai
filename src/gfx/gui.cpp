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

const nk_draw_vertex_layout_element gui_i::vertex_layout[] = {
	{ NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, pos) },
	{ NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, uv) },
	{ NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(vertex_s, color) },
	{ NK_VERTEX_LAYOUT_END }
};

gui_i::gui_i(gui_e type) : type(type) {
	
	NK_MEMSET(&config, 0, sizeof(config));

	config.vertex_layout = vertex_layout;
	config.vertex_size = sizeof(vertex_s);
	config.null = null_texture;
	config.circle_segment_count = 22;
	config.curve_segment_count = 22;
	config.arc_segment_count = 22;
	config.global_alpha = 1.0f;
	
	gui_ifaces.push_back(this);
}

/*void gui_i::init() {
	// Close view and draw APIs.
	//draw.close();
	//view.close();

	nk_init_default(&context, NULL);

	//clip.userdata = 

	nk_buffer_init_default(&commands);



	//count++;
}*/

void gui_i::close() {
	//draw.close();
	//view.close();

	//nk_font_atlas_clear(&font_atlas);

	nk_free(&context);
	nk_buffer_free(&commands);
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
