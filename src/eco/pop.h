#pragma once

#include "good.h"

namespace eco {

	struct species_s : comp_s {

		string_t name;

		// portrait


		species_s();



	};

	struct pop_spec_s {
		species_s::id_t species;
	};

	struct pop_s {
		pop_spec_s spec;


		// Count of units.
		long_t count;
 

	};
}
