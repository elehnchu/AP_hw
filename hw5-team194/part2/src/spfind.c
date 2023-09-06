#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pfind[2];
    int sort[2];
    int stat[2];
    pid_t pid[2];

    //checks pipe errors
    pipe(pfind);
    pipe(sort);

    if (pipe(pfind) < 0 || pipe(sort) < 0 ){
        perror("Error: Cannot create pipe.");
        return EXIT_FAILURE;
    }
    
    //fd[0] open for reading
    //fd[1] open for writing
    
    //for first process
    pid[0] = fork();
    if (pid[0] < 0){
        perror("Error: pfind fork() failed.");
        return EXIT_FAILURE;
        
        //for first child process
    } else if ((pid[0]) == 0){
        close(pfind[0]);
        if (dup2(pfind[1], STDOUT_FILENO) == -1) {
            perror("Error: dup2() failed for pfind.");
            return EXIT_FAILURE;
        }
        close(pfind[1]);

        if ((execv("./pfind", argv)) == -1){
            perror ("Error: pfind failed.");
            return EXIT_FAILURE;
        }
    }
    
    //for second process
    pid[1] = fork();
    if ( pid[1] < 0){
        perror ("Error: sort fork() failed.");
        return EXIT_FAILURE;

        //for second child process
    } else if ((pid[1]) == 0) {

        close(pfind[1]);
        if (dup2(pfind[0], STDIN_FILENO) == -1) {
            perror("Error: dup2() failed for sort.");
            return EXIT_FAILURE;
        }
        close(pfind[0]);
        close (sort[0]);

        if (dup2(sort[1], STDOUT_FILENO) == -1) {
            perror("Error: dup2() failed for sort.");
            return EXIT_FAILURE;
        }
        close(sort[1]);

        if ((execlp("sort", "sort", NULL)) == -1){
            perror ("Error: sort failed.");
            return EXIT_FAILURE;
        }
    } 
    //close all unused file descriptors
    close(sort[1]);
    close (pfind[0]);
    close (pfind[1]);

    //parent process continues
    char buf[6000] = "";
    ssize_t readd;
    int counter = 0;

    while ((readd = read(sort[0], buf, sizeof(buf) - 1)) > 0){
        buf[readd] = '\0';
        fprintf(stderr, "%s", buf);
        for (int i = 0; i < readd; i++){
            if (buf[i] == '\n'){
                counter++;
            }
        }
    }

    if (readd == -1){
        perror("Error: read() failed.");
        return EXIT_FAILURE;
    }

    close (sort[0]);

    for (int k = 0; k < 2; k++){
        if (waitpid(pid[k], &stat[k], 0) == -1){
            perror("Error: waitpid() failed.");
            return EXIT_FAILURE;
        }
    }

    for (int z = 0; z < 2; z++){
        if (!WIFEXITED(stat[z]) || (WEXITSTATUS(stat[z])) != 0){
            return EXIT_FAILURE;
        }
    }

    if ((strncmp(buf, "Usage", 5)) != 0 && counter > 0){
        printf ("Total matches: %d\n", counter);
    } else {
        printf("No matches found.\n");
    }

    return EXIT_SUCCESS;
}
