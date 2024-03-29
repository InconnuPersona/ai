#pragma once

#include "SDL2/SDL.h"

struct view_sdl2 : view_i {
	int display;
	SDL_Window* window;
	Uint32 window_flags;
	
	view_sdl2();

	void open(int width, int height, cstring_t& title, bool fullscreen = false, int display = 0) override; // Initializes the view system.
	
	void close() override;

	SDL_Window* get_handle();

	void set_flags(int flags);

	void get_view_modes(vector_t<view_mode_s>& modes) override;

	vec2 size() override;
};

#ifdef AI_GFX_IMPLEMENTATION

view_sdl2::view_sdl2() {
	display = 0;
	window = NULL;
	window_flags = 0;
}

void view_sdl2::open(int width, int height, cstring_t& title, bool fullscreen, int display) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display), width, height, window_flags);

	if (!window) {
		ERROR("unable to create SDL2 window.");
	}

	this->display = SDL_GetWindowDisplayIndex(window);

	if (this->display < 0) {
		ERROR("window is on an invalid display.");
	}
}

void view_sdl2::close() {

}

SDL_Window* view_sdl2::get_handle() {
	return window;
}

void view_sdl2::get_view_modes(vector_t<view_mode_s>& modes) {
	SDL_DisplayMode mode;
	int count, i;

	count = SDL_GetNumDisplayModes(display);

	if (count < 1) {
		ERROR("unable to get number of display modes.");
	}

	for (i = 0; i < count; i++) {
		if (SDL_GetDisplayMode(display, i, &mode) != 0) {
			ERROR("unable to get display mode.");
		}

		modes.push_back({ mode.w, mode.h, mode.refresh_rate });
	}
}

void view_sdl2::set_flags(int flags) {
	window_flags = flags;
}

vec2 view_sdl2::size() {
	int w, h;

	SDL_GetWindowSize(window, &w, &h);

	return vec2(w, h);
}

#endif
