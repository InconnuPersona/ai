#include "input.h"
#include "video.h"
#include "view.h"
#include "world.h"

#undef main

user_interface_t ui;
world_t world;

input_t input;
video_t video;
video_state_t videoState;
view_t test_view;

texture_t tv_texture;

int mx, my;

string_t rootdir = ".";

color_t color = { 0, 0, 0, 255 };

texture_t test;

void tv_open
(view_t* view, video_t* video) {
 color_t text_color = { 255, 255, 255, 255 };
 vector2f_t pos = { 0, 0 };
 
 init_world(&world, &ui);
 
 render_text("Gloria fortis miles; the walls close further in.", &ui.video->font, text_color, pos, video, &tv_texture);
 load_texture(&test, video, "../AI/Assets/Graphics/map.png");
 
 return;
}

void tv_process
(view_t* view, float time) {
 
 process_present(&world, time);
 
 return;
}

void tv_render
(view_t* view, video_t* video, view_port_t* port) {
 tv_texture.target.x = mx;
 tv_texture.target.y = my;
 
 render_texture(&test, ui.video, port);
 render_texture(&tv_texture, ui.video, port);
 
 return;
}

void init_test_view
(void) {
 
 test_view.open = tv_open;
 test_view.process = tv_process;
 test_view.render = tv_render;
 
 return;
}

void init_libraries
(void) {
 int sdl_flags = SDL_INIT_AUDIO | SDL_INIT_VIDEO;
 int sdl_image_flags = IMG_INIT_PNG;
 int sdl_mixer_flags = MIX_INIT_MP3 | MIX_INIT_MID;
 
 if (SDL_Init(sdl_flags) != 0) {
  clog(LOG_ERROR, "init: 'SDL2' library initialization failed - %s.", SDL_GetError());
  return;
 }
 
 if (IMG_Init(sdl_image_flags) != sdl_image_flags) {
  clog(LOG_ERROR, "init: 'SDL2' image library initialization failed - %s", IMG_GetError());
  return;
 }
 
 if (TTF_Init() != 0) {
  clog(LOG_ERROR, "init: 'SDL2' 'TTF' font library initialization failed - %s.", TTF_GetError());
  return;
 }
 
 if (Mix_Init(sdl_mixer_flags) != 0) {
  clog(LOG_ERROR, "init: 'SDL2' audio mixer library initialization failed - %s.", Mix_GetError());
  return;
 }
 
 if (SDLNet_Init() == -1) {
  clog(LOG_ERROR, "init: 'SDL2' networking library initialization failed - %s.", SDLNet_GetError());
  return;
 }
 
 return;
}

void init
(void) {
 
 init_libraries();
 
 {
  {
   videoState.width = 640;
   videoState.height = 480;
   videoState.label = "Annexatio Imperii";
   videoState.fontFile = "../ai/assets/graphics/fonts/times.ttf";
  }
  
  init_video(&video, &videoState);
  
  init_input(&input);
  
  init_view_context();
  init_test_view();
  
  load_world(&world, "test.txt");
  
  {
   ui.type = 
   ui.audio = NULL;
   ui.input = &input;
   //ui.network = &network;
   ui.video = &video;
   ui.view = &test_view;
  }
 }
 
 return;
}

void quit
(void) {
 Mix_Quit();
 TTF_Quit();
 IMG_Quit();
 SDL_Quit();
 
 cout("quit: successful exit.");
 
 return;
}

int main
(int argc, char** argv) {
 float sleep_time = 1.f / 30;
 
 init();
 
 open_view(ui.view, ui.video);
 
 while (1) {
  receive_input();
  
  process_view(ui.view, current_time());
  
  clear_present(&video, color);
  
  render_view(ui.view, ui.video, (view_port_t*) 1);
  
  render_present(&video);
  
  delay(sleep_time);
 }
 
 quit();
 
 return 0;
}
