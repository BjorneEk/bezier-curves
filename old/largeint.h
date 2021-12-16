#pragma once


typedef union _LARGE_INTEGER {
	struct {
		unsigned long LowPart;
		long  HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		unsigned long LowPart;
		long  HighPart;
	} u;
	long long QuadPart;
} LARGE_INTEGER;
