#include "stdlib.h"
#include "stdio.h"

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

