//#include "draw.h"

/*void draw_map() {
 SDL_Rect src, dst;
 
 src.x = src.y = 0;
 src.w = map.w;
 src.h = map.h;
 
 glm::vec2 dim, ofs;
 
 dim = map.to_view((float) map.w, (float) map.h);
 ofs = map.to_view(0, 0);
 
 dst.x = (int) ofs.x;
 dst.y = (int) ofs.y;
 dst.w = (int) (dim.x - ofs.x);
 dst.h = (int) (dim.y - ofs.y);
 
 SDL_RenderCopy(render, map.nodemap, &src, &dst);
 
 /*for (link_s& link : map.links) {
  switch (link.type) {
  case LINK_LAND:
   setcolor(255, 255, 255);
   
   line(map.nodes[link.n0].pos, map.nodes[link.n1].pos);
   break;
   
  case LINK_SEA:
   setcolor(255, 255, 255);
   
   dotted_line(map.nodes[link.n0].pos, map.nodes[link.n1].pos, 1);
   break;
   
  default:
   break;
  }
  //
 }*/
 
 /*for (auto& node : nodes.node_bbs) {
  //setcolor(128, 128, 128);
  //fillrect(map.to_view(node.pos) - 5.f, vec2(10));
  
  setcolor(255, 255, 255);
  //fillrect(map.to_view(node.pos) - 4.f, vec2(8));
  
  //setcolor()
  ofs = map.to_view(node.key.min);
  dim = map.to_view(node.key.max);
  
  dim -= ofs;
  
  drawrect(ofs, dim);
 }*//*
 
 for (auto& link : nodes.links) {
  int n0, n1;
  
  n0 = link.n0;
  n1 = link.n1;
  
  //nodes[n1].pos
  
 }
 
}

menu_s menu;

void draw_menu() {
 if (!menu.menu) {
  return;
 }
 
 
}

void draw_init() {
 int w, h;
 
 SDL_Init(SDL_INIT_VIDEO);
 
 window = SDL_CreateWindow(PROJ_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, SDL_WINDOW_SHOWN);
 
 if (!window) {
  ERROR("unable to create window.");
 }
 
 SDL_GetWindowSize(window, &w, &h);
 
 view.dim = vec2(w, h);
 view.off = vec2(0, 0);
 view.scale = 1.f;
 
 render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
 
 if (!render) {
  ERROR("unable to create renderer.");
 }
}

void draw() {
 SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
 SDL_RenderClear(render);
 
 // Calculate map model.
 //map.calc_model();
 
 
 // Draw game in this order.
 //draw_map();
 //draw_sidebar();
 //draw_menu();
 
 SDL_RenderPresent(render);
}*/
