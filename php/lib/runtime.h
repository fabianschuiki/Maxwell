/**
 * Maxwell Runtime Header
 */

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

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
typedef float64_t float_t;

//Class Hierarchy
typedef struct Type_t {
	struct Type_t * isa;
	const char * name;
} Type_t;
#define type_make(t) (Type_t){&type_Type, t}

//Strings
typedef struct {
	Type_t * isa;
	const char * v;
} String_t;

//Runtime external stuff.
extern Type_t type_Type;
extern Type_t type_String;
