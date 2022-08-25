#pragma once

//#include "map/node.h"

#include "action.h"
#include "good.h"
#include "idea.h"
#include "org.h"

#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

// taxes gov idea is established once 

namespace eco {
	struct pop_s;

	struct pop_stat_s {
		//int killed;
		int born;
		int died;

		int unrest;

		int labor;

		int births;
		int growth;
	};

	struct labor_s {
		//pop_s::id_t pop;
		long_t count;
	};

	struct eco_s {
		HAS_ID(int);

		pile_s stock;
		pile_s demand;

		ent_s::id_t ruler;

		pop_stat_s stats;

		//tuplemap_t<labor_s, hold_s::id_t> assigned_labor;

		//tuplemap_t < pop_s, node_s::id_t>

		// idea

		//tuplemap_t<pop_s::id_t, idea_axis_align_s> pop_aligns;

		// Classes are determined at the eco level,
		// And determine both the voting power and
		// goods usage order. Higher class pops receive
		// the first larger share of goods before other
		// lower pops receive them.
		// Certain specialties of pops are prohibited from
		// achieving higher classes 

		//simd_t<long_t> pop_grown;
		//simd_t<long_t> pop_young;

		//hold_s::id_t;

		//vector_t<idea_s> ideas;

		//vector_t<hold_s::id_t> holds;
		//vector_t<pop_s> pops;

		//vector_t<dec_s> current_decisions;
	};

	struct eco_tick {
		vector_t<eco_s>& ecos;

		eco_tick(vector_t<eco_s>& ecos);

		void operator()(const tbb::blocked_range<size_t>& r);
	};
}

// Economy




// parallel_for(blocked_range<size_t>(0, n), eco_ai(eco));
