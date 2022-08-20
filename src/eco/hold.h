#pragma once

#include "base.h"

namespace eco {
	enum hold_e {
		HOLD_HARVEST,
		HOLD_CRAFT,
		HOLD_TRAIN,
	};
	
	// Input factors of a holding.
	struct hold_in_s {

	};

	struct hold_s : comp_s {
		hold_e type;

		string_t& get_name();
	};
}
