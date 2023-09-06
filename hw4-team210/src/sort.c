#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024
void print_block() {
  printf("Usage: ./sort [-i|-d] [filename]\n");
  printf("   -i: Specifies the input contains ints.\n");
  printf("   -d: Specifies the input contains doubles.\n");
  printf("   filename: The file to sort. If no file is supplied, input is read from \n\t stdin.\n");
  printf("   No flags defaults to sorting strings.\n");
}

int main(int argc, char **argv) {
  
   int input;
   int flagcount = 0;
   int datatype = 0;
   char *file = NULL;

  // Parse command line arguments using getopt
  while ((input = getopt(argc, argv, ":id")) != -1) {
    switch (input) {
    case 'i':
	if (datatype != 1){
           flagcount++;
        }
        datatype = 1;
        break;
    case 'd':
	if (datatype != 2){
	   flagcount++;
	}
        datatype = 2;
        break;
    case '?':
        //for all unrecognized flags, both single or multiple.
        fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
        print_block();
	return EXIT_FAILURE;
    default:
        return EXIT_FAILURE;
    }
  }
  // Check for multiple valid flags
  if ((flagcount > 1)) {
    fprintf(stderr, "Error: Too many flags specified.\n");
    return EXIT_FAILURE;
  }
  
  // Check for multiple filenames
  if (optind + 1 < argc) {
      fprintf(stderr,"Error: Too many files specified.\n");
      return EXIT_FAILURE;
  } 

  // Read input into an array
  char buff[MAX_STRLEN + 2];
  char **sort_array;
  if ((sort_array = (char**) malloc(MAX_ELEMENTS * sizeof(char*))) == NULL) {
      fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
      return EXIT_FAILURE;
  }  
  //copies contents in buff to array
  int input_count = 0;
  int temp_counter = 0;
  
  if( argv[optind] != NULL){
    FILE *pf = fopen(argv[optind], "r");
    // Check for invalid filename
    if (pf == NULL) {
        fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno));
        return EXIT_FAILURE;
    } else {
	 for(int i = 0; i < MAX_ELEMENTS; i++){
            if ((sort_array[input_count] = (char*) malloc(sizeof(buff) * sizeof(char))) == NULL) {
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                for (int i = 0; i < input_count; i++) {
                    free(sort_array[i]);
                }
                fclose(pf);
                return EXIT_FAILURE;
	    }
            input_count++;
         }
 	 while (fgets(buff, (MAX_STRLEN + 1), pf) != NULL) {
	    char *temp = strchr(buff, '\n');
       	    if(temp !=NULL){
		*temp = '\0';
	     }
	     if (*buff != '\0') {
		  strcpy(sort_array[temp_counter++], buff);
		  if (ferror(pf)){
			fprintf(stderr, "Cannot read data due to error %d. \n", errno);
			break;
		   }
	      }
	 }
    }
    fclose(pf);
    //there is no file input (stdin)
  } else {
	   for(int i = 0; i < MAX_ELEMENTS; i++){
            if ((sort_array[input_count] = (char*) malloc(sizeof(buff) * sizeof(char))) == NULL) {
                fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
                for (int i = 0; i < input_count; i++) {
                    free(sort_array[i]);
                }
                return EXIT_FAILURE;
            }
            input_count++;
         }
         while (fgets(buff, (MAX_STRLEN + 1), stdin) != NULL) {
              strcpy(sort_array[temp_counter++], buff);
         }
    }
  // datatype=0 ( string or no input)  datatype = 1 (int), datatype = 2 (double)
  if (datatype == 0) {
    quicksort(sort_array, temp_counter, sizeof(char*), str_cmp);
    for (int i = 0; i < temp_counter; i++) {
        printf("%s\n", sort_array[i]);
    }
    for (int i = 0; i < input_count; i++) {
        free(sort_array[i]);
    }
  } else if (datatype == 1) {
      int int_array[temp_counter];
      for (int i = 0; i < temp_counter; i++){
          char* char_type = sort_array[i];
          int int_type = atoi(char_type);
          int_array[i] = (int) int_type;
      }
      quicksort(int_array, temp_counter, sizeof(int), int_cmp);
      for (int i = 0; i < temp_counter; i++) {
        printf("%d\n", int_array[i]);
      }
      for (int i = 0; i < input_count; i++) {
        free(sort_array[i]);
      }
  } else if (datatype == 2) {
      double dbl_array[temp_counter];
      for (int i = 0; i < temp_counter; i++){
          char* char_type = sort_array[i];
          double dbl_type = atof(char_type);
          dbl_array[i] = (double) dbl_type;
      }
      quicksort(dbl_array, temp_counter, sizeof(double), dbl_cmp);
      for (int i = 0; i < temp_counter; i++) {
          printf("%.6f\n", dbl_array[i]);
      }
      for (int i = 0; i < input_count; i++) {
        free(sort_array[i]);
      }
  } else {
      quicksort(sort_array, temp_counter, sizeof(char*), str_cmp);
      for (int i = 0; i < temp_counter; i++) {
          printf("%s\n", sort_array[i]);
      }
      for (int i = 0; i < input_count; i++) {
        free(sort_array[i]);
      }
  }
 free(sort_array);
 return EXIT_SUCCESS;

}


