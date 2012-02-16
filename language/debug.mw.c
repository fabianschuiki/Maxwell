/* automatically compiled on 2012-02-16T14:07:50+01:00 */

#include <stdio.h>

inline int operator_3D (int * a, int * b) { *a = *b; return *a; }
inline int operator_2B (int * a, int * b) { return *a + *b; }
inline int operator_2A (int * a, int * b) { return *a * *b; }
inline int operator_2F (int * a, int * b) { return *a / *b; }
inline int operator_3D3D (int * a, int * b) {
	int i, r = 1;
	for (i = 0; i < *b; i++)
		r *= *a;
	return r;
}
int show(int * a) { printf("%i\n", *a); return 0; }

// --- runtime end ---

//def.func

void func_main()
{
	//expr.call;
	int _tmp0 = 15;
	int _tmp1 = 3;
	int _tmp2 = operator_2F(&_tmp0, &_tmp1);
	int _tmp3 = show(&_tmp2);
	_tmp3;
}

// --- debugging code ---
void main() { func_main(); }
