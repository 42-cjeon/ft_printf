#include <stdio.h>
#include "ft_printf.h"


int main(void)
{
	int a;
	const char *string = "-";
	printf("|%#8.50000x|\n", 100);
	ft_printf("|%-50000d|\n", 100);
	return 0;
}