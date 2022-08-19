#include "thread.h"

#include <chrono>
#include <thread>

// This sets the basis of all time measurements to the
// time of program initialization. It is done to reduce
// the floating point rounding error if trying to base
// the time off of epoch time or an absolute system time.
std::chrono::system_clock::time_point time_base = std::chrono::system_clock::now();

void thread_s::sleep(double time) {
	std::this_thread::sleep_for(std::chrono::nanoseconds((long_t) (time * 1000000)));
}

void thread_s::yield() {
	std::this_thread::yield();
}

double watch_s::time() {
	long_t nano;

	nano = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time_base).count();

	return (double) nano / 1000000;
}

double watch_s::elapsed() {
	return time() - last_sync;
}

void watch_s::sync() {
	last_sync = time();
}

watch_s& watch_s::operator+=(double time) {
	last_sync += (long_t) (time * 1000000);

	return *this;
}
