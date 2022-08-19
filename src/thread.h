#pragma once

#include "base.h"

struct thread_s {

	static void sleep(double time);
	static void yield();
};

// Time shall always be counted in milliseconds.
struct watch_s {
	long_t last_sync;


	//long_t

	double time();

	double elapsed();

	void sync();

	watch_s& operator+=(double time);
};
