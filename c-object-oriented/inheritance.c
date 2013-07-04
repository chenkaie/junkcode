#include <stdio.h>

#define ShapeMembers(TYPE) void (*new)(struct TYPE*);float (*area)(struct TYPE*)

typedef struct _Shape {
	ShapeMembers(_Shape);
} Shape;

float ShapeArea(Shape *obj) { return 0; }

void ShapeNew(Shape *obj) {
	obj->new = ShapeNew;
	obj->area = ShapeArea;
}

typedef struct _Circle {
	ShapeMembers(_Circle);
	float r;
} Circle;

float CircleArea(Circle *obj) { return 3.14 * obj->r * obj->r; }

void CircleNew(Circle *obj) {
	obj->new = CircleNew;
	obj->area = CircleArea;
}

int main() {
	Shape s;
	ShapeNew(&s);
	printf("s.area()=%G\n", s.area(&s));

	Circle c;
	CircleNew(&c);
	c.r = 3.0;
	printf("c.area()=%G\n", c.area(&c));
}

