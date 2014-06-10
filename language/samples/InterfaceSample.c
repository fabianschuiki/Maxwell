/* Copyright (c) 2013 Fabian Schuiki */

struct Vector {
	float x;
	float y;
};
struct Complex {
	float r;
	float i;
};

float norm_Vector(struct Vector v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

float norm_Complex(struct Complex c)
{
	return sqrtf(c.r*c.r + c.i*c.i);
}

/* The structure generated from the interface associates a pointer to an object
 * with a dispatch table that may be used on that object. */
struct normable_dtbl;
struct normable {
	void* ptr;
	struct normable_dtbl* dtbl;
};

/* Dispatch table automatically generated for the "normable" interface.
 * Corresponds to what would be a vtable in C++. */
struct normable_dtbl {
	float (*norm) (struct normable arg);
};

float useNorm(struct normable n)
{
	return n.dtbl->norm(n);
}

/* Glue code automatically generated for (1) since dispatching utilizes
 * pointers as function arguments, and the dispatched function uses a value. */
float normable_norm_Vector(struct normable arg)
{
	return norm_Vector(*(struct Vector*)arg.ptr);
}

/* As above, yet for (2). */
float normable_norm_Complex(struct normable arg)
{
	return norm_Complex(*(struct Complex*)arg.ptr);
}

void main()
{
	struct Vector v = ...;
	struct Complex c = ...;

	static const struct normable_dtbl dtbl0 = {normable_norm_Vector /*(1)*/};
	float nv = useNorm((struct normable){&v, &dtbl0});

	static const struct normable_dtbl dtbl1 = {normable_norm_Complex /*(2)*/};
	float nc = useNorm((struct normable){&c, &dtbl1});
}
