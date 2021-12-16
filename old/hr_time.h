#pragma once
//#include <windows.h>
//#include "bigint.h"
#include "largeint.h"

typedef struct {
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stop_watch;

void start_timer(stop_watch *timer);
void stop_timer(stop_watch *timer);
double LIToSecs(LARGE_INTEGER * L);
double get_elapsed_time(stop_watch *timer);
