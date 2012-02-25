/* automatically compiled on 2012-02-25T01:38:35+01:00 */

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

//def.func

void func_main()
{
	//expr.var;
	int _tmp0 = 25;
	int vx = _tmp0;
	vx;
	//expr.call;
	int _tmp1 = show(&vx);
	_tmp1;
}

// --- debugging code ---
int main() { func_main(); return 0; }
