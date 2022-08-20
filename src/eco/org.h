#pragma once

#include "idea.h"

namespace eco {
	struct org_i {
		HAS_ID(int);


	};

	// Organizations, banks, governments, tribes, etc.
	struct org_s : ent_s {
		org_i::id_t type;
		HAS_ID(int);

		vector_t<act_i::id_t> permitted;
	};
}


