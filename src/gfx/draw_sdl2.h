#pragma once

struct draw_sdl2 : draw_i {
	SDL_Renderer* renderer;
	float font_scale;

	SDL_Renderer* get_handle();

	void init(SDL_Window* window);

	void clear(color_s color) override;
	void present() override;
};

#ifdef AI_GFX_IMPLEMENTATION

void draw_sdl2::clear(color_s color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);

	SDL_RenderClear(renderer);
}

void draw_sdl2::init(SDL_Window* window) {
	int flags;

	flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(window, -1, flags);

	if (!renderer) {
		ERROR("unable to create SDL2 renderer.");
	}

	vec2 scale;
	vec2i render;
	vec2i size;

	SDL_GetRendererOutputSize(renderer, &render.x, &render.y);
	SDL_GetWindowSize(window, &size.x, &size.y);

	scale = render / size;

	SDL_RenderSetScale(renderer, scale.x, scale.y);

	font_scale = scale.y;
}

void draw_sdl2::present() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* draw_sdl2::get_handle() {
	return renderer;
}

#endif
