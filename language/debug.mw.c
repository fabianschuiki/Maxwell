/* automatically compiled on 2012-02-25T16:05:32+01:00 */

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

int show(int * a) { printf("%i\n", *a); return 0; }

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
void func_showClass()
{
}

//def.func
void func_main()
{
	//expr.var;
	Type_t s6_t;
	s6_t.isa = &type_Type;
	s6_t;
	//expr.var;
	Int_t s6_a;
	s6_a.isa = &type_Int;
	s6_a;
	//expr.call;
	int _tmp0 = showType(&s6_t);
	_tmp0;
	//expr.call;
	int _tmp1 = showType(&s6_a);
	_tmp1;
}

// --- debugging code ---
int main() { func_main(); return 0; }
