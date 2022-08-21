#include "gfx/gui.h"
#include "main.h"

#ifdef _WIN32
 //#include <winsock2.h>
#else
 #include <sys/poll.h>
#endif

#ifndef STDIN_FILENO
 #define STDIN_FILENO _fileno(stdin)
#endif

#define STDIN_PROMPT "> "

// For right now, implement everything by hand.

map::map_s world;
double game_speed = 2.0;
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

#include "gfx/calculator.h"
#include "gfx/canvas.h"
//#include "gfx/overview.h"
#include "gfx/node_editor.h"

struct nk_colorf bg = { 0.1, 0.18, 0.24, 1 };

void test_gui() {
    nk_context* ctx = gfx::gui;

    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        enum { EASY, HARD };
        static int op = EASY;
        static int property = 20;

        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            fprintf(stdout, "button pressed\n");
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
}

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
  
  // Set callbacks.

  // Load fonts.
  //gfx::gui_font_s font;

  // Load cursors.

  // UI customization.
 }
 
 // Load core game data.
 //exec_file("game/core.txt");
 
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
 
 int lost;

 watch.sync();

 while (true) {
  //if (use_console) {
  // read_stdin();
  //}
  
  if (use_gui && gfx::gui) {
   gfx::gui->poll_input(watch.time());
  }
  
  /*if (!game_speed) {
   watch.sync();
  }
  else if (game_speed < 0) {
   ERROR("negative game speed reached.");
  }
  
  lost = (int) (watch.elapsed() / game_speed);

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
   gfx::draw->clear({ 0, 0, 0 });
   
   test_gui();
   
   calculator(gfx::gui);
   canvas(gfx::gui);
   //overview(gfx::gui);
   node_editor(gfx::gui);

   //map->render();
   gfx::gui->render(true);

   gfx::draw->present();
  }
  
  thread_s::sleep(1.0 / 30);
 }
}
