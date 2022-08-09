#pragma once

//#include "map/node.h"

#include "pop.h"

// taxes gov idea is established once 

namespace eco {
	struct pop_s;

	struct eco_s : comp_s {
		pile_s stock;
		pile_s demand;

		pop_stat_s stats;

		//hold_s::id_t;

		//vector_t<idea_s> ideas;

		//vector_t<hold_s::id_t> holds;
		//vector_t<pop_s> pops;

	};

	/*struct eco_ai {


		eco_ai(eco_s* eco) {
		}

		operator()(const blocked_range<size_t>& r) {
		}
	};*/
}

// Economy




// parallel_for(blocked_range<size_t>(0, n), eco_ai(eco));
