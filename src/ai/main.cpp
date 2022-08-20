#include "gfx/gui.h"
#include "main.h"

/*#include <sys/poll.h>

#ifndef STDIN_FILENO
 #define STDIN_FILENO _fileno(stdin)
#endif

#define STDIN_PROMPT "> "

// For right now, implement everything by hand.*/

map::map_s world;
//int game_speed = 2000;
vers_s version;
//host_s host;

bool use_console = false;
bool use_gui = true;
bool use_http = false;

void quit() {
 fflush(stdout);
 
 exit(0);
}

/*void read_stdin() {
 pollfd fds;
 size_t size;
 char* text;
 int ret;
 
 fds.fd = STDIN_FILENO;
 fds.events = POLLIN;
 
 while (true) {
  ret = poll(&fds, 1, 0);
  
  switch (ret) {
  case 0:
   return;
   
  case 1:
   //printf("reading...\n");
   
   text = NULL;
   size = 0;
   
   if (getline(&text, &size, stdin) > 0) {
	proc_cmds(text);
	
	free(text);
   }
   
   printf(STDIN_PROMPT);
   
   fflush(stdout);
   
   break;
   
  default:
   ERROR("file descriptor read error.");
  }
 }
 
 fflush(stdout);
}*/

#undef main

int main(int argc, char** argv) {
 string_t build;
 watch_s watch;
 
 if (atexit(quit)) {
  ERROR("unable to register exit function.");
 }
 
 //=====================================================
 
 build = __DATE__;
 
 version.major = 0;
 version.minor = 1;
 version.build = 0;
 
 for (char c : build) {
  version.build += (int) c;
 }
 
 version.print();
 printf("executable compiled on " __DATE__ " " __TIME__ ".\n");
 
 proc_args(argc, argv);
 
 //=====================================================
 
 if (use_gui) {
  gfx::init_gui("sdl2render", { 640, 480, 60 });
 }
 
 // Load core game data.
 exec_file("res/core.txt");
 
 //=====================================================
 
 //view.off = vec2(-750, -100);
 //view.scale = 1.f;
 
 //model = glm::translate(model, vec3(view.off.x, view.off.y, 1));
 
 //if (use_console) {
 // set_nonblock(STDIN_FILENO);
 // 
 // printf("console enabled.\n");
 // printf(STDIN_PROMPT);
 // 
 // fflush(stdout);
 //}
 
 //=====================================================
 
 double last;

 watch.sync();

 while (true) {
  //if (use_console) {
  // read_stdin();
  //}
  
  if (use_gui && gfx::gui) {
   gfx::gui->input(watch.time());
  }
  
  /*if (!game_speed) {
   last = time;
  }
  else if (game_speed < 0) {
   ERROR("negative game speed reached.");
  }
  
  lost = watch.elapsed() / game_speed;

  // Tick game.
  while (lost) {
   //if (clients are behind by a day, wait.)
   // printf("waiting for clients to sync.\n");
   //map.tick_day();
   
   watch

   watch += game_speed;
   lost--;
  }*/
  
  // -------------------------------------------------------
  
  if (use_gui && gfx::gui) {
   //map->render();
   gfx::gui->render(true);

   //gfx::draw->render();
  }
  
  thread_s::sleep(1.0 / 30);
 }
 
}
