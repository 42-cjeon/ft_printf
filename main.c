#include <stdio.h>
#include "ft_printf.h"


int main(void)
{
	int a;
	ssize_t o;
	ssize_t r;
	const char *string = "-";
	o = printf("|%04d|\n", 9);
	r = ft_printf("|%04d|\n", 9);
	printf("EXPECTED=%zd, RECIVED=%zd\n", o, r);
	return 0;
}