/* automatically compiled on 2012-02-29T09:38:48+01:00 */

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
void func_test__Int_ (Int_t* a)
{
}

//def.func
void func_test__Vector_ (Vector_t* a)
{
}

//def.func
void func_main__ ()
{
	//expr.var;
	Int_t s10_a;
	s10_a.isa = &type_Int;
	s10_a;
	//expr.var;
	Vector_t s10_b;
	s10_b.isa = &type_Vector;
	s10_b;
	//expr.call;
	func_test__Int_(&s10_a);
	;
	//expr.call;
	func_test__Vector_(&s10_b);
	;
}

// --- debugging code ---
int main() { func_main__(); return 0; }
