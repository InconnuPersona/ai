#pragma once

struct gui_sdl2_render : public gui_i {
	gui_sdl2_render();

	static void clip_copy(nk_handle user, const char* text, int len);
	static void clip_paste(nk_handle user, nk_text_edit* edit);
	
	void init(view_mode_s& mode) override;
};

#ifdef GFX_IMPLEMENTATION

gui_sdl2_render::gui_sdl2_render() : gui_i(GUI_SDL2_RENDER) {
	

}

void gui_sdl2_render::clip_copy(nk_handle user, const char* text, int len) {
	string_t str(text);

	SDL_SetClipboardText(str.c_str());
}

void gui_sdl2_render::clip_paste(nk_handle user, nk_text_edit* edit) {
	const char* text = SDL_GetClipboardText();

	if (text) {
		nk_textedit_paste(edit, text, nk_strlen(text));
	}
}

void gui_sdl2_render::init(view_mode_s& mode) {
	SDL_version runtime;
	//view_sdl2* view;
	//draw_sdl2* draw;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GetVersion(&runtime);

	//log.printf();

	if (SDL_VERSIONNUM(runtime.major, runtime.minor, runtime.patch) < SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL)) {
		//log.printf("SDL2 runtime version %i.%i.%i is older than the compiled version %i.%i.%i, which may cause issues with rendering.");
	}

	/*

	view = new view_sdl2();

	view->get_view_modes(view_modes);

	draw = new draw_sdl2();

	draw->init(view->get_handle());

	// Fonts

	//draw->init_fonts();*/

	nk_init_default(this, NULL);

	// clipboard

	clip.copy = clip_copy;
	clip.paste = clip_paste;
	clip.userdata = nk_handle_ptr(NULL);

	nk_buffer_init_default(&commands);

	gfx::view = view;
	gfx::draw = draw;
}

#endif
