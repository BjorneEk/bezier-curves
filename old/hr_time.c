//#include <windows.h>

#ifndef hr_timer
#include "hr_time.h"
#define hr_timer
#endif

void start_timer(stop_watch *timer) {
	QueryPerformanceCounter(&timer->start);
}

void stop_timer(stop_watch *timer) {
	QueryPerformanceCounter(&timer->stop);
}

double LIToSecs(LARGE_INTEGER * L) {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return ((double)L->QuadPart / (double)frequency.QuadPart);
}
double get_elapsed_time(stop_watch *timer) {
	LARGE_INTEGER time;
	time.QuadPart = timer->stop.QuadPart - timer->start.QuadPart;
	return LIToSecs(&time);
}
