#pragma once

#include "eco/action.h"

// Event decision.
struct Decision : eco::act_i {
	int choice;
};

// The decision of whether a pop or org will rebel.
struct Rebel : eco::act_i {
	enum {
		REBEL_ECO_CHANGE,
		REBEL_IDEA_AXIS, // Rebels supporting a specific axis direction.
		REBEL_DEFECT, // Seek to join another state.
		REBEL_FREEDOM, // Seek to establish new state.

	};


};

struct EthnicSplit : eco::act_i {
	float ETHNIC_SPLIT_THRESHHOLD = 0.5f;
};
