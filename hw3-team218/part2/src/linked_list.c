#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

void print_list(linked_list *list, void (*print_function)(void*)) {
    putchar('[');
    node *cur = list->head;
    if (cur != NULL) {
        print_function(cur->data);
        cur = cur->next;
    }
    for ( ; cur != NULL; cur = cur->next) {
        printf(", ");
        print_function(cur->data);
    }
    printf("]\n{length: %lu, head->data: ", list->size);
    list->head != NULL ? print_function(list->head->data) :
                         (void)printf("NULL");
    printf(", tail->data: ");
    list->tail != NULL ? print_function(list->tail->data) :
                         (void)printf("NULL");
    printf("}\n\n");
}

/* creates link list we will use */
linked_list* create_linked_list() {
    linked_list* list =(linked_list *) malloc(sizeof(linked_list));

    if (list == NULL) {
        return NULL;
    }

    /*set size to 0*/
    list->size = 0;

    /*set tail and head pointers to NULL*/
    list->tail = NULL;
    list->head = NULL;
   

    /*return a pointer to the linkedlist.
     *  Will return NULL in case where allocation fails*/
    return list;
}


/*implement insert in order function*/ 
bool insert_in_order(linked_list *list, void *data, int (*cmp)(const void*, const void*)) {
    if (list == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
        return true;
    }

    node *current = list->head;
    node *previous = NULL;


    while (current != NULL && cmp(current->data, data) < 0) {
        previous = current;
        current = current->next;
    }
    
    // add new_node to the beginning of the list
    if (previous == NULL) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    // add new_node to the end of the list
    else if (current == NULL) {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    // add new_node in the middle of the list
    else {
        new_node->next = current;
        new_node->prev = previous;
        previous->next = new_node;
        current->prev = new_node;
    }
    list->size++;
    return true;
}

void free_list(linked_list *list, void (*free_data)(void *)) {	
	/*check if list is null*/
	if (list == NULL) {
        return;
    }	
    node *current_node = list->tail;
    node *prev;
    while (list->tail != NULL) {
         prev = current_node->prev;
         free_node(current_node, free_data);
         current_node= prev;
         list -> tail = current_node;
    }

    /*free up memory allocated for list*/
    free(list);
}

