/* Copyright © 2013 Fabian Schuiki */

struct Circle {
	float mx;
	float my;
	float r;
};
struct Rectangle {
	float x0;
	float y0;
	float x1;
	float y1;
};

bool collide_Circle_Circle(struct Circle a, struct Circle b) { ... }
bool collide_Circle_Rectangle(struct Circle a, struct Rectangle b) { ... }

/* Union structure generated by the variable definition inside main(). */
struct union_Circle_Rectangle {
	char a;
	union {
		Circle asCircle;
		Rectangle asRectangle;
	};
}

/* Dispatch function automatically generated by the call to collide with a
 * dispatchable union type. */
inline bool collide_dispatch0(struct Circle a, struct union_Circle_Rectangle b)
{
	switch (b.a) {
		case 0: return collide_Circle_Circle(a, b.asCircle);
		case 1: return collide_Circle_Rectangle(a, b.asRectangle);
	}
	return false;
}

void main()
{
	struct Circle a = ...;
	struct union_Circle_Rectangle b = ...;

	bool c = collide_dispatch0(a,b);
}