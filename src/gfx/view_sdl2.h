#pragma once

struct view_sdl2 : view_i {
	SDL_Window* window;
	Uint32 window_flags;
	
	void init(int width, int height, cstring_t& title) override; // Initializes the view system.
	
	
};

#ifdef GFX_IMPLEMENTATION

void view_sdl2::init(int width, int height, cstring_t& title) {

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);


}

#endif
