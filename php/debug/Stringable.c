enum hello_arg0 {
	hello_arg0_A = 0,
	hello_arg0_int = 1
};

enum hello_arg1 {
	hello_arg1_int = 0,
	hello_arg1_B = 1
};

struct Foo_intf {
	enum hello_arg0 ha0;
};
struct Bar_intf {
	enum hello_arg1 ha1;
}

hello_func hello_dtable[2][2];
hello_dtable[hello_arg0_A][hello_arg1_int] = &hello1;
hello_dtable[hello_arg0_int][hello_arg1_B] = &hello2;
hello_dtable[hello_arg0_A][hello_arg1_B] = &hello3;
// rest: hello_dtable[...][...] = NULL;

inline void hello (enum hello_arg0 a0, void *arg0, enum hello_arg1, void *arg1)
{
	hello_dtable[a0][a1] (arg0, arg1);
}

void hello_1 (struct A *x, int *y) {}
void hello_2 (int *x, struct B *y) {}
void hello_3 (struct A *x, struct B *y) {}

void world (struct Foo_intf *f, struct Bar_intf *b)
{
	hello_dispatch(f->ha0, f, b->ha1, b);
}