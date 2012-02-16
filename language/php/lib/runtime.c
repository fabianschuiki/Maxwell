#include <stdio.h>

inline int operator_3D (int * a, int * b) { *a = *b; return *a; }
inline int operator_2B (int * a, int * b) { return *a + *b; }
inline int operator_2A (int * a, int * b) { return *a * *b; }
inline int operator_3D3D (int * a, int * b) {
	int i, r = 1;
	for (i = 0; i < *b; i++)
		r *= *a;
	return r;
}
int show(int * a) { printf("%i\n", *a); return 0; }
