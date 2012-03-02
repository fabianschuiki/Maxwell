/* automatically compiled on 2012-03-02T18:12:18+01:00 */

#include <assert.h>
#include <stdio.h>

//Class Hierarchy
typedef struct Type_t {
	struct Type_t * isa;
	const char * name;
} Type_t;
#define type_make(t) (Type_t){&type_Type, t}
Type_t type_Type = type_make("Type");

// --- runtime end ---


//def.type
Type_t type_int = type_make("int");
typedef struct {
	Type_t * isa; /* = &type_int */
	int x, y;
} int_t;

//def.func
typedef struct {
	int_t* r;
} func_2b_t;
func_2b_t func_2b (int_t* a, int_t* b)
{
}

//def.func
void func_main ()
{
	//expr.var;
	int_t s8_x;
	s8_x.isa = &type_int;
	s8_x;
	//expr.var;
	int_t s8_y;
	s8_y.isa = &type_int;
	s8_y;
	//expr.var;
	func_2b_t _tmp0 = func_2b(&s8_x, &s8_y);
	int_t s8_z = _tmp0;
	s8_z.isa = &type_int;
	s8_z;
}

// --- debugging code ---
int main() { func_main__(); return 0; }
