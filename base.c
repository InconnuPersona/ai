#include "base.h"

#include <SDL2/SDL.h>

int load_file
(string_t file, string_t* text) {
 FILE* handle;
 int length;
 
 if (!text) {
  cout("load_file: invalid text pointer received.");
  return -1;
 }
 
 handle = fopen(file, "rb");
 
 if (!handle) {
  cout("load_file: could not read file handle - %s.", strerror(errno));
  return -1;
 }
 
 fseek(handle, 0, SEEK_END);
 
 length = ftell(handle);
 
 fseek(handle, 0, SEEK_SET);
 
 text[0] = malloc(length + 1);
 
 fread(*text, sizeof(char), length, handle);
 
 fclose(handle);
 
 text[0][length] = '\0';
 
 return length;
}

float current_time
(void) {
 return (float) (SDL_GetTicks() / 1000.f);
}

void delay
(float seconds) {
 int milliseconds = (int) ((float) seconds * 1000.f);
 
 SDL_Delay(milliseconds);
}
