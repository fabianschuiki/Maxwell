/* Copyright (c) 2013 Fabian Schuiki */

struct Vector {
	float x;
	float y;
};

/* In C, the byref parameter is implemented as a pointer. Note that in most
 * cases, the compiler should inline the assignment function and not call this
 * compiled version of the operator at all. */
struct Vector*
op_assign_Vector_Vector(struct Vector* a, struct Vector b)
{
	a->x = b.x;
	a->y = b.y;
	return a;
}

void main()
{
	Vector a = {0,0};
	Vector b = {1,2};
	op_assign_Vector_Vector(&a, b);
}
