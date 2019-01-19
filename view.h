#pragma once

#include "ns/object.h"
#include "video.h"

typedef struct
view_element_s {
 MAKE_LINK(view_element);
 
 string_t label;
 object_t object;
 
 struct view_element_s* parent;
 struct view_element_s* elements;
 
 void (*open)(struct view_element_s* this, video_t* video);
 void (*close)(struct view_element_s* this, video_t* video);
 void (*process)(struct view_element_s* this, float time);
 void (*render)(struct view_element_s* this, video_t* video, view_port_t* port);
} view_element_t;

typedef view_element_t view_t;

void init_view_context();

void load_view(view_t* view, string_t file);

void open_view(view_t* view, video_t* video);
void process_view(view_t* view, float time);
void render_view(view_t* view, video_t* video, view_port_t* port);
void close_view(view_t* view);
