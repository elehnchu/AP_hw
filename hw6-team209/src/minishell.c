#include <signal.h>
#include <stdbool.h>
#include <stdio.h>	//for printing
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>	//for error messages
#include <limits.h>	//for path max
#include <signal.h>
#include <pwd.h>	//for getpwuid()

#define BRIGHTBLUE "\x1b[34;1m"
#define DEFAULT    "\x1b[0m"
#define MAX_CHAR_LENGTH 4096
#define MAX_TOKENS 2048

char *cwd;
char *pcwd;
char *buf;
char *path;

void printprompt(){
        getcwd(cwd, PATH_MAX);
        snprintf(pcwd, PATH_MAX + 4, "[%s]$ ", cwd);
        printf("%s%s%s", BRIGHTBLUE, pcwd, DEFAULT);
		//will print in reg color after
}

void gohome(){
	uid_t uid = getuid();
	struct passwd *passwordstruct;
	if((passwordstruct = getpwuid(uid))==NULL){
		fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(chdir(passwordstruct->pw_dir) == -1){
		fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", passwordstruct->pw_dir, strerror(errno));
	}
}

void gobranchpath(char *tokens[]){
	getcwd(cwd, PATH_MAX);

	snprintf(path, PATH_MAX, "%s/%s", cwd, tokens[1]);
        
	if(chdir(path) == -1){
                fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", path, strerror(errno));
        }
}

void gonewpath(char *tokens[]){
	uid_t uid = getuid();
        struct passwd *passwordstruct;
        if((passwordstruct = getpwuid(uid))==NULL){
                fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        snprintf(path, PATH_MAX, "%s/%s", passwordstruct->pw_dir, ++tokens[1]);
	
	if(chdir(path) == -1){
                fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", path, strerror(errno));
        }
}


void completelynewpath(char *tokens[]){
	if(chdir(tokens[1]) == -1){
                fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", tokens[1], strerror(errno));
        }
}

void changedirectory(char *tokens[]){

	//if no other arguments -> go home
	if(tokens[1] == NULL){
		gohome();
	} else if(tokens[1] != NULL && tokens[2] == NULL){
		
		//if 2nd token is ~ or ~/  -> gohome()
		if((!strcmp(tokens[1], "~") || !strcmp(tokens[1], "~/"))){
			gohome();
		}

		//see if it starts with ~/ or just go from folder we're in
		if(!(strncmp(tokens[1], "~", 1))){	//this is where we'd gonewpath()
			gonewpath(tokens);
		} else if (!(strncmp(tokens[1], "/", 1))){
			completelynewpath(tokens);
		}else{
			gobranchpath(tokens);
		}
	}
}	

//free-ing function
void bye(){
	if (cwd != NULL) {
        	free(cwd);
    		cwd = NULL;
	}
    	if (pcwd != NULL) {
        	free(pcwd);
		pcwd = NULL;
    	}
    	if (buf != NULL) {
        	free(buf);
		buf = NULL;
    	}
	if (path != NULL) {
                free(path);
                path = NULL;
        }
}

//code from class commandreader.c
/* signal_val is not used in this project but is shown for completeness. */
volatile sig_atomic_t interrupted = 0;

/* Signal handler */
void catch_signal(int sig) {
    interrupted = 1;
}

int main(int argc, char **argv){

	int exitbool = 0;	//0 for false, 1 for true

	if((cwd = (char *)malloc(PATH_MAX)) == NULL){
		fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
	}
	if((pcwd = (char *)malloc(PATH_MAX + 4)) == NULL){
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
	if((buf = (char *)malloc(PATH_MAX)) == NULL){
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
	if((path = (char *)malloc(PATH_MAX)) == NULL){
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
        char *tokens[MAX_TOKENS];


	//register atexit functions
	if (atexit(bye) != 0) {
                fprintf(stderr, "Error: Cannot set exit function.\n");
                exit(EXIT_FAILURE);
        }


	//code from class commandreader.c
	struct sigaction action;
    	memset(&action, 0, sizeof(struct sigaction));
    	action.sa_handler = catch_signal;

    	if (sigaction(SIGINT, &action, NULL) == -1) {
        	perror("sigaction(SIGINT)");
        	return EXIT_FAILURE;
    	}
    	
	while (true) {
        	printprompt();
	    	fflush(stdout);
        	if (fgets(buf, PATH_MAX, stdin) == NULL) {
			/* can this replace the below code?
			// Check if read failed due to interruption by a signal
         		if (interrupted) {
                		interrupted = 0;
                		continue;
            		}
            		// Otherwise, assume read failed for some other reason and exit
            		fprintf(stderr, "Error: fgets() failed.\n");
            		exit(EXIT_FAILURE);
        		}*/
            		if (errno == EINTR) {
				printf("\n");
                		errno = 0; // Need to reset errno to 0. fgets() does not do this for us.
                		continue;
            		} else if (feof(stdin)) {
                		printf("\n");
                		return EXIT_SUCCESS;
            		} else if (ferror(stdin)) {
                		printf("\n");
                		return EXIT_FAILURE;
            		}
        	}
        	
		char *eoln = strchr(buf, '\n');
		if (eoln != NULL) {
            		*eoln = '\0';
       		}

		

		// Tokenize input to deal with spacing out elements
                int i = 0;
                tokens[i] = strtok(buf, " ");
		while (tokens[i] != NULL) {
                        i++;
                        tokens[i] = strtok(NULL, " ");
                }
                tokens[i] = NULL;


                if (tokens[0] == NULL) {
                        // Input was not properly formatted
                        fprintf(stderr, "Error: Invalid input.\n");
                	// Check if input is a known command
                }else if (strcmp(tokens[0], "exit") == 0 ){
			exitbool=1;
			break;
			
		}else if ( strcmp(tokens[0], "cd") == 0) {
                        // Exit the if else statement
	
                	changedirectory(tokens);

			//continue;
                        //else if command is unknown then fork
                } else {
                        pid_t pid = fork();
                        if (pid < 0) {
                                fprintf(stderr,"Error: fork() failed. %s.\n",  strerror(errno));
                                exit(EXIT_FAILURE);
                        } else if (pid == 0) {
                                //child process
                                if (execvp(tokens[0], tokens) == -1) {
                                        fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
                                }
                        } else {
                        	//parent process
				int stat;
				if (waitpid(pid, &stat, 0) == -1) {
					if (interrupted) {
                                        	printf("\n");
                                        	interrupted = 0; 
                                        	continue;
                                	}else{
                                        	// Waiting for child process failed
                                        	fprintf(stderr, "Error: waitpid() failed. %s.\n", strerror(errno));
                                        	exit(EXIT_FAILURE);
					}
                                }
				continue;
                                if (!WIFEXITED(stat) || (WEXITSTATUS(stat)) != 0){
                                        return EXIT_FAILURE;
                                } else if (WIFSIGNALED(stat)) {
                                	// Child process was terminated by a signal
                                        fprintf(stderr, "Error: Child process was terminated by signal %d.\n", WTERMSIG(stat));
                                        exit(EXIT_FAILURE);
                                }
                        }
                }

		if(exitbool == 1){
			break;
		}
	}		
	return EXIT_SUCCESS;
}
