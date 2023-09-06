#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include <string.h>

/** Take an array of char* pointers and print each of the strings to standard
* out. This function must use only pointer arithmetic and no array
* subscripting. The output start with "[", ends with "]\n", and prints the
* strings inside, each separated by a comma and space.
* Example: [Hi, BYE, AP, COMSW 3157, FunTimes]
*/

void display_strings(char **strings) {
    printf("[");
    if (strings != NULL) {
        char **str_ptr = strings;
        if (*str_ptr != NULL) {
            printf("%s", *str_ptr++);
            while (*str_ptr != NULL) {
                printf(", %s", *str_ptr++);
            }
        }
    }
    printf("]\n");
}

void my_strlowcase(char *s1, const char *s2) {
	int i;
	for (i = 0; s2[i] != '\0'; i++) {
		if (s2[i] >= 'A' && s2[i] <= 'Z') {
			s1[i] = s2[i] + ('a' - 'A');
		} else {
			s1[i] = s2[i];
		}
	}
	
	s1[i] = '\0';

}


static char **copy_args_lowercase(int argc, char **argv) {
	char **copy = malloc((argc) * sizeof(char *));
	char **cp_ptr = copy;
	char **arg_ptr = argv + 1;
	while (*arg_ptr != NULL) {
		int len = strlen(*arg_ptr);
		*cp_ptr = malloc((len + 1) * sizeof(char));
		my_strlowcase(*cp_ptr, *arg_ptr);
		arg_ptr++;
		cp_ptr++;
	}
	
	*cp_ptr = NULL;
	return copy;
}


static void free_copy(char **copy) {
	char **cp_ptr = copy;
	while (*cp_ptr != NULL) {
		free(*cp_ptr);
		cp_ptr++;
	}
	
	free(copy);
}
  

int main(int argc, char **argv) {
    char **copy;
    copy = copy_args_lowercase(argc, argv);
    printf("Raw arguments       : ");
    display_strings(argv + 1);
    printf("Lowercase arguments : ");
    display_strings(copy);
    free_copy(copy);
    return EXIT_SUCCESS;
}

