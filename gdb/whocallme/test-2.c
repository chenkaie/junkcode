#include "whocallme.h"

void test()
{
	who_call_me(); 
}
void test_a()
{
	test_b();
	test_c();
}
void test_b()
{
	test();
}
void test_c()
{
	who_call_me(); 
}
int main(int argc, char *argv[])
{
	init_function_table(argv[0]);
	test();
	test_a();      
	test_b();
	test_c();
}
