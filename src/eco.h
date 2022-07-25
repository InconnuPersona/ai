#pragma once

#include "pop.h"

struct node_s {
 
};

// An entity
struct ent_s {
 typedef int id_t;
 
 id_t id;
 int rank; // population/government class
};

struct pop_s : ent_s {
};

struct gov_s : ent_s {
 
};

// Economy
struct eco_s {
 pile_s stock;
 pile_s demand;
 
 vector_t<idea_s> ideas;
 
 vector_t<pop_s> pops;
 
 void add_goods() {
  
 }
 
};

