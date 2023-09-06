# Homework 3

There are two parts to this homework. In part 1, you will write a function that can print out all command line arguments in lowercase.
In part 2, you will write a linked list library, which will then be used to sort command line arguments. Instructions for each part can be found under

    part1/instructions.md
    part2/instructions.md

All your changes must be done under the `src` directory for each part.

Your code should be organized as follows. (Ignoring all markdown files)

    part1
        \_ src
            \_ mystring.h
            \_ mystring.c
            \_ lowercase.c
            \_ Makefile
    part 2
        \_ src
            \_ node.h
            \_ node.c
            \_ linked_list.h
            \_ linked_list.c
            \_ sortargs.c
            \_ Makefile

All files and directories must be named exactly as above case-sensitive. ***You should not commit any extraneous files, such as object files or executables.***

All rules about Makefiles and compilation are listed on HW2 and will be the same for all future assignments.

Starting with HW3, you will be heavily penalized if any execution, including error cases, of your program leaks memory or causes memory errors. These include (among other things) failure to call `free()` on the memory you obtained through `malloc()`, accessing past array bounds, dereferencing uninitialized pointers, etc.

You can use a debugging tool called valgrind to check your program:

    valgrind --leak-check=full ./your_executable <optional args>

It will tell you if your program has any memory leaks or errors.  For more details on common errors, read [this guide](https://github.com/cs3157-borowski/guides/blob/main/valgrind.md) put together by the TAs.

All submissions must include at least five git commits with meaningful messages.

After completing the homework, fill out [this form](https://docs.google.com/forms/d/e/1FAIpQLScxoejSN_-nlHfId7LfTRtAdyup9bKjfsX7vU_7xfEOS9hpjw/viewform?usp=sf_link) with how many hours the assignment took you and how difficult you found the assignment.

## Submission

To submit:

    git commit -am "hw3 completed"
    git tag -a "handin" -m "hw3 submission"
    git push origin main
    git push origin handin

## Acknowledgments

This homework was developed by Dr Brian Borowski and Mateo Maturana for Spring 2023.
Parts of the homework are influenced by Prof Jae Lee.