#pragma once

#include "action.h"

namespace eco {

	struct idea_axis_i {
		HAS_ID(int);

		// Whether ideas on the axis will split a pop into separate
		
		// A pop may only adopt one idea from a cardinal axis
		bool cardinal;
	};
	
	struct idea_i {
		HAS_ID(int);

		idea_axis_i::id_t axis;

		struct effect_s {
			id_t idea;
			float value;
		};

	};

	struct idea_axis_align_s {
		idea_axis_i::id_t axis;
		idea_i::id_t idea;

		long_t count;
	};

	struct idea_s {
		idea_i::id_t type;

		
	};


}
