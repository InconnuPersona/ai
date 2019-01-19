#include "input.h"

#include <SDL2/SDL.h>

extern int mx, my;

void init_input
(input_t* input) {
 
 if (!input) {
  return;
 }
 
 input->buffer = calloc(MAX_INPUT_BUFFER_ELEMENTS, sizeof(input_element_p));
 input->elements = NEW(input_element_p);
 
 input->key_map = NULL;
 
 // TODO: setup SDL event filters for mobile applications
 
 return;
}

//boolean_t add_input_key
//(input_key* key, )

boolean_t set_input_key
(input_key_t* key, input_t* input) {
 input_key_t* index;
 
 if (!key || !input) {
  return false;
 }
 
 if (get_input_key(&index, key->label, input)) {
  index->state = key->state;
  index->time = key->time;
  
  return true;
 }
 else {
  //add_input_key(key, input);
 }
 
 return false;
}

boolean_t get_input_key
(input_key_t** key, string_t label, input_t* input) {
 input_key_t* index;
 
 if (!key || !input || !label) {
  clog(LOG_DEBUG, "get_input_key: .");
  return false;
 }
 
 for (index = input->key_map; index; index = (input_key_t*) index->next) {
  if (strcmp(label, index->label) == 0) {
   *key = index;
   return true;
  }
 }
 
 return false;
}

void receive_input
(void) {
 SDL_Event e;
 
 while (SDL_PollEvent(&e)) {
  switch (e.type) {
  case SDL_QUIT:
   clog(LOG_MESSAGE, "receive_input: 'SDL_QUIT' event received.");
   exit(0);
   break;
   
  case SDL_KEYDOWN:
  case SDL_KEYUP:
   cdbg("receive_input: key received - key code [%i] - state [%i] - time [%i]", e.key.keysym.scancode, e.key.state, e.key.timestamp);
   
   input_key_t key;
   
   //key.
   
   //set_input_element();
   
   break;
   
  case SDL_MOUSEMOTION:
   mx = e.motion.x;
   my = e.motion.y;
   cdbg("receive_input: mouse motion received - position [%i, %i] - delta [%i, %i]", e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
   break;
   
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
   cdbg("receive_input: mouse button received");
   break;
   
  case SDL_MOUSEWHEEL:
   cdbg("receive_input: mouse wheel motion received");
   break;
   
  default:
   break;
  }
 }
 
 return;
}
