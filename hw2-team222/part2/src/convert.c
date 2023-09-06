#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int n;

	printf ("Enter an integer : ");
	scanf("%d", &n);
	printf ("\n");
	printf("signed decimal   : %d\n", n);
	printf("unsigned decimal : %u\n", n);
	printf("hexadecimal      : %x\n", n);
	printf("binary           : ");
	int i = 31;
	int spaces=0;
	while (i>=0)
        {
                if (spaces==4){
                        printf(" ");
                        spaces=0;
                }
                spaces ++;
                if (1&(n>>i))
                {
                        putc('1', stdout);
                }
                else
                {
                        putc('0', stdout);
                }
                i--;
        }

	printf("\n");
    	return EXIT_SUCCESS;
}
