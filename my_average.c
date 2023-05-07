#include "my_average.h"

double average(int n_value, ...)
{

	int count = 0;
	double sum = 0;

	va_list var_arg;
	va_start(var_arg, n_value);

	for (; count < n_value; count += 1)
	{
		int p = (va_arg(var_arg, int));
		printf("%d\n", p);
		sum += p;
	}

	va_end(var_arg);
	return sum / n_value;
}
