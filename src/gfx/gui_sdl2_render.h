#pragma once

struct gui_sdl2_render : public gui_i {
	SDL_Renderer* renderer;

	map_t<gui_font_s*, SDL_Texture*> fonts;

	gui_sdl2_render();

	static void clip_copy(nk_handle user, const char* text, int len);
	static void clip_paste(nk_handle user, nk_text_edit* edit);
	
	void init(view_mode_s& mode) override;
	void close() override;
	void render(bool antialias) override;

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
		//log.printf("SDL2 runtime version %i.%i.%i is older than the compiled version %i.%i.%i, which may cause issues with rendering.");
	}

	// Preinstantiate interfaces instead.
	view = new view_sdl2();

	view->get_view_modes(view_modes);
	view->set_flags(SDL_WINDOW_SHOWN);

	view->open(mode.w, mode.h, PROJ_NAME);

	draw = new draw_sdl2();

	draw->init(view->get_handle());

	renderer = draw->get_handle();

	//draw->init_fonts();

	nk_init_default(this, NULL);

	clip.copy = clip_copy;
	clip.paste = clip_paste;
	clip.userdata = nk_handle_ptr(NULL);

	nk_buffer_init_default(&commands);

	finish(view, draw);
}

void nk_sdl_render(nk_context& ctx, nk_buffer& cmds, SDL_Renderer* renderer, enum nk_anti_aliasing AA, nk_draw_null_texture& null_texture) {
	SDL_Rect saved_clip;
#ifdef NK_SDL_CLAMP_CLIP_RECT
	SDL_Rect viewport;
#endif
	SDL_bool clipping_enabled;
	int vs = sizeof(vertex_s);
	size_t vp = offsetof(vertex_s, pos);
	size_t vt = offsetof(vertex_s, uv);
	size_t vc = offsetof(vertex_s, color);

	/* convert from command queue into draw list and draw to screen */
	const struct nk_draw_command* cmd;
	const nk_draw_index* offset = NULL;
	struct nk_buffer vbuf, ebuf;

	/* fill converting configuration */
	struct nk_convert_config config;
	static const struct nk_draw_vertex_layout_element vertex_layout[] = {
		{NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, pos)},
		{NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(vertex_s, uv)},
		{NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(vertex_s, color)},
		{NK_VERTEX_LAYOUT_END}
	};
	NK_MEMSET(&config, 0, sizeof(config));
	config.vertex_layout = vertex_layout;
	config.vertex_size = sizeof(vertex_s);
	config.vertex_alignment = NK_ALIGNOF(vertex_s);
	config.null = null_texture;
	config.circle_segment_count = 22;
	config.curve_segment_count = 22;
	config.arc_segment_count = 22;
	config.global_alpha = 1.0f;
	config.shape_AA = AA;
	config.line_AA = AA;

	/* convert shapes into vertexes */
	nk_buffer_init_default(&vbuf);
	nk_buffer_init_default(&ebuf);
	nk_convert(&ctx, &cmds, &vbuf, &ebuf, &config);

	/* iterate over and execute each draw command */
	offset = (const nk_draw_index*)nk_buffer_memory_const(&ebuf);

	clipping_enabled = SDL_RenderIsClipEnabled(renderer);
	SDL_RenderGetClipRect(renderer, &saved_clip);
#ifdef NK_SDL_CLAMP_CLIP_RECT
	SDL_RenderGetViewport(sdl.renderer, &viewport);
#endif

	nk_draw_foreach(cmd, &ctx, &cmds)
	{
		if (!cmd->elem_count) continue;

		{
			SDL_Rect r;
			r.x = cmd->clip_rect.x;
			r.y = cmd->clip_rect.y;
			r.w = cmd->clip_rect.w;
			r.h = cmd->clip_rect.h;
#ifdef NK_SDL_CLAMP_CLIP_RECT
			if (r.x < 0) {
				r.w += r.x;
				r.x = 0;
			}
			if (r.y < 0) {
				r.h += r.y;
				r.y = 0;
			}
			if (r.h > viewport.h) {
				r.h = viewport.h;
			}
			if (r.w > viewport.w) {
				r.w = viewport.w;
			}
#endif
			SDL_RenderSetClipRect(renderer, &r);
		}

		{
			const void* vertices = nk_buffer_memory_const(&vbuf);

			SDL_RenderGeometryRaw(renderer,
				(SDL_Texture*)cmd->texture.ptr,
				(const float*)((const nk_byte*)vertices + vp), vs,
				(const SDL_Color*)((const nk_byte*)vertices + vc), vs,
				(const float*)((const nk_byte*)vertices + vt), vs,
				(vbuf.needed / vs),
				(void*)offset, cmd->elem_count, 2);

			offset += cmd->elem_count;
		}
	}

	SDL_RenderSetClipRect(renderer, &saved_clip);
	if (!clipping_enabled) {
		SDL_RenderSetClipRect(renderer, NULL);
	}

	nk_clear(&ctx);
	nk_buffer_clear(&cmds);
	nk_buffer_free(&vbuf);
	nk_buffer_free(&ebuf);
}

void gui_sdl2_render::render(bool antialias) {
	nk_anti_aliasing aa;
	nk_buffer vbuf, ebuf;
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

	nk_sdl_render(*this, commands, renderer, aa, null_texture);

	/*{
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

	clipping_enabled = SDL_RenderIsClipEnabled(renderer);

	SDL_RenderGetClipRect(renderer, &saved_clip);

#ifdef NK_SDL_CLAMP_CLIP_RECT
	SDL_RenderGetViewport(renderer, &port);
#endif

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
	nk_buffer_free(&ebuf);*/
}

#endif
