#pragma once

#include "base.h"

// Decisions

namespace eco {
	enum act_flag_e : int {
		ACT_PERMITTED = FLAG_BIT(0),
		ACT_AUTO_ALLOW = FLAG_BIT(1),
	};

	struct act_i {
		HAS_ID(int);


	};

	struct act_s {
		act_i::id_t act;

		act_flag_e flags;
	};

	// All actions are hardcoded.
	struct act_mng_s {

	};

	struct effect_s {

	};
}
