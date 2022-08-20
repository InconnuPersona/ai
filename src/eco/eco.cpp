#include "eco.h"

using namespace eco;

void eco_tick::operator()(const tbb::blocked_range<size_t>& r) {
	for (size_t i = r.begin(); i != r.end(); i++) {

	}
}
