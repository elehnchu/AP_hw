#include <stdio.h>
#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>

int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
               S_IRGRP, S_IWGRP, S_IXGRP,
               S_IROTH, S_IWOTH, S_IXOTH};


//declaring variables to be malloced
char *dir;
char *perm;
char *perm_string;

int free_perm_string = 0;       //for false, initially

//./pfind -d <directory> -p <permissions string> [-h]
// anything in [] is optional
// anything in <> is required

/**
 * Displays the usage message on the screen.
 */
void display_usage(char *progname, FILE *stream) {
    fprintf(stream,
    "Usage: %s -d <directory> -p <permissions string> [-h]\n", progname);
}
//pass in ./pfind
//stream should be to terminal (stdout)

void display_invalidperm(FILE *stream){
        fprintf(stream, "Error: Permissions string '%s' is invalid.\n", perm);
}


//frees everything before program is exited
void bye(){
        free(dir);
        free(perm);
	if(free_perm_string){
		free(perm_string);
	}
}


//checks for validity of permission strings
//returns 0 if valid, -1 if invalid
int check_perm(char *perm){
        if(strlen(perm) != 9){
                return -1;
	}
	for(int i=0; i<9; i = i+3){
		if(perm[i] != 'r' && perm[i] != '-'){
			return -1;
		}
	}
        //check w
        for(int i=1; i<9; i = i+3){
                if(perm[i] != 'w' && perm[i] != '-'){
                        return -1;
                }
        }
	//check x
        for(int i=2; i<9; i = i+3){
                if(perm[i] != 'x' && perm[i] != '-'){
                        return -1;
                }
        }
	return 0;	//valid perm
}


//will output permissions as string from st_mode
char *this_perm_string(struct stat statbuf){
    	for (int i = 0; i < 9; i += 3) {
        	perm_string[i + 0] = statbuf.st_mode & perms[i] ? 'r' : '-';
        	perm_string[i + 1] = statbuf.st_mode & perms[i + 1] ? 'w' : '-';
        	perm_string[i + 2] = statbuf.st_mode & perms[i + 2] ? 'x' : '-';
    	}

	//why must we use dot operator if statbuf is a struct??

    	perm_string[9] = '\0';
    	return perm_string;
}



//recurses through given directory
//0 returned if successful, -1 returned if failed
int recurse_dir(char *path){
	DIR *directory;

	directory = opendir(path);
	if(directory == NULL){
		fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n", path, strerror(errno));
		return -1;
	}

	struct dirent *dir_struct;	//ptr to dirent struct called dir_struct
	struct stat stat_struct;	//stat structure (gives info on each file)
	char newpath[PATH_MAX];

	if(directory){
		//goes to each item
		while((dir_struct = readdir(directory)) != NULL){
			//skip . and ..
			if (strcmp(dir_struct->d_name, ".") == 0 || strcmp(dir_struct->d_name, "..") == 0) {
            			continue;
        		}
				//moves d+new dir to newpath, PATH_MAX bytes possibly can be moved over	
			snprintf(newpath, PATH_MAX, "%s/%s", path, dir_struct->d_name);

			//code from statfullpath.c in class
			if (lstat(newpath, &stat_struct) < 0) {
            			fprintf(stderr, "Error: Cannot stat file '%s'. %s.\n", dir_struct->d_name, strerror(errno));
            			continue;
        		}
			if (S_ISDIR(stat_struct.st_mode)) {

				//if perm string matches, it prints ...
				if(strcmp(perm, this_perm_string(stat_struct)) == 0){
					printf("%s\n", newpath);	
				}
				recurse_dir(newpath);	//parameter is path to the next directory	
			} else {
				//if perm string matches, it prints ...
                                if(strcmp(perm, this_perm_string(stat_struct)) == 0){
                                	printf("%s\n", newpath);
				}
			}
		}
	}

	closedir(directory);
	return 0;
}


int main(int argc, char **argv){

	int opt = 0;
	int dflag=0, pflag=0;
	int dfound = 0, pfound = 0;

	dir = (char *)malloc(PATH_MAX);
	perm = (char *)malloc(100);

	//registering bye() to be called when process (this program) terminates
        if (atexit(bye) != 0) {
                fprintf(stderr, "Error: Cannot set exit function.\n");
                exit(EXIT_FAILURE);
        }

	char *dircpy;
	char *permcpy;	

	opterr = 0;	//supresses built in error messages

	//put a : after every flag that has a value it takes in
	while((opt = getopt(argc, argv, "d:p:h")) != -1){
		switch(opt){
			case 'd':
				dflag++;
				dircpy = optarg;	//gives value directly after accessing d flag
				break;
			case 'p':
				pflag++;
				permcpy = optarg;
				break;
			case 'h':
				display_usage(argv[0], stdout);
				return EXIT_SUCCESS;
				break;
			case '?':
				//check if d or p
				if(optopt == 'd'){
					dfound = 1;
				} else if(optopt == 'p'){
					pfound = 1;
				} else {
					fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
                			return EXIT_FAILURE;
				}
				break;
			default:
				printf("reached default\n");
				return EXIT_FAILURE;
		}
	}

	//no arguments passed in
	if(dflag == 0 && pflag == 0 && dfound == 0 && pfound == 0){
		display_usage(argv[0], stderr);
		return EXIT_FAILURE;
	}

	if(dflag < 1 || dfound == 1){
                fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
                return EXIT_FAILURE;
        }

	if(pflag < 1 || pfound == 1){
		fprintf(stderr, "Error: Required argument -p <permission string> not found.\n");
		return EXIT_FAILURE;
	}

	if(dflag > 1 || pflag > 1){
		fprintf(stderr, "Error: Too many options enabled.\n");
		display_usage(argv[0], stderr);
		exit(EXIT_FAILURE);
	}

	//moving the inputs to the malloced space
	strcpy(dir, dircpy);
	strcpy(perm, permcpy);


	struct stat test_statbuf;
        //checking validity of given path
        if(stat(dir, &test_statbuf) < 0){
		fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", dir, strerror(errno));
                exit(EXIT_FAILURE);
        }


	//checking validity of given permission string
        if(check_perm(perm) == -1){
                display_invalidperm(stderr);
                exit(EXIT_FAILURE);
        }


	//mallocing for permission string to be used in comparison in recurse_dir()
	//code from permstat.c from class
        if ((perm_string = malloc(10 * sizeof(char))) == NULL) {
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
        } else{
		free_perm_string = 1;	//seting it to be freed at exit
	}

	//prints out every file that matches permission string in the given dir
	if(recurse_dir(dir) == -1){
		//printf("recurse_dir() failed\n");
		return EXIT_FAILURE;
	}



	exit(EXIT_SUCCESS);
}
