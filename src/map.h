#pragma once

#include "eco.h"

// The root node is 0.
struct nodemap_s {
 
 
 vector_t<link_s> links;
 
 tuplemap_t<aabb_s, node_s::id_t> node_bbs;
 
 vector_t<node_s> nodes;
 
 multimap_t<node_s::id_t, node_s::id_t> node_held;
 
 int* tiles;
 int w, h;
 
 void gen_nodes(int* data, int w, int h);
 
 int by_id(int id);
 int by_color(int color);
 
 // Tick process
 
 // Consume resources for pops and holdings.
 //void eat_res();
 
 // generate resources. Pop labor, etc.
 //void gen_res();
 
 
 node_s& operator[](size_t i);
 
 void print_nodes();
};

struct map_s {
 // Map scalable dimensions. All submaps are
 // a factor of these.
 int w, h;
 
 // A counter of the last used dynamic tag number.
 int last_dyntag;
 
 // Modelview matrix.
 mat4 model;
 
 vector_t<good_s> goods;
 //vector_t<owner_s> owners;
 
 texture_t nodemap;
 texture_t terrain;
 
 void load_good(line_s& line);
 void load_node(line_s& line);
 void load_link(line_s& line);
 void load_tag(line_s& line);
 
 int by_tag(tag_s tag);
 
 void calc_model();
 
 node_s& get_node(int id);
 //owner_s& get_owner(tag_s tag);
 
 bool tag_alive(tag_s tag);
 
 vec2 to_view(vec2 pos);
 vec2 to_view(float x, float y);
 
 // Load game files.
 void init();
 
 // Load save file.
 void load(string_t path);
};

extern map_s map;
extern nodemap_s nodes;
