int fib (int n)
{
	int result;

	if (n <= 2)
		result = 1;
	else
		result = fib(n-2) + 
			 fib(n-1);

	return result;
}

int main()
{
	int ret = fib(5);
	return ret;
}

