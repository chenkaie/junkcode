#include <stdio.h>

#define ShapeClassMembers(OBJ) float (*area)(struct OBJ*)
#define ShapeMembers(OBJ) 

struct _Shape;

typedef struct _ShapeClass {
	ShapeClassMembers(_Shape);
} ShapeClass;

typedef struct _Shape {
	ShapeClass *class;
	ShapeMembers(_Shape);
} Shape;

float ShapeArea(Shape *obj) { return 0; }

ShapeClass shapeClass = { .area = ShapeArea };

struct _Circle;

typedef struct _CircleClass {
	ShapeClassMembers(_Circle);
	float r;
} CircleClass;

typedef struct _Circle {
	CircleClass *class;
	ShapeMembers(_Circle);
	float r;
} Circle;

float CircleArea(Circle *obj) { return 3.14 * obj->r * obj->r; }

CircleClass circleClass = { .area = CircleArea };

int main() {
	Shape s = { .class = &shapeClass };
	Circle c = { .class = &circleClass, .r = 3.0 };
	Shape *list[] = { &s, (Shape*) &c };
	int i;
	for (i=0; i<2; i++) {
		Shape *o = list[i];
		printf("s.area()=%G\n", o->class->area(o));
	}
}
