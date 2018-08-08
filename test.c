#include <stdio.h>
#include <locale.h>
#include "includes/ft_printf.h"

int main(int argc, char** argv) {
	// ft_printf("%llhd\n", 4294967296);
	// printf("%llhd\n", 4294967296);
	setlocale(LC_ALL, "");

	char *a = "a";
	int my = ft_printf("mine -->%05.%<--\n", 0);
	int yo = printf("their-->%05.%<--\n", 0);
	fflush(stdin);
	printf("return:->%i<-\n", my);
	printf("return:->%i<-\n", yo);

	//printf("%lu\n%lu\n%lu\n%lu\n%lu\n%lu\n",sizeof(short),sizeof(char),sizeof(int),sizeof(intmax_t), sizeof(size_t),sizeof(long));
	//printf("%.7-+hlz4", 5);
	// printf("%1#2 3-ljyh-10z0.2-+d\n", 5);
	// printf("%1#2 3-ljYh-10z0.2-+d\n", 5);
	return 0;
}
