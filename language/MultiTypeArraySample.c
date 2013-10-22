/* Copyright © 2013 Fabian Schuiki */

/* Union type automatically generated by (1). Note that String is a value in
 * Maxwell and is therefore no pointer in C. The actual data contained within
 * the string is stored in a buffer in the background, opaque to the user. */
struct union_Int_Real_String {
	char a;
	union {
		int asInt;
		float asReal;
		struct String asString;
	};
};

/* Constant array type automatically generated by (1). Note that the naming
 * could still be improved. */
struct ConstArray_union_Int_Real_String3 {
	int length;
	union_Int_Real_String elements[3];
};

void main()
{
	/* Constant string literals have not yet been specified, so here's a
	 * dummy. */
	struct String tmp0 = somehowDerivedFrom("hello");

	/* The initialization uses C99 designated initialization syntax for the
	 * union members. A few modifications to the compiler should allow it to
	 * produce C89 code as well. */
	struct ConstArray_union_Int_Real_String3 a = {3, {
		{0, .asInt = 0},
		{1, .asReal = 1.2},
		{2, .asString = tmp0}
	}}; /* (1) */

	/* The actual name of the cast is abbreviated, but would be something like
	 * cast_ConstArray_union_Int_Real_String_ArrayVector_union_Int_Real_String. */
	struct ArrayVector_union_Int_Real_String* b = cast_etc(&a);

	/* The function names tend to explode in complexity as soon as the type
	 * specialization is encoded in the name. Maybe we need to find a better
	 * solution to this, even if it is indexing and similar things. */
	struct union_Int_Real_String tmp1 = {0, .asInt = 1};
	add_ArrayVector_union_Int_Real_String_union_Int_Real_String(b, tmp1);

	/* The actual name of the operator function is abbreviated, but would be
	 * op_index_ArrayVector_union_Int_Real_String_Int. */
	struct union_Int_Real_String c = op_index_ArrayVector_etc_Int(b, 3);
}