/* Copyright (c) 2013 Fabian Schuiki */

/* This structure is automatically generated due to the use of the string
 * literal (1). Length refers to the length of the string, accounting for the
 * UTF-8 encoding of the string. Size refers to the actual number of bytes used
 * to keep the entire string in memory. */
struct ConstString12 {
	int length;
	int size;
	char bytes[12];
};

/* The ConstStringIterator is shown as a referenced and would most likely not
 * be part of the source file, but rather declared outside. */
struct ConstString {
	int length;
	int size;
	char bytes[]; // this might not properly compile
};
struct ConstStringIterator {
	int i; // character index
	char* c; // current character start
	struct ConstString* s; // string the iterator refers to
};

void main()
{
	/* The string needs to be encoded to UTF-8 in order to declare it properly
	 * in C. */
	struct ConstString12 a = {11, 12, "H\uC3\uA9llo World"}; /* (1) */
	int b = a.length;
	int c = a.size;

	/* Accessing characters by index in a string is an elaborate task, as the
	 * string needs to be iterated character by character. */
	int d = op_index_ConstString_int(&a, 1);

	struct ConstStringIterator tmp0 = ConstStringIterator_new(&a);
	for (; ConstStringIterator_valid(&tmp0); ConstStringIterator_next(&tmp0)) {
		int k = ConstStringIterator_char(&tmp0);
		// intentionally left blank follows here
	}
}
