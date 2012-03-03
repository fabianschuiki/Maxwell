/* automatically compiled on 2012-03-03T11:16:22+01:00 */

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

//Builtin Types
typedef u_int8_t  uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
typedef float     float32_t;
typedef double    float64_t;

//Native Types (depends on machine bus width)
typedef int64_t   int_t;
typedef uint64_t  uint_t;
typedef float64_t double_t;

//Class Hierarchy
typedef struct Type_t {
	struct Type_t * isa;
	const char * name;
} Type_t;
#define type_make(t) (Type_t){&type_Type, t}
Type_t type_Type = type_make("Type");
// --- runtime end ---

//definition of type A
Type_t type_A = type_make("A");
typedef struct {
	Type_t * isa /* = &type_A*/;
} A_t;

//definition of type B
Type_t type_B = type_make("B");
typedef struct {
	Type_t * isa /* = &type_B*/;
} B_t;

//Definition of function test
void func_test (A_t* x)
{
	
}

//Definition of function cast
typedef struct {
	A_t* r;
} func_cast_t;
func_cast_t func_cast (B_t* x)
{
	
}

//definition of type Vector
Type_t type_Vector = type_make("Vector");
typedef struct {
	Type_t * isa /* = &type_Vector*/;
} Vector_t;

//Definition of function main
void func_main ()
{
	A_t* s12_a;
	B_t* s12_b;
	func_test(s12_a);
	func_test(func_cast(s12_b).r);
	int16_t s12_ix = 1;
	int16_t s12_iy = 2;
	int16_t s12_iz = (s12_ix + s12_iy);
	printf("iz = %i\n", (int)*&s12_iz);
}

// --- debugging code ---
int main() { func_main(); return 0; }
