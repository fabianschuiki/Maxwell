/* Copyright © 2013 Fabian Schuiki */

/* This structure is automatically generated in the root scope due to the use
 * of the array literal. For constant arrays the length may actually be
 * omitted, since a constant function returning the array's length may be
 * generated in order to implement the constant array interface. */
struct ConstArray_Int3 {
	int length;
	int elements[3];
};

void main()
{
	struct ConstArray_Int3 x = {3, {0, 1, 2}};
	int l = x.length;
	int x0 = x.elements[0];

	int sum = 0;
	int tmp0;
	for (tmp0 = 0; tmp0 < x.length; tmp0++) {
		int a = x.elements[tmp0];
		sum += a;
	}
}