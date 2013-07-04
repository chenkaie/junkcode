#include <stdio.h>
void func4() { puts("Output"); }
void func3() { func4(); }
void func2() { func3(); }
void func1() { func2(); }

int main()
{
	int ret = 0;
	func1();
	return ret;
}
