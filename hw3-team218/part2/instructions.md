# Part 2

## Part A

Your job is to implement a generic doubly linked list that can hold any data type.
The interface has been specified and provided to you in a header file called `linked_list.h`.
You will write `linked_list.c` that implements each function whose prototype is included in `linked_list.h`. Specifically, you will write the following functions:

``` c
linked_list* create_linked_list();

bool insert_in_order(
    linked_list *list, void *data, int (*cmp)(const void*, const void*));

void free_list(linked_list *list, void (*free_data)(void *));
```

*Please note that `bool` is not a data type in C, but `stdbool.h` maps true to 1 and false to 0 for convenience using macros.*

The header file contains detailed comments specifying the behavior of the functions. Your implementation should follow the specified behavior.

Although we are not providing a test file, you are responsible for correct implementation of all functions. Remember that your implementation must also not leak memory, you can check this by running Valgrind as specified in the README.md.

## Part B

You will write a program, named "sortargs", that takes words as command-line arguments and sorts them in alphanumeric order and also print the sorted list along with some other list data. *Hint: `strcmp` may be useful for sorting.*

For example,

```
$ ./sortargs hi apple trumpet zebra
[]
{length: 0, head->data: NULL, tail->data: NULL}

["hi"]
{length: 1, head->data: "hi", tail->data: "hi"}

["apple", "hi"]
{length: 2, head->data: "apple", tail->data: "hi"}

["apple", "hi", "trumpet"]
{length: 3, head->data: "apple", tail->data: "trumpet"}

["apple", "hi", "trumpet", "zebra"]
{length: 4, head->data: "apple", tail->data: "zebra"}
```

Your program should be able to handle any number of arguments and the output should match the above verbatim. *Hint: Use `print_list` from `linked_list.h`*.

You may not have any additional `include` statements other than what is included in the skeleton code, any additional include statements will be removed before grading. 
