#define AI_GFX_IMPLEMENTATION

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

const nk_draw_vertex_layout_element gui_i::vertex_layout[] = {
	{ NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, pos) },
	{ NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, uv) },
	{ NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(vertex_s, color) },
	{ NK_VERTEX_LAYOUT_END }
};

gui_font_s::gui_font_s(float size) : size(size) {
	atlas = new nk_font_atlas;
	handle = NULL;
}

gui_i::gui_i(gui_e type) : type(type), font_scale(1.f) {
	
	//gui_ifaces.push_back(this);
}

/*void gui_i::init(view_mode_s& mode) {
	// Close view and draw APIs.
	//draw.close();
	//view.close();

	//nk_init_default(&context, NULL);

	//clip.userdata = 

	//nk_buffer_init_default(&commands);



	//count++;
}*/

void gui_i::close() {
	//draw.close();
	//view.close();

	//nk_font_atlas_clear(&font_atlas);

	nk_buffer_free(&commands);
	nk_free(this);
}

void gfx::init_gui(cstring_t& iface, view_mode_s mode) {
	
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

void gui_i::font_stash_begin(gui_font_s* font) {
	nk_font_atlas_init_default(font->atlas);
	nk_font_atlas_begin(font->atlas);
}

gui_font_s* gui_i::load_font(cstring_t& path, float size, struct nk_font_config& config) {
	gui_font_s* font;

	font = new gui_font_s(size);

	font_stash_begin(font);

	font->handle = nk_font_atlas_add_from_file(font->atlas, path.c_str(), font->size * font_scale, &config);

	font_stash_end(font);

	return font;
}

void gui_i::set_font(gui_font_s* font) {
	if (!font) {
		ERROR("invalid pointer to gui_font_s");
	}

	nk_style_set_font(this, &font->handle->handle);
}

void gui_i::finish(view_i* view, draw_i* draw) {
	struct nk_font_config config;

	gfx::view = view;
	gfx::draw = draw;

	default_font = new gui_font_s(default_font_size);

	config = nk_font_config(0);

	font_stash_begin(default_font);

	default_font->handle = nk_font_atlas_add_default(default_font->atlas, default_font->size * font_scale, &config);

	font_stash_end(default_font);

	set_font(default_font);
}
