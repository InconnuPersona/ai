#pragma once

#include "entity.h"
#include "user.h"

#define MAX_TILE_SLOTS 8

typedef pointer_t slot_t;

typedef struct {
 float height;
 slot_t slots[MAX_TILE_SLOTS];
} tile_t;

typedef struct {
 
} division_map_t;

typedef reference_t terrain_t;

typedef struct {
 terrain_t terrain;
 
} terrain_map_t;

typedef struct {
 tile_t* tiles;
} tile_map_t;

typedef struct {
 entity_p* entities;
} entity_map_t;

typedef struct {
 int width, height;
 
 tile_map_t tilemap;
 division_map_t divisions;
 terrain_map_t terrain;
 entity_map_t entities;
} map_t;

typedef struct
world_s {
 context_t* context;
 user_interface_t* user_interface;
 
 map_t map;
} world_t;

void load_map(world_t* world, char* file);

void load_world(world_t* world, string_t file);
void init_world(world_t* world, user_interface_t* ui);

// generate randomized world
void form_world(world_t* world);

void destroy_world(world_t* world);

void process_present(world_t* world, float time);
