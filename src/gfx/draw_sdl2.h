#pragma once

struct draw_sdl2 : draw_i {
	SDL_Renderer* renderer;
	float font_scale;

	void init(SDL_Window* window);
};

#ifdef GFX_IMPLEMENTATION

void draw_sdl2::init(SDL_Window* window) {
	int flags;

	flags |= SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

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


#endif
