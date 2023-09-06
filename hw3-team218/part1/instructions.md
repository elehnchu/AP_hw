# Part 1

## Part A

You will write `mystring.c` that implements the following three string utility methods whose prototypes are included in `mystring.h`.

``` c
size_t my_strlen(char *src);
char *my_strcpy(char *dst, char *src);
void my_strlower(char *src);
```

The header file contains detailed comments specifying the behavior of the functions. Your implementation should follow the specified behavior.

Although we are not providing a test file, you are responsible for correct implementation of all functions.

You may not have any other include statements in `mystring.c` other than the following: `#include "mystring.h"` and `#include <stddef.h>`. Any other include statements will be removed before grading, which may cause your code not to compile.


## Part B

You will write a program, named "lowercase", that takes words as command line arguments, then prints all words in lowercase. For example,

```
$ ./lowercase HI ByE Tomorrow
Raw arguments       : [HI, ByE, Tomorrow]
Lowercase arguments : [hi, bye, tomorrow]
```

Your program should be able to handle any number of arguments.

Here are some requirements and hints:

- You CANNOT modify the main function. Your job is to implement other functions that `main()` calls.
- You may not add any other `include` statements. Any additional include statements will be removed before grading.
- You must call `malloc()` to allocate memory. Any calls to `memset()`, `calloc()`, or any similar functions will be commented out.
- In `copy_args_lowercase`, you should make a "copy" of the memory structure shown on Page 115 in K&R (Section 5.10 - Command Line Arguments). 
- In `free_copy()`, you must `free()` everything you previously `malloc()ed`
- Remember that your code should have no memory errors or memory leaks. Use valgrind often to test your code.
