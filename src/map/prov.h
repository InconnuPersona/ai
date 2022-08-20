#pragma once

#include "eco/node.h"
//#include "eco/org.h"

namespace map {
	// Terrain
	struct terr_s {



	};

	// Province node
	struct prov_s : public node_s {
		eco::eco_s::id_t eco;

		//org_s::id_t owner;
		//org_s::id_t holder;
	};
}

 //tuplemap_t<terr_s::id_t, float> terrains;
