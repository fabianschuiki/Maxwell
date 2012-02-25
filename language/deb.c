/* automatically compiled on 2012-02-23T22:03:28+01:00 */

#include <stdio.h>

inline int operator_3D (int * a, int * b) { *a = *b; return *a; }
inline int operator_2B (int * a, int * b) { return *a + *b; }
inline int operator_2A (int * a, int * b) { return *a * *b; }
inline int operator_2F (int * a, int * b) { return *a / *b; }
inline int operator_3D3D (int * a, int * b) { return (*a == *b); }
inline int operator_3C (int * a, int * b) { return *a < *b; }

inline int unary_2D (int * a) { return -*a; }

int show(int * a) { printf("%i\n", *a); return 0; }

// --- runtime end ---

// --- debugging code ---
void main() { func_main(); }
