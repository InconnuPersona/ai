#pragma once

#include "good.h"

// A population specification.
struct pop_spc_s : public comp_s {
 int spec; // species
 int subs; // subspecies
};

// Population statistics
struct pop_stat_s {
 int killed;
 int born;
 int died;
};

struct pop_out_s {
 int unrest;
 
 int labor;
 
 int births;
 int growth;
};

struct pop_s : ent_s {
 pop_spc_s spec;
 pop_out_s out;
 
 vector_t<idea_s> ideas;
 
 // Count of units.
 long_t count;
 
 
 void tick();
};
