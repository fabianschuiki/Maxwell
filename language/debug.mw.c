/* automatically compiled on 2012-02-17T19:54:58+01:00 */

#include <stdio.h>

inline int operator_3D (int * a, int * b) { *a = *b; return *a; }
inline int operator_2B (int * a, int * b) { return *a + *b; }
inline int operator_2A (int * a, int * b) { return *a * *b; }
inline int operator_2F (int * a, int * b) { return *a / *b; }
inline int operator_3D3D (int * a, int * b) { return (*a == *b); }
inline int operator_3C (int * a, int * b) { return *a < *b; }
int show(int * a) { printf("%i\n", *a); return 0; }

// --- runtime end ---

//def.func

void func_main()
{
	//expr.var;
	int _tmp0 = 0;
	int va = _tmp0;
	va;
	//stmt.for;
	int _tmp1 = 0;
	int vi = _tmp1;
	vi;
	do {
		int _tmp2 = 3;
		int _tmp3 = operator_3C(&vi, &_tmp2);
		if (!_tmp3)
			break;
		{
			//expr.var;
			int _tmp4 = operator_2B(&va, &vi);
			int vtx = _tmp4;
			vtx;
			//expr.call;
			int _tmp5 = operator_3D(&va, &vtx);
			_tmp5;
		}
		int _tmp6 = 1;
		int _tmp7 = operator_2B(&vi, &_tmp6);
		int _tmp8 = operator_3D(&vi, &_tmp7);
		_tmp8;
	} while(1);
	//expr.call;
	int _tmp9 = show(&va);
	_tmp9;
}

// --- debugging code ---
void main() { func_main(); }
