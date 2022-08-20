#include "node.h"

using namespace map;

node_s::node_s(node_e level) : level(level) {

}


/*struct node_base_s {
 
};

//void map_s::node_pass_1() {
// 
//}
//
//void map_s::node_pass_2() {
// 
//}

void calc_nodes() {
 
}

struct nodeline_s {
 int col;
 int beg, end;
};

struct noderow_s {
 std::vector<nodeline_s> lines;
};

struct weight_s {
 int value;
 int area;
 vec2 pos;
 int row;
 int beg, end; // last line.
};

struct nodegen_s {
 int col;
 
 vec2 min, max;
 
 vector_t<nodeline_s> lines;
 
 std::set<int> adj_nodes;
 
 nodegen_s() {
  col = 0;
  min = max = vec2();
 }
 
 nodegen_s(const nodegen_s& gen) {
  col = gen.col;
  min = gen.min;
  max = gen.max;
  
  lines = std::move(lines);
 }
 
 void stretch(int x, int y) {
  min.x = std::min((float) x, min.x);
  min.y = std::min((float) y, min.y);
  max.x = std::max((float) x, max.x);
  max.y = std::max((float) y, max.y);
 }
};

vector_t<nodegen_s> node_gens;

void nodemap_s::gen_nodes(int* data, int w, int h) {
 vector_t<noderow_s> rows;
 vector_t<weight_s> weights;
 
 nodegen_s gen;
 
 nodeline_s line;
 noderow_s row;
 int color;
 int i, j;
 int node;
 int m, r, s, x, y;
 
 node_gens.clear();
 
 // Collect node lines into rows and generate bounds.
 for (i = 0; i < w * h; i++) {
  color = data[i] & 0x00ffffff;
  
  if (!color) {
   continue;
  }
  
  line.beg = i;
  
  while ((i % w != 0) && ((data[i + 1] & 0x00ffffff) == color)) {
   i++;
  }
  
  line.col = color;
  line.end = i + 1;
  
  //printf("line: [0x%x] %i, %i\n", line.col, line.beg, line.end);
  
  for (j = 0; j < (int) node_gens.size(); j++) {
   if (node_gens[j].col == line.col) {
	break;
   }
  }
  
  if (j == (int) node_gens.size()) {
   gen.col = line.col;
   gen.max = vec2((int) (line.end % w), (int) (line.end / w) + 1);
   gen.min = vec2((int) (line.beg % w), (int) (line.beg / w));
   
   //printf("gen: [0x%x] (%f, %f)-(%f, %f)\n", gen.col, gen.min.x, gen.min.y, gen.max.x, gen.max.y);
   
   node_gens.push_back(gen);
   
   node_gens[j].lines.push_back(line);
  }
  else {
   node_gens[j].stretch(line.beg % w, line.beg / w + 1);
   node_gens[j].stretch(line.end % w, line.end / w + 1);
   
   node_gens[j].lines.push_back(line);
  }
  
  if ((i + 1) % w != 0) {
   color = data[i + 1] & 0x00ffffff;
   
   if (color) {
	node_gens[j].adj_nodes.insert(color);
   }
  }
 }
 
 for (i = 0; i < (int) node_gens.size(); i++) {
  node = by_color(node_gens[i].col);
  
  if (node == -1) {
   //printf("node not specified in map file found, [0x%x]\n", node_gens[i].col);
   continue;
  }
  
  //////////////////////////////
  // Generate weights.
  
  weights.clear();
  
  x = y = 0;
  
  
  /*for (auto& line : node_gens[i].lines) {
   r = line.end - line.beg;
   
   x = line.beg % w + r;
   x /= 2;
   
   y = line.beg / w;
   
   if (weights.empty()) {
	weights.push_back((weight_s) { r, r, vec2(x, y), y, line.beg, line.end });
   }
   else {
	for (auto it = weights.begin(); it != weights.end(); it++) {
	 if (it->row == y - 1) {
	  // Find the overlapping range.
	  s = std::max(0, std::min(line.end, it->end) - std::max(line.beg, it->beg) + 1);
	  
	  if (s > 0) {
	   m = r + s + it->value;
	   r += it->area;
	   
	   float l1, l2;
	   
	   l1 = (it->end - it->beg) / m;
	   l2 = (line.end - line.beg) / m;
	   
	   weights.erase(it);
	  }
	 }
	}
	
   }
   
   if (!nodes[node].pos) {
	nodes[node].pos = vec2(x, y);
   }
   else {
	nodes[node].pos += 
   }
  }*//*
  
  for (int c : node_gens[i].adj_nodes) {
   printf("node 0x%x touches 0x%x.\n", node_gens[i].col, c);
   
   // Add links.
  }
  
  node_bbs.push_back({ node_gens[i].min, node_gens[i].max });
 }
 
 tiles = data;
 this->w = w;
 this->h = h;
}

int nodemap_s::by_id(int id) {
 size_t i;
 
 for (i = 0; i < nodes.size(); i++) {
  if (nodes[i].id == id) {
   return (int) i;
  }
 }
 
 return -1;
}

int nodemap_s::by_color(int color) {
 size_t i;
 
 for (i = 0; i < nodes.size(); i++) {
  if (nodes[i].col == color) {
   return (int) i;
  }
 }
 
 return -1;
}

node_s& nodemap_s::operator[](size_t i) {
 return nodes[i];
}*/
