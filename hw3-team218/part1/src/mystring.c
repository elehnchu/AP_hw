#include "mystring.h"
#include <stddef.h>

size_t my_strlen(char *src){
    size_t counter = 0;
    char *temp = src;
    while (*temp != '\0') {
        counter++;
        temp++;
   }
    return counter;
}

char *my_strcpy(char *dst, char *src) {
    char *temp = src;
    char *desttemp = dst;
    while (*temp != '\0') {
        *desttemp = *temp;
        temp++;
        desttemp++;
    }
    *desttemp = '\0';
    return dst;
}

void my_strlower(char *src) {
 	char *temp = src;
 	while (*temp != '\0'){
 		*temp = tolower(*temp);
 		temp++;
 	}
 
}
