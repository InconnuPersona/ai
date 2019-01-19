#pragma once

#include "base.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_TTF.h>

#define MAX_WINDOW_DIMENSIONS 2

typedef struct {
 vector3f_t position;
 
} camera_t;

typedef struct
font_s {
 string_t name;
 TTF_Font* handle;
} font_t;

typedef struct
texture_s {
 string_t file;
 SDL_Surface* surface;
 SDL_Texture* handle;
 SDL_Rect source, target;
} texture_t;

typedef struct
view_port_s {
 vector2f_t dimensions;
} view_port_t;

typedef struct
window_s {
 uint width, height;
 SDL_Window* handle;
 SDL_Renderer* renderer;
} window_t;

typedef struct
video_state_s {
 string_t label;
 uint width, height;
 string_t fontFile;
} video_state_t;

typedef struct
video_s {
 window_t window;
 view_port_t port;
 font_t font;
} video_t;

void init_video(video_t* video, video_state_t* initial_state);

void clear_present(video_t* video, color_t color);
void render_present(video_t* video);

void load_texture(texture_t* texture, video_t* video, string_t file);
void free_texture(texture_t* texture);

void render_texture(texture_t* texture, video_t* video, view_port_t* port);

void init_font(font_t* font, string_t file, string_t name, int size);
void free_font(font_t* font);

void render_text(string_t text, font_t* font, color_t color, vector2f_t position, video_t* video, texture_t* texture);
