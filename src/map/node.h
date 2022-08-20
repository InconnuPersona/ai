#pragma once

#include "eco.h"

namespace map {
	enum node_e {
		NODE_NONE = 0,
		NODE_STAR = 1,
		NODE_LAND = 2, // Planet, layers of planet, binary planets, or moons.
		NODE_PROV = 3,
	};

	struct node_s {
		const node_e level;

		HAS_ID(short);

		//int col;
		//vec2 pos, rot;
		//float text_scale;

		id_t parent;

		//eco::eco_s::id_t eco;

		node_s(node_e level = NODE_NONE);

		//virtual 
	};

	struct addr_s {
		node_s::id_t star;
		node_s::id_t land;
		node_s::id_t prov;
	};

}
