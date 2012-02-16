/* automatically compiled on 2012-02-16T13:42:26+01:00 */

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

// --- runtime end ---

void func_main()
{
	int va;
	int _tmp0 = 1;
	int _tmp1 = operator_3D(&va, &_tmp0);
	_tmp1;
	int vb;
	int _tmp2 = 19;
	int _tmp3 = operator_3D(&vb, &_tmp2);
	_tmp3;
	int vx;
	int _tmp4 = operator_2B(&va, &vb);
	int _tmp5 = operator_3D(&vx, &_tmp4);
	_tmp5;
	int _tmp6 = 3;
	int _tmp7 = 2;
	int _tmp8 = operator_3D3D(&_tmp6, &_tmp7);
	int _tmp9 = show(&_tmp8);
	_tmp9;
}

// --- debugging code ---
void main() { func_main(); }
