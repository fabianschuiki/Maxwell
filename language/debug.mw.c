/* automatically compiled on 2012-02-19T21:00:29+01:00 */

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
	int _tmp0 = 1;
	int _tmp1 = unary_2D(&_tmp0);
	int va = _tmp1;
	va;
	//stmt.for;
	int _tmp2 = 0;
	int vi = _tmp2;
	vi;
	do {
		int _tmp3 = 3;
		int _tmp4 = operator_3C(&vi, &_tmp3);
		if (!_tmp4)
			break;
		{
			//expr.var;
			int _tmp5 = operator_2B(&va, &vi);
			int vtx = _tmp5;
			vtx;
			//expr.call;
			int _tmp6 = operator_3D(&va, &vtx);
			_tmp6;
		}
		int _tmp7 = 1;
		int _tmp8 = operator_2B(&vi, &_tmp7);
		int _tmp9 = operator_3D(&vi, &_tmp8);
		_tmp9;
	} while(1);
	//expr.call;
	int _tmp10 = show(&va);
	_tmp10;
}

// --- debugging code ---
void main() { func_main(); }
