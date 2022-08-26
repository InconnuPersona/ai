#pragma once

#include "base.h"

namespace map {
	// An abstract class representing
	struct node_s {
		const int type;

		HAS_ID(int);

		id_t parent;
		vector_t<node_s::id_t> neighbors;

		//vector_t<effect_s> active_effects;

		//int col;
		//vec2 pos, rot;
		//float text_scale;


		//eco::eco_s::id_t eco;

		//node_s(node_e level = NODE_NONE);

		//virtual 
	};

	struct node_mgr_s {

	};
}
