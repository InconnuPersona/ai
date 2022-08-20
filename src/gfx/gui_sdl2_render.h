#pragma once

struct gui_sdl2_render : public gui_i {
	gui_sdl2_render();

	static void clip_copy(nk_handle user, const char* text, int len);
	static void clip_paste(nk_handle user, nk_text_edit* edit);
	
	void init(view_mode_s& mode) override;
	void render(bool antialias) override;
};

#ifdef GFX_IMPLEMENTATION

gui_sdl2_render::gui_sdl2_render() : gui_i(GUI_SDL2_RENDER) {
	
}

void gui_sdl2_render::render(bool antialias) {
	SDL_Rect saved_clip;
	SDL_Rect viewport;
	size_t vp, vt, vc;
	int vs;
	nk_anti_aliasing aa;
	nk_draw_index* offset;

	nk_buffer vbuf, ebuf;
	const nk_draw_command* cmd;

	aa = antialias ? NK_ANTI_ALIASING_ON : NK_ANTI_ALIASING_OFF;

	config.shape_AA = aa;
	config.line_AA = aa;

	vs = sizeof(vertex_s);

	nk_buffer_init_default(&vbuf);
	nk_buffer_init_default(&ebuf);

	nk_convert(this, &commands, &vbuf, &ebuf, &config);

	offset = (nk_draw_index*) nk_buffer_memory_const(&ebuf);

	bool clipping_enabled;

	clipping_enabled = SDL_RenderIsClipEnabled(renderer);

	nk_draw_foreach(cmd, &context, &commands) {
		if (!cmd->elem_count) {
			continue;
		}

		SDL_RenderGeometryRaw(
			renderer,
			(SDL_Texture*)cmd->texture.ptr,
			(const float*) , vs,
			(const float*) , vs,
			(const float*) , vs,
			(int) (vbuf.needed / vs),
			(void*) offset, cmd->elem_count, 2);

		offset += cmd->elem_count;
	}

	SDL_RenderSetClipRect(renderer, &saved_clip);

	if (!clipping_enabled) {
		SDL_RenderSetClipRect(renderer, NULL);
	}

	nk_clear(this);
	nk_buffer_clear(&commands);
	nk_buffer_free(&vbuf);
	nk_buffer_free(&ebuf);
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
