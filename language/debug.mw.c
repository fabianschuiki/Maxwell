/* automatically compiled on 2012-03-02T23:04:48+01:00 */

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

//definition of type object
Type_t type_object = type_make("object");
typedef struct {
	Type_t * isa /* = &type_object*/;
} object_t;

//definition of type scalar
Type_t type_scalar = type_make("scalar");
typedef struct {
	Type_t * isa /* = &type_scalar*/;
} scalar_t;

//definition of type primit
Type_t type_primit = type_make("primit");
typedef struct {
	Type_t * isa /* = &type_primit*/;
} primit_t;

//Definition of function +
typedef struct {
	object_t* r;
} func_2b_t;
func_2b_t func_2b (object_t* a, object_t* b)
{
	
}

//Definition of function +
typedef struct {
	scalar_t* r;
} func_2b_1_t;
func_2b_1_t func_2b_1 (scalar_t* a, scalar_t* b)
{
	
}

//Definition of function +
typedef struct {
	primit_t r;
} func_2b_2_t;
func_2b_2_t func_2b_2 (primit_t a, primit_t b)
{
	
}

//Definition of function main
void func_main ()
{
	object_t* s20_ox;
	object_t* s20_oy;
	object_t* s20_oz = func_2b(s20_ox, s20_oy).r;
	scalar_t s20_sx;
	scalar_t s20_sy;
	scalar_t s20_sz = *func_2b_1(&s20_sx, &s20_sy).r;
	primit_t s20_px;
	primit_t s20_py;
	primit_t s20_pz = func_2b_2(s20_px, s20_py).r;
	int_t s20_ix = 1;
	int_t s20_iy = 2;
	int_t s20_iz = (s20_ix + s20_iy);
}

// --- debugging code ---
int main() { func_main(); return 0; }
