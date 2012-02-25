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
