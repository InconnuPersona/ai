#include "log.h"

#include <stdarg.h>

void log_s::printf(cstring_t& format, ...) {
	va_list args;

	va_start(args, format);

	va_end(args);
}
