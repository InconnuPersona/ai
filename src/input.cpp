#include "draw.h"
#include "menu.h"

#define CLICK_TIME 150

void quit();

bool pressed = false;

int last_kdown;
int last_lmdown;
int last_rmdown;

void input(int time) {
 SDL_Event e;
 int x, y;
 
 while (SDL_PollEvent(&e)) {
  
  switch (e.type) {
  case SDL_QUIT:
   quit();
   break;
   
  case SDL_KEYDOWN:
  case SDL_KEYUP:
   break;
   
  case SDL_MOUSEBUTTONDOWN:
   if (e.button.button == SDL_BUTTON_LEFT) {
   	last_lmdown = e.button.timestamp;
   }
   else {
   	last_lmdown = e.button.timestamp;
   }
   break;
   
  case SDL_MOUSEBUTTONUP:
   if (e.button.button == SDL_BUTTON_LEFT) {
	if (e.button.timestamp - last_lmdown < CLICK_TIME) {
	 //menu_click(0, e.button.x, e.button.y);
	}
   }
   else {
	if (e.button.timestamp - last_rmdown < CLICK_TIME) {
	 //menu_click(1, e.button.x, e.button.y);
	}
   }
   break;
   
  case SDL_MOUSEMOTION:
   if (e.motion.state == SDL_BUTTON_LMASK) {
	//menu_drag(0, e.motion.xrel, e.motion.yrel);
   }
   else {
	//menu_drag(1, e.motion.xrel, e.motion.yrel);
   }
   
   break;
   
  case SDL_MOUSEWHEEL:
   SDL_GetMouseState(&x, &y);
   
   //menu_scroll(x, y, e.wheel.y);
   
   break;
  }
  
// Handle inputs on input.
// No need for event, or relay system yet.
 }
 
}
