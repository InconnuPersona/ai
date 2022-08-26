#pragma once

#include "eco/action.h"

#define DEFINE_ACT(Name) struct Name##Act : eco::act_i

// Event decision.
DEFINE_ACT(RulerDecision) {
	int choice;
};

// The decision of whether a pop or org will rebel.
DEFINE_ACT(Rebel) {
	enum {
		REBEL_ECO_CHANGE,
		REBEL_IDEA_AXIS, // Rebels supporting a specific axis direction.
		REBEL_DEFECT, // Seek to join another state.
		REBEL_FREEDOM, // Seek to establish new state.

	};

	//ACT_PREREQ()
};

DEFINE_ACT(EthnicSplit) {
	float ETHNIC_SPLIT_THRESHHOLD = 0.5f;
};

DEFINE_ACT(ExpandEco) {
	
}
