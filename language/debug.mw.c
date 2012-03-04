/* automatically compiled on 2012-03-04T20:41:41+01:00 */

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

//Definition of function cast
typedef struct {
	A_t* a;
} func_cast_t;
func_cast_t func_cast ( i)
{
	
}

//Definition of function main
void func_main ()
{
	25;
}

// --- debugging code ---
int main() { func_main(); return 0; }
