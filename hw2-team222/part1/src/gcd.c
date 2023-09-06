#include <stdio.h>
#include <stdlib.h>
#include "iterative.h"
#include "recursive.h"

int main(int argc, char **argv) {

	int a;
        int b;

	if (argc!=3)
	{
		fprintf( stderr, "Usage: ./gcd <integer m> <integer n>\n");
		return EXIT_FAILURE;
	}
	
	a = atoi (argv[1]);
        b = atoi (argv[2]);

	if(a==0 && b==0)
	{
		fprintf( stdout, "gcd(0, 0) = undefined\n");
		return EXIT_SUCCESS;
	}
	else
	{
                int iter= gcd_iterative(a,b);
                int recur= gcd_recursive(a,b);
                fprintf( stdout, "Iterative: gcd(%d, %d) = %d\n", a,b,iter);
                fprintf( stdout, "Recursive: gcd(%d, %d) = %d\n", a,b,recur);
                return EXIT_SUCCESS;
	}
}
