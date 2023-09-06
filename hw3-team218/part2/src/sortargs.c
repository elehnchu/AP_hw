#include <stdio.h>
#include <string.h>
#include "linked_list.h"


/*passed to insert_in_order() to compare the strings in the list*/
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

void print_string(void *data) {
    printf("\"%s\"", (char*)data);
}

void free_data (void *data){
	// Do nothing
}

int string_cmp(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

int main(int argc, char **argv) {
    linked_list *list = create_linked_list();
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    print_list(list, print_string);
    for (int i = 1; i < argc; i++) {
        char *word = argv[i];
        insert_in_order(list, word, string_cmp);
        print_list(list, print_string);
    }
    free_list(list, free_data);
    return EXIT_SUCCESS;
}


/*print the strings in the list*/
