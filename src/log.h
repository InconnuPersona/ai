#pragma once

#include "types.h"

struct log_s {

	void printf(cstring_t& format, ...);

};

extern log_s log;
