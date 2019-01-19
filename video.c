#include "video.h"

void init_video
(video_t* video, video_state_t* state) {
 if (!video || !state) {
  clog(LOG_ERROR, "init_video: null argument(s) received.");
  return;
 }
 
 if (!state->label || state->width < 1 || state->height < 1) {
  clog(LOG_ERROR, "init_video: invalid initial window state.");
  return;
 }
 
 video->window.handle = SDL_CreateWindow(state->label, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, state->width, state->height, SDL_WINDOW_SHOWN);
 
 if (!video->window.handle) {
  clog(LOG_ERROR, "init_video: 'SDL2' window creation failed - %s.", SDL_GetError());
  return;
 }
 
 video->window.renderer = SDL_CreateRenderer(video->window.handle, -1, SDL_RENDERER_SOFTWARE);
 
 if (!video->window.renderer) {
  clog(LOG_ERROR, "init_video: 'SDL2' renderer creation failed - %s.", SDL_GetError());
  return;
 }
 
 init_font(&video->font, state->fontFile, "default", 12);
 
 return;
}

void clear_present
(video_t* video, color_t color) {
 SDL_SetRenderDrawColor(video->window.renderer, color.r, color.g, color.b, color.a);
 SDL_RenderClear(video->window.renderer);
 
 return;
}

void render_present
(video_t* video) {
 if (!video) {
  return;
 }
 
 SDL_RenderPresent(video->window.renderer);
}

void load_texture
(texture_t* texture, video_t* video, string_t file) {
 SDL_Surface* surface;
 SDL_Rect* source;
 SDL_Rect* target;
 
 if (!texture || !file) {
  cout("load_texture: ");
  return;
 }
 
 texture->file = file;
 
 surface = IMG_Load(file);
 
 if (!surface) {
  cout("load_texture: could not load '%s'", IMG_GetError());
  return;
 }
 
 texture->surface = surface;
 
 texture->handle = SDL_CreateTextureFromSurface(video->window.renderer, surface);
 
 if (!texture->handle) {
  cout("load_texture: could not create texture from surface");
  return;
 }
 
 source = &texture->source;
 target = &texture->target;
 
 source->x = source->y = 0;
 SDL_QueryTexture(texture->handle, NULL, NULL, &source->w, &source->h);
 
 target->x = target->w = 0;
 SDL_QueryTexture(texture->handle, NULL, NULL, &target->w, &target->h);
 
 //texture->handle = handle;
 
 return;
}

void render_texture
(texture_t* texture, video_t* video, view_port_t* port) {
 
 if (!texture || !video || !port) {
  return;
 }
 
 SDL_RenderCopy(video->window.renderer, texture->handle, &texture->source, &texture->target);
 
 return;
}

void init_font
(font_t* font, string_t file, string_t name, int size) {
 
 if (!font || !name || !file || size < 1) {
  return;
 }
 
 font->name = name;
 font->handle = TTF_OpenFont(file, size);
 
 if (!font->handle) {
  clog(LOG_ERROR, "init_font: could not load font - %s.", TTF_GetError());
  return;
 }
 
 return;
}

void free_font
(font_t* font) {
 if (!font) {
  return;
 }
 
 TTF_CloseFont(font->handle);
 
 return;
}

void render_text
(string_t text, font_t* font, color_t color, vector2f_t position, video_t* video, texture_t* texture) {
 SDL_Rect* source;
 SDL_Rect* target;
 SDL_Surface* surface;
 SDL_Color sdl_color = { color.r, color.g, color.b };
 int w, h;
 
 if (!text || !video || !texture) {
  clog(LOG_ERROR, "render_text: .");
  return;
 }
 
 if (!font) {
  font = &video->font;
 }
 
 //clog(LOG_DEBUG, "render_text: received arguments text[%s] font[%i] color[%i, %i, %i] position[%i, %i] video[%i] texture[%i]", text, font, color.r, color.g, color.b, position.x, position.y, video, texture);
 
 surface = TTF_RenderText_Solid(font->handle, text, sdl_color);
 
 if (!surface) {
  clog(LOG_ERROR, "render_text: could not create or render font surface - %s.", TTF_GetError());
  return;
 }
 
 texture->file = 0;
 texture->handle = SDL_CreateTextureFromSurface(video->window.renderer, surface);
 
 if (!texture->handle) {
  clog(LOG_ERROR, "render_text: could not create texture from font surface - %s.", SDL_GetError());
  return;
 }
 
 source = &texture->source;
 target = &texture->target;
 
 source->x = source->y = 0;
 
 target->x = position.x;
 target->y = position.y;
 
 SDL_QueryTexture(texture->handle, NULL, NULL, &w, &h);
 
 source->w = target->w = w;
 source->h = target->h = h;
 
 SDL_FreeSurface(surface);
 
 return;
}
