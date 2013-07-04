#include <stdio.h>

struct Circle {
	void (*new)(struct Circle*, float); 
	float (*area)(struct Circle*);
	float r;
};

float CircleArea(struct Circle *obj) { return 3.14 * obj->r * obj->r; }

void CircleNew(struct Circle *obj, float r) {
	obj->new = CircleNew;
	obj->area = CircleArea;
	obj->r = r;
}

int main() {
	struct Circle c;
	CircleNew(&c, 3.0);
	printf("area() = %G\n", c.area(&c));
}
