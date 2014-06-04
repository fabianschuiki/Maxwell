/* Copyright © 2013 Fabian Schuiki */

/* Specialized and compiled for T=Int. Memory is a special builtin type that
 * allocates a memory region and prefixes it with a reference counter (if
 * needed), as well as the region's length in elements. */
struct Memory_Int {
	int size;
	atomic_t rc;
	int mem[];
};

struct Memory_Int* make_Int_Memory_Int(int size)
{
	struct Memory_Int* i;
	i = malloc(sizeof(struct Memory_Int) + sizeof(int) * size);
	i->size = size;
	i->rc = 1;
	return i;
}

/* Specialized and compiled for T=Int. */
struct VectorArray_Int {
	atomic_t rc;
	struct Memory_Int* data;
	int size;
};

struct VectorArray_Int* make_VectorArray_Int()
{
	return make_Int_VectorArray_Int(2);
}

struct VectorArray_Int* make_Int_VectorArray_Int(int capacity)
{
	struct VectorArray_Int* a;
	a = malloc(sizeof(struct VectorArray_Int));
	a->size = 0;
	a->data = make_Int_Memory_Int(capacity);
	a->rc++;
	return a;
}

struct VectorArray_Int* make_ConstArray_Int_VectorArray_Int(struct ConstArray_Int* c)
{
	struct VectorArray_Int* a;
	a = make_Int_VectorArray_Int(c->length);
	int i;
	for (i = 0; i < c->length; i++) {
		a->data->mem[i] = c->elements[i];
	}
}

int op_subscript_VectorArray_Int_Int(struct VectorArray_Int* a, int index)
{
	int e;
	e = a->data->mem[index];
	return e;
}

VectorArray_Int* op_subscript_VectorArray_Int_Int_Int_VectorArray_Int(struct VectorArray_Int* a, int index, int v)
{
	a->data->mem[index] = v;
	struct VectorArray_Int* b = a;
	return b;
}

void add_VectorArray_Int_Int(struct VectorArray_Int* a, int v)
{
	if (a->size + 1 > a->data->size)
		grow_VectorArray_Int(a);
	a->data->mem[a->size] = v;
	a->size++;
}

void resize_VectorArray_Int_Int(struct VectorArray_Int* a, int capacity)
{
	struct Memory_Int* d = a->data;
	a->data = make_Int_Memory_Int(capacity);
	int l;
	if (d->size < a->size) {
		l = d->size;
	} else {
		l = a->size;
	}
	int i;
	for (i = 0; i < l; i++) {
		a->data->mem[i] = d->mem[i];
	}
}

void grow_VectorArray_Int(struct VectorArray_Int* a)
{
	resize_VectorArray_Int_Int(a, a->data->size * 2);
}

void clear_VectorArray_Int(struct VectorArray_Int* a)
{
	a->size = 0;
}

/* Specialized and compiled for @a = VectorArray[Int]. Proper declaration order
 * is problematic here. Somehow types need to be declared at the beginning of
 * each source file. */
struct VectorArrayIterator_Int {
	VectorArray_Int* a;
	int i;
};

struct VectorArrayIterator_Int begin_VectorArray_Int_VectorArrayIterator_Int(struct VectorArray_Int* a)
{
	struct VectorArrayIterator_Int i;
	i.a = a;
	i.i = 0;
	return i;
}

void next_VectorArrayIterator_Int(struct VectorArrayIterator_Int* i)
{
	i->i += 1;
}

void get_VectorArrayIterator_Int_Int(struct VectorArrayIterator_Int i)
{
	return i->a->data->mem[i->i];
}

void end_VectorArrayIterator_Int_Bool(struct VectorArrayIterator_Int i)
{
	return i->i >= i->a->size;
}

void main()
{
	struct ConstArray_Int3 tmp0 = {3, {0, 1, 2}};
	struct VectorArray_Int* a;
	a = make_ConstArray_Int_VectorArray_Int(tmp0);
	add_VectorArray_Int_Int(a, 3);

	struct VectorArrayIterator_Int i;
	for (i = begin_VectorArray_Int_VectorArrayIterator_Int(a); !end_VectorArrayIterator_Int_Bool(i); next_VectorArrayIterator_Int(&i)) {
		int b = get_VectorArrayIterator_Int_Int(i);
	}
}