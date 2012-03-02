/* automatically compiled on 2012-03-03T00:35:53+01:00 */

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

//Definition of function main
void func_main ()
{
	A_t* s11_a;
	B_t* s11_b;
	func_test(s11_a);
	func_test(func_cast(s11_b).r);
	int_t s11_ix = 1;
	int_t s11_iy = 2;
	int_t s11_iz = (s11_ix + s11_iy);
}

// --- debugging code ---
int main() { func_main(); return 0; }
