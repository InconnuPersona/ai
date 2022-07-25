#pragma once

#include "node.h"

// taxes gov idea is established once 

// Economy
struct eco_s {
 pile_s stock;
 pile_s demand;
 
 hold_s::id_t 
 
 vector_t<idea_s> ideas;
 
 vector_t<hold_s::id_t> holds;
 vector_t<pop_s> pops;
 
 void add_good() {
  
 }
 
};

struct eco_ai {
 
 
 eco_ai(eco_s* eco) {
 }
 
 operator()(const blocked_range<size_t>& r) {
 }
};

// parallel_for(blocked_range<size_t>(0, n), eco_ai(eco));
