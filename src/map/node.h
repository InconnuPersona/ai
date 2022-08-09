#pragma once

#include "eco/eco.h"

namespace map {
	enum link_e {
		LINK_ABST = 0, // Abstract link

		LINK_LAND,
		LINK_SEA, // Sea links may join with land nodes.
		LINK_CROSS, // Sea crossing between two unconnected land nodes.
		LINK_CANAL, // Land crossing between two unconnected sea nodes.
	};

	enum node_e {
		NODE_NONE = 0,
		NODE_STAR = 1,
		NODE_LAND = 2, // Planet, layers of planet, binary planets, or moons.
		NODE_PROV = 4,
	};

	struct node_s : public comp_s {
		struct addr_s {
			id_t star;
			id_t land;
			id_t prov;
		};

		node_e level;

		int col;
		vec2 pos, rot;
		//float text_scale;

		id_t parent;

		//eco::eco_s::id_t eco;

	};

	struct link_s : public comp_s {
		link_e type;

		node_s::id_t l, r;

		float len;
	};
}
