#pragma once

struct gui_sdl2_render : public gui_i {
	SDL_Renderer* renderer;
	SDL_Window* window;

	map_t<gui_font_s*, SDL_Texture*> fonts;

	gui_sdl2_render();

	static void clip_copy(nk_handle user, const char* text, int len);
	static void clip_paste(nk_handle user, nk_text_edit* edit);
	
	void init(view_mode_s& mode) override;
	void close() override;
	void render(bool antialias) override;

	void poll_input(double time) override;

protected:
	void font_stash_end(gui_font_s* font) override;
};

#ifdef AI_GFX_IMPLEMENTATION

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

void gui_sdl2_render::close() {

}

void gui_sdl2_render::font_stash_end(gui_font_s* font) {
	SDL_Texture* texture;
	const void* data;
	int w, h;

	data = nk_font_atlas_bake(font->atlas, &w, &h, NK_FONT_ATLAS_RGBA32);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	if (!texture) {
		ERROR("unable to create font texture.");
	}

	SDL_UpdateTexture(texture, NULL, data, w * 4);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	nk_font_atlas_end(font->atlas, nk_handle_ptr(texture), &null_texture);

	if (font_scale > 1.f) {
		font->handle->handle.height /= font_scale;
	}

	fonts.insert({ font, texture });
}

void gui_sdl2_render::init(view_mode_s& mode) {
	SDL_version runtime;
	int flags;
	
	flags = SDL_INIT_VIDEO;

	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

	if (SDL_Init(flags) != 0) {
		ERROR("unable to initialize SDL2.");
	}

	SDL_GetVersion(&runtime);

	//log.printf();

	if (SDL_VERSIONNUM(runtime.major, runtime.minor, runtime.patch) < SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL)) {
		//log.printf("SDL2 runtime version %i.%i.%i is older than the compiled version, which may cause issues with rendering.");
	}

	// Preinstantiate interfaces instead.
	view = new view_sdl2();

	view->get_view_modes(view_modes);
	view->set_flags(SDL_WINDOW_SHOWN);

	view->open(mode.w, mode.h, PROJ_NAME);

	window = view->get_handle();

	draw = new draw_sdl2();

	draw->init(window);

	renderer = draw->get_handle();

	//draw->init_fonts();

	nk_init_default(this, NULL);

	clip.copy = clip_copy;
	clip.paste = clip_paste;
	clip.userdata = nk_handle_ptr(NULL);

	nk_buffer_init_default(&commands);

	finish(view, draw);
}

void gui_sdl2_render::poll_input(double time) {
	SDL_Event e;
	nk_glyph glyph;
	int x, y;
	bool down;

	nk_input_begin(this);
	
	while (SDL_PollEvent(&e)) {
		if (input.mouse.grab) {
			SDL_SetRelativeMouseMode(SDL_TRUE);

			input.mouse.grab = 0;
		}
		else if (input.mouse.ungrab) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_WarpMouseInWindow(window, input.mouse.prev.x, input.mouse.prev.y);

			input.mouse.ungrab = 0;
		}

		switch (e.type) {
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			down = (e.type == SDL_MOUSEBUTTONDOWN);
			x = e.button.x;
			y = e.button.y;

			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				if (e.button.clicks > 1) {
					nk_input_button(this, NK_BUTTON_DOUBLE, x, y, down);
				}
				
				nk_input_button(this, NK_BUTTON_LEFT, x, y, down);
				
				break;

			case SDL_BUTTON_MIDDLE:
				nk_input_button(this, NK_BUTTON_MIDDLE, x, y, down);
				break;

			case SDL_BUTTON_RIGHT:
				nk_input_button(this, NK_BUTTON_RIGHT, x, y, down);
				break;
			}
			
			break;

		case SDL_MOUSEMOTION:
			if (input.mouse.grabbed) {
				x = input.mouse.prev.x;
				y = input.mouse.prev.y;

				nk_input_motion(this, x + e.motion.xrel, y + e.motion.yrel);
			}
			else {
				nk_input_motion(this, e.motion.x, e.motion.y);
			}
			break;

		case SDL_MOUSEWHEEL:
			nk_input_scroll(this, nk_vec2((float) e.wheel.x, (float) e.wheel.y));
			break;

		case SDL_TEXTINPUT:
			memcpy(glyph, e.text.text, NK_UTF_SIZE);

			nk_input_glyph(this, glyph);
			break;

		default:
			break;
		}
	}

	nk_input_end(this);
}

void gui_sdl2_render::render(bool antialias) {
	nk_anti_aliasing aa;
	nk_buffer vbuf, ebuf;
	nk_convert_config config;
	const nk_draw_command* cmd = NULL;
	const nk_draw_index* offset = NULL;
	SDL_Rect clip, saved_clip;
	const void* vertices;
	bool clipping_enabled;
	size_t vp, vt, vc;
	int vs;
#ifdef NK_SDL_CLAMP_CLIP_RECT
	SDL_Rect port;
#endif

	aa = antialias ? NK_ANTI_ALIASING_ON : NK_ANTI_ALIASING_OFF;

	{
		std::memset(&config, 0, sizeof(config));

		config.vertex_layout = vertex_layout;
		config.vertex_size = sizeof(vertex_s);
		config.vertex_alignment = alignof(vertex_s);
		config.circle_segment_count = 22;
		config.curve_segment_count = 22;
		config.arc_segment_count = 22;
		config.global_alpha = 1.0f;
		config.shape_AA = aa;
		config.line_AA = aa;

		vs = sizeof(vertex_s);
		vp = offsetof(vertex_s, pos);
		vt = offsetof(vertex_s, uv);
		vc = offsetof(vertex_s, color);

		nk_buffer_init_default(&vbuf);
		nk_buffer_init_default(&ebuf);

		nk_convert(this, &commands, &vbuf, &ebuf, &config);

		offset = (const nk_draw_index*) nk_buffer_memory_const(&ebuf);
	}

	{
		clipping_enabled = SDL_RenderIsClipEnabled(renderer);

		SDL_RenderGetClipRect(renderer, &saved_clip);

#ifdef NK_SDL_CLAMP_CLIP_RECT
		SDL_RenderGetViewport(renderer, &port);
#endif
	}

	nk_draw_foreach(cmd, this, &commands) {
		if (!cmd->elem_count) {
			continue;
		}

		clip.x = cmd->clip_rect.x;
		clip.y = cmd->clip_rect.y;
		clip.w = cmd->clip_rect.w;
		clip.h = cmd->clip_rect.h;
		
#ifdef NK_SDL_CLAMP_CLIP_RECT
		if (r.x < 0) {
			r.w += r.x;
			r.x = 0;
		}

		if (r.y < 0) {
			r.h += r.y;
			r.y = 0;
		}
		
		r.w = std::max(r.w, port.w);
		r.h = std::max(r.h, port.h);
#endif

		SDL_RenderSetClipRect(renderer, &clip);

		vertices = nk_buffer_memory_const(&vbuf);

		SDL_RenderGeometryRaw(
			renderer,
			(SDL_Texture*) cmd->texture.ptr,
			(const float*) ((byte_t*) vertices + vp), vs,
			(const SDL_Color*) ((byte_t*) vertices + vc), vs,
			(const float*) ((byte_t*) vertices + vt), vs,
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

#endif
