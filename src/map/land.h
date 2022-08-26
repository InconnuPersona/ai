#pragma once

#include "prov.h"
#include "rand.h"

namespace map {

	/*enum link_e {
		LINK_ABST = 0, // Abstract link

		LINK_LAND,
		LINK_SEA, // Sea links may join with land nodes.
		LINK_CROSS, // Sea crossing between two unconnected land nodes.
		LINK_CANAL, // Land crossing between two unconnected sea nodes.
	};

	enum land_e {
		LAND_SPHERE,
		LAND_SQUARE,
	};*/

	struct link_s : public comp_s {
		int type;

		node_s::id_t l, r;

		float len;
	};

	struct land_data_s {

			int w, h;

			image_s tiles;
			//image_s terrain;
			//image_s height;

	};

	struct land_s : node_s {
		//const land_e type;

		date_s date;

		vector_t<link_s> links;
		
		//land_s(land_e type);


	};

	struct land_gen {
		
		land_gen(land_s* lands);

		void push_cartesian(vector_t<double>& out, float lat, float lon);

		void gen_fibonacci_sphere(vector_t<double>& out, int N, float jitter, rand_s rand);

		void make_sphere();

		void add_south_pole();

		/*void gen() {
			vector_t<double> gps_coords;
			vector_t<double> abs_coords;
			int i;

			gen_fibonacci_sphere(gps_coords);

			for (i = 0; i < gps_coords.size() / 2; i++) {
				push_cartesian(abs_coords, gps_coords[i * 2], gps_coords[i * 2 + 1]);
			}

			delaunator::Delaunator delaunay(abs_coords);

			abs_coords.push_back(0);
			abs_coords.push_back(0);
			abs_coords.push_back(1);
			add_south_pole(, delaunay);



		}*/

		//operator()(const blocked_range<size_t>& r);
	};
	
	//parallel_for(blocked_range<size_t>(0, n), land_gen(lands));

}
