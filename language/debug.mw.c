/* automatically compiled on 2012-03-05T10:53:50+01:00 */

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

//Definition of function cast
typedef struct {
	A_t* a;
} func_cast_t;
func_cast_t func_cast ( i)
{
	
}

//Definition of function cast
typedef struct {
	 i;
} func_cast_1_t;
func_cast_1_t func_cast_1 (A_t* a)
{
	
}

//Definition of function cast
typedef struct {
	B_t* b;
} func_cast_2_t;
func_cast_2_t func_cast_2 (A_t* a)
{
	
}

//Definition of function cast
typedef struct {
	A_t* a;
} func_cast_3_t;
func_cast_3_t func_cast_3 (B_t* b)
{
	
}

//Definition of function show
void func_show ( a,  b)
{
	
}

//Definition of function main
void func_main ()
{
	A_t* s25_z;
	int_t s25_x = 35;
	int_t s25_a = s25_x;
	A_t* s25_b = s25_a;
	printf("a = %i\n", (int)*&s25_a);
}

// --- debugging code ---
int main() { func_main(); return 0; }
