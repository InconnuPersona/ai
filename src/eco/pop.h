#pragma once

#include "good.h"
#include "map/node.h"

namespace eco {

	// All pops possess an inherent ethnicity, unrelated to
	// the 'ethnic' idea, that determines their portrait.
	// Ethnicities are not visible in the game menus directly,
	// however, a lack of movement between pops in the ethnicity
	// for marriage may result in separate ethnicities to arise,
	// which alters each pops ethnic coherence.
	// Once ethnic coherence goes below , the 

	// Pops lacking ethnic coherence may diverge finally 
	// The decision to do an ethnic split occurs at the
	// eco level

	// If an ethnicity falls below the retention limit
	struct pop_ethnic_s {
		HAS_ID(int);
	};

	// Pop species are much more distinguishable than ethnics,
	// and is the most critical factor of determining what
	// a specific pop needs, produces, or desires. If the
	// gene_mod idea is upgraded to a certain level, then
	// new "half species" may be formed that can accept
	// genetics from 
	struct pop_species_s {
		HAS_ID(int);

		string_t name;
		bool half;

		// portrait

		pop_species_s();



	};

	struct pop_half_species_s : pop_species_s {
		pop_species_s::id_t p0, p1;
	};

	struct pop_spec_s {
		pop_species_s::id_t species;
		
		tuplemap_t<pop_ethnic_s::id_t, int> ethnic;


	};

	struct pop_s {
		HAS_ID(short);

		pop_spec_s spec;

		map::node_s::id_t loc;

		// Coherence is how likely the pop is to follow the 
		float coherence;

		// Total count of population.
		long_t total;
		
		// Represents members of the population that are adults
		// free of childcare that may contribute to the labor
		// of an eco.
		long_t grown;

		// 
		long_t nurse;

		// Offspring of the pop, contribute very little to 
		long_t young;

		// Progeny is the potential offspring produced by each
		// pop per tick that is distributed in their eco. Most
		// progeny is weighted to fall back into the original
		// pop to produce offspring, however, other pops that
		// accept progeny of differing ethnicity will have their
		// ethnic composition altered by the amount of progeny
		// received. This in turn reduces coherence, however,
		// this is a natural part of the game. Over time,
		// ethnic composition will drift towards the larger
		// components
		long_t progeny;
	};
}
