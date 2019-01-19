#include "world.h"
#include "ns/script.h"

void load_map
(world_t* world, char* file) {
 //script_t script;
 
 //load_script(&script, file);
 
 //if ()
}

void init_map
(map_t* map) {
}

void load_world
(world_t* world, string_t file) {
 
 world->context = 0;
 world->user_interface = 0;
 
 //init_world();
 
 return;
}

void init_world
(world_t* world, user_interface_t* ui) {
 
 //world->map
 
 world->user_interface = ui;
 
 init_map(&world->map);
 
 return;
}

void process_present
(world_t* world, float time) {
 
 //cout("time: %f", time);
 
 return;
}
