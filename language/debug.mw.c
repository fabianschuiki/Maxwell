/* automatically compiled on 2012-02-25T17:35:46+01:00 */

#include <assert.h>
#include <stdio.h>

//Class Hierarchy
typedef struct Type_t {
	struct Type_t * isa;
	const char * name;
} Type_t;
#define type_make(t) (Type_t){&type_Type, t}
Type_t type_Type = type_make("Type");

int showType(void * obj)
{
	assert(obj != NULL && "trying to showType on NULL");
	printf("@%s\n", (*(Type_t **)obj)->name);
	return 0;
}

inline int operator_3D (int * a, int * b) { *a = *b; return *a; }
inline int operator_2B (int * a, int * b) { return *a + *b; }
inline int operator_2A (int * a, int * b) { return *a * *b; }
inline int operator_2F (int * a, int * b) { return *a / *b; }
inline int operator_3D3D (int * a, int * b) { return (*a == *b); }
inline int operator_3C (int * a, int * b) { return *a < *b; }


inline int unary_2D (int * a) { return -*a; }

//int show(int * a) { printf("%i\n", *a); return 0; }

//int
typedef struct {
	Type_t * isa;
	int v;
} int_t;
Type_t type_int = type_make("int");

inline int binary_equal(int_t * v, int * a) { v->v = *a; return 0; }

int show(int_t * i) { printf("%i\n", i->v); return 0; }

// --- runtime end ---


//def.type
Type_t type_Int = type_make("Int");
typedef struct {
	Type_t * isa; /* = &type_Int */
	int x, y;
} Int_t;

//def.type
Type_t type_Vector = type_make("Vector");
typedef struct {
	Type_t * isa; /* = &type_Vector */
	int x, y;
} Vector_t;

//def.func
void func_main()
{
	//expr.var;
	int_t s4_a;
	s4_a.isa = &type_int;
	s4_a;
	//expr.call;
	int _tmp0 = 5;
	int _tmp1 = binary_equal(&s4_a, &_tmp0);
	_tmp1;
	//expr.call;
	int _tmp2 = show(&s4_a);
	_tmp2;
}

// --- debugging code ---
int main() { func_main(); return 0; }
