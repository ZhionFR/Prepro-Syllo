#include "stdlib.h"
#include "stdio.h"
#include <string.h>


#include "save.h"

char ** getQuantList(){
    int len = 5; // 5 for example

    char ** quantList = (char**)malloc(len * sizeof(char*));

    for (int i = 0; i < len; i ++){
        quantList[i] = (char*) malloc(50 * sizeof(char));
        // EXAMPLE LINE : WE NEED TO PUT REAL FILE VALUES HERE
        quantList[i] = "Quantificateur Vide";
    }

    return quantList;
}

// macro et assert seront prochainement add.

// Function to save an array of strings to a specified file.
int save_string_array_in_file(char ** words, int length, char * file_name){
    // Test if the input array is empty.
    if (words == NULL){
        fprintf(stderr, "Error save_string_list_in_file() : word points to null.");
        exit(EXIT_FAILURE);
    }
    // File opening in write mode.
    FILE * p_file = fopen(file_name, "w");
    if (p_file == NULL){
        fprintf(stderr, "Error save_string_list_in_file() : file opening filed.");
        exit(EXIT_FAILURE);
    }
    // Write each stirng from the array in the file.
    for (int index = 0 ; index < length; index ++){
        fputs(words[index], p_file);
        fputs("\n", p_file);
    }
    // Closing the file.
    fclose(p_file);
    // End program with success status.
    return EXIT_SUCCESS;
}

// Function to restore an array of string from a file.
int restore_string_array_from_file(char ** words, int length, char * file_name){
    //  Test input string array.
    if (words == NULL){
        fprintf(stderr, "Error restore_string_array_from_file() : word points to null.");
        exit(EXIT_FAILURE);
    }
    // File opening.
    FILE * p_file = fopen(file_name, "r");
    if (p_file == NULL){
        fprintf(stderr, "Error restore_string_array_from_file() : file opening filed.");
        exit(EXIT_FAILURE);
    }
    // Restore each words from file in string array.
    for (int index = 0 ; index < length; index ++){
        fgets(words[index], 100, p_file);
        // Dans le cas ou '\n' a ete enregistre dans word[index] on le remplace par '\0'.
        words[index][strcspn(words[index], "\n")] = '\0';
    }
    // Close the file.
    fclose(p_file);
    // Exit program with sucess.
    return EXIT_SUCCESS;
}
