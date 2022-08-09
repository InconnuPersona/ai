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

	struct pop_stat_s {
		//int killed;
		int born;
		int died;

		int unrest;

		int labor;

		int births;
		int growth;
	};
}
