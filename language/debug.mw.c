/* automatically compiled on 2012-02-25T15:13:03+01:00 */

#include <assert.h>
#include <stdio.h>

//Class Hierarchy
typedef struct {
	const char * name;
} class_t;
class_t class_class = (class_t){"class"};

int showClass(void * obj)
{
	assert(obj != NULL && "trying to showClass on NULL");
	printf("class %s\n", (*(class_t **)obj)->name);
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
class_t class_Int = (class_t){"Int"};
typedef struct {
	class_t * isa; /* = &class_Int */
	int x, y;
} Int_t;

//def.type
class_t class_Vector = (class_t){"Vector"};
typedef struct {
	class_t * isa; /* = &class_Vector */
	int x, y;
} Vector_t;

//def.func
void func_main()
{
	//expr.var;
	Int_t s4_a;
	s4_a.isa = &class_Int;
	s4_a;
	//expr.call;
	int _tmp0 = showClass(&);
	_tmp0;
}

// --- debugging code ---
int main() { func_main(); return 0; }
