#include <stdio.h>

#define ShapeText(TYPE) void (*new)(struct TYPE*);float (*area)(struct TYPE*)

typedef struct _Shape {
	ShapeText(_Shape);
} Shape;

float ShapeArea(Shape *obj) { return 0; }

void ShapeNew(Shape *obj) {
	obj->new = ShapeNew;
	obj->area = ShapeArea;
}

typedef struct _Circle {
	ShapeText(_Circle);
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
	Circle c;
	CircleNew(&c);
	c.r = 3.0;
	Shape *list[] = { &s, (Shape*) &c };
	int i;
	for (i=0; i<2; i++) {
		Shape *o = list[i];
		printf("s.area()=%G\n", o->area(o));
	}
}
