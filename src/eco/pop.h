#pragma once

#include "good.h"
#include "map/node.h"
#include "simd.h"

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

	struct pop_spec_s {
		pop_species_s::id_t species;
		
		tuplemap_t<pop_ethnic_s::id_t, int> ethnic;


	};

	struct pop_s {
		HAS_ID(int);

		pop_spec_s spec;

		map::node_s::id_t loc;

		// Coherence is how likely the pop is to follow the leader of their eco.
		float coh;
		
		// Belligerance.
		float mil;
		
		// 
		
		
	};

	

	// 
	struct pop_vector_s {
		//simd64_u total;
		//simd64_u elder;
		//simd64_u grown;
		//simd64_u nurse;
		//simd64_u young;
	};
}
