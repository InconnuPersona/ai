#include "view.h"

context_t view_context;

void init_view_context
(void) {
 
}

void load_view
(view_t* view, string_t file) {
 script_t script;
 object_t object;
 /*
 load_script(&script, file);
 
 compile_script(&script, &view_context, &object);
 
 copy_object(&object, &view->script);
 */
 return;
}

void open_view
(view_t* view, video_t* video) {
 
 if (!view || !video) {
  return;
 }

 view->open(view, video);
 
 return;
}

void process_view
(view_t* view, float time) {

 if (!view) {
  return;
 }
 
 view->process(view, time);
 
 return;
}

void render_view
(view_t* view, video_t* video, view_port_t* port) {
 
 if (!view || !video || !port) {
  return;
 }
 
 view->render(view, video, port);
 
 return;
}
