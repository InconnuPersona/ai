#pragma once

#include "eco/eco.h"

namespace map {
	struct node_s {
		const int type;

		HAS_ID(int);

		//int col;
		//vec2 pos, rot;
		//float text_scale;

		id_t parent;

		//eco::eco_s::id_t eco;

		//node_s(node_e level = NODE_NONE);

		//virtual 
	};

}
