#include "land.h"

#include "delaunator.hpp"

using namespace map;

void make_sphere() {

}

land_s::land_s(land_e type) : node_s(NODE_LAND), type(type) {


}

/*void land_gen::push_cartesian(vector_t<double>& out, float lat, float lon) {
	// Convert from degrees to radians.
	lat = lat / 180.f * M_PI;
	lon = lon / 180.f * M_PI;

	out.push_back(cos(lat) * cos(lon));
	out.push_back(cos(lat) * sin(lon));
	out.push_back(sin(lat));
}*/
