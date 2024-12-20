#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "save.h"


#include "interface.h"
// pas de panique
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"


// Check if value is 0
int isDead(int value) {
    return value == KILL;
}

// Check if string = "0"
int isDeadStr(const char* name) {
    return (strcmp(name, "0")) == KILL;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard all characters in the input buffer
    }
}

// Return the number for the quantifier between 1 and 4
int getQuantif(int num, int len[], int * ver, char ** fileA, char ** fileE, char ** fileI, char ** fileO) {
    int stop = 0;
    int index = 1, temp;
    int filterA = 1, filterE = 1, filterI = 1, filterO = 1;
    int choice;
    while (!stop) {
        printf("Choisir un quantificateur Q%i : \n", num);
        printf("-1 : Choix du filtre\n");
        printf("-2 : Nouveau quantificateur\n");
        
        // For each filter, print the list of quantifiers
        if (filterA) {
            temp = printQuantList(fileA, index, len[0]);
            index = temp;
        }
        if (filterE) {
            temp = printQuantList(fileE, index, len[1]);
            index = temp;
        }
        if (filterI) {
            temp = printQuantList(fileI, index, len[2]);
            index = temp;
        }
        if (filterO) {
            temp = printQuantList(fileO, index, len[3]);
            index = temp;
        }
                    
        // Collect the number for the choice of the quantifier
        scanf("%i", &choice);
        
        // If there's a choice, the function will stop after this
        if (choice > 0) {
            stop = 1;
        }

        // New quantifier
        if (choice == -2) {
            return -2;
        }

        // Condition for exiting the function
        if (isDead(choice)){
            exit(1);
        }
        
        // Choice of filter
        if (choice == -1) {
            do {
                choice = getFilter(filterA, filterE, filterI, filterO);
                switch (choice) {
                    case 1 :
                        filterA = !filterA;
                        break;
                    case 2 :
                        filterE = !filterE;
                        break;
                    case 3 :
                        filterI = !filterI;
                        break;
                    case 4 :
                        filterO = !filterO;
                        break;
                }
            } while (choice != -1);
            index = 1;
        }
    }
    
    
    if (filterA) {
        if (choice > len[0]){
            choice -= len[0];
        }else{
            *ver = choice;
            return 1;
        }
    }
    if (filterE) {
        if (choice > len[1]){
            choice -= len[1];
        }else{
            *ver = choice;
            return 2;
        }
    }
    if (filterI) {
        if (choice > len[2]){
            choice -= len[2];
        }else{
            *ver = choice;
            return 3;
        }
    }
    if (filterO) {
        if (choice > len[3]){
            choice -= len[3];
        }else{
            *ver = choice;
            return 4;
        }
    }
}



// Add a quantifier in the txt file.
int addQuantif(int *len[], char ** fileA, char ** fileE, char ** fileI, char ** fileO){

    // Ask for the new quantif
    char str1[100]; // Static buffer size, adjust as needed.
    int type = 0;
    printf("Quel est le type de votre quantificateur : \n"
           "1. Universel positif (A)\n"
           "2. Universel negatif (E)\n"
           "3. Existentiel positif (I)\n"
           "4. Existentiel negatif (O)\n");
    scanf("%i", &type);


    printf("Merci de saisir votre quantificateur.\n"
           "N'oubliez pas d'indiquer la position des {S} et {P} afin de pouvoir les utiliser plus tard.\n"
           "Si jamais vous souhaitez supprimer un quantificateur, merci de le faire dans le fichier.txt correspondant.\n");
    clearInputBuffer();
    fgets(str1, sizeof(str1), stdin);

    switch (type) {
        case 0:
            exit(0);
        case 1 :
            fileA = addstr(fileA, str1);
            *len[0] = *len[0] + 1;
            break;
        case 2 :
            fileE = addstr(fileE, str1);
            *len[1] = *len[1] + 1;
            break;
        case 3 :
            fileI = addstr(fileI, str1);
            *len[2] = *len[2] + 1;
            break;
        case 4 :
            fileO = addstr(fileO, str1);
            *len[3] = *len[3] + 1;
            break;
        default :
            printf("error while taking type of quantif");
            exit(0);
    }
}

// The function to show the possible filters with their status (on/off)
int getFilter(int fA, int fE, int fI, int fO) {
    int q = 0;
    printf("Activer/Desactiver les filtres : (-1 pour retourner a l'ecran de selection)\n"
           " 1. A : universel positif, statut : %3s\n"
           " 2. E : universel negatif, statut : %3s\n"
           " 3. I : existentiel positif, statut : %3s\n"
           " 4. O : existentiel negatif, statut : %3s\n",
           STATUS[fA], STATUS[fE], STATUS[fI], STATUS[fO]);
    scanf("%i", &q);
    return q;
}

int printQuantList(char ** words, int index, int len) {
    int temp = index;
    for (int i = 0; i < len; i++) {
        char * word = words[i];
        printf("%2i. %s\n", temp+i, word);
        index++;
    }
    return index;
}

// Unused for now, may need to be deleted
int getType(char* name) {
    int t;
    printf("Quel est le type de votre proposition %s ?\n", name);
    scanf("%i", &t);
    return t;
}

// Get either S, P or M value
void getName(int type, char* name) {
    if (type == S) printf("Quel est le sujet de la conclusion ?");
    if (type == P) printf("Quel est le predicat de la conclusion ?");
    if (type == M) printf("Quel est le moyen-terme ?");
    if (type == S1) printf("Quel est le sujet de la premiere premice ?");
    if (type == P1) printf("Quel est le predicat de la premiere premice ?");
    if (type == S2) printf("Quel est le sujet de la deuxieme premice ?");
    printf(" Votre choix : (max 50 caracteres)\n");
    scanf("%s", name);
}

void printPropo(char *sentence, char *propS, char *propP, char *placeholderS, char *placeholderP) {
    char res1[100];
    char res2[100];
    replacePlaceholder(sentence, propS, res1, placeholderS);
    replacePlaceholder(res1, propP, res2, placeholderP);
    printf("%s", res2);
}

char *getSentence(char ** fileA, char ** fileE, char ** fileI, char ** fileO, int q, int v){
    if (q==1) {
        return fileA[v-1];
    }
    if (q==2) {
        return fileE[v-1];
    }
    if (q==3) {
        return fileI[v-1];
    }
    if (q==4) {
        return fileO[v-1];
    }
}

void printFigures(int figNum, char ** fileA, char ** fileE, char ** fileI, char ** fileO,
                  char *S, char *P, char *M, int q1, int q2, int q3, int v1, int v2, int v3){

    char *s1 = getSentence(fileA, fileE, fileI, fileO, q1, v1);
    char *s2 = getSentence(fileA, fileE, fileI, fileO, q2, v2);
    char *s3 = getSentence(fileA, fileE, fileI, fileO, q3, v3);
    if (figNum == 1) {
        printPropo(s1, M, P, "{S}", "{P}");
        printf("\n");
        printPropo(s2, S, M, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 2) {
        printPropo(s1, P, M, "{S}", "{P}");
        printf("\n");
        printPropo(s2, S, M, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 3) {
        printPropo(s1, M, P, "{S}", "{P}");
        printf("\n");
        printPropo(s2, M, S, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 4) {
        printPropo(s1, P, M, "{S}", "{P}");
        printf("\n");
        printPropo(s2, M, S, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
}

void printFiguresMethod2(int figNum, char ** fileA, char ** fileE, char ** fileI, char ** fileO,
                  char *S, char *P, char *M, char *S1, char *P1, int q1, int q2, int q3, int v1, int v2, int v3){

    char *s1 = getSentence(fileA, fileE, fileI, fileO, q1, v1);
    char *s2 = getSentence(fileA, fileE, fileI, fileO, q2, v2);
    char *s3 = getSentence(fileA, fileE, fileI, fileO, q3, v3);
    if (figNum == 1) {
        printPropo(s1, S1, P1, "{S}", "{P}");
        printf("\n");
        printPropo(s2, S, M, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 2) {
        printPropo(s1, S1, P1, "{S}", "{P}");
        printf("\n");
        printPropo(s2, S, M, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 3) {
        printPropo(s1, S1, P1, "{S}", "{P}");
        printf("\n");
        printPropo(s2, M, S, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
    if (figNum == 4) {
        printPropo(s1, S1, P1, "{S}", "{P}");
        printf("\n");
        printPropo(s2, M, S, "{S}", "{P}");
        printf("\n");
        printPropo(s3, S, P, "{S}", "{P}");
        printf("\n");
        printf("\n");
    }
}

void replacePlaceholder(char *phrase, char *name, char *result, char* placeholder) {
    char *pos = strstr(phrase, placeholder); // on trouve la position du placeholder
    int phlen = strlen(placeholder); // on determine sa longueur

    if (pos != NULL) { // on coupe de chaque cote du placeholder et on le met au milieu
        strncpy(result, phrase, pos - phrase);
        result[pos - phrase] = '\0';

        strcat(result, name);

        strcat(result, pos + phlen);
    } else {
        strcpy(result, phrase);
    }
}

int getRules(int rules[]) {
    int choice = 0;
    printf("Liste des regles avec leur activation : (-1 pour le resultat, 0 pour quitter)\n"
           "1. Rmnt : %3s\n"
           "2. Rlh : %3s\n"
           "3. Rnn : %3s\n"
           "4. Rn : %3s\n"
           "5. Rpp : %3s\n"
           "6. Rp : %3s\n"
           "7. Ruu : %3s\n"
           "8. Raa : %3s\n"
           "9. Inint : %3s\n",
           STATUS[rules[0]], STATUS[rules[1]], STATUS[rules[2]],
           STATUS[rules[3]], STATUS[rules[4]], STATUS[rules[5]],
           STATUS[rules[6]], STATUS[rules[7]], STATUS[rules[8]]);
    scanf("%i", &choice);
    return choice;
}

void askRules(int rules[]) {
    int choice = 0;
    int loop = 1;
    while (loop) {
        choice = getRules(rules);
        switch (choice) {
            case -1:
                loop = 0;
                break;
            case 0:
                exit(0);
            case 1 :
                rules[0] = !rules[0];
                break;
            case 2 :
                rules[1] = !rules[1];
                break;
            case 3 :
                rules[2] = !rules[2];
                break;
            case 4 :
                rules[3] = !rules[3];
                break;
            case 5 :
                rules[4] = !rules[4];
                break;
            case 6 :
                rules[5] = !rules[5];
                break;
            case 7 :
                rules[6] = !rules[6];
                break;
            case 8 :
                rules[7] = !rules[7];
                break;
            case 9 :
                rules[8] = !rules[8];
                break;
            default :
                printf("error while checking the rules");
                break;
        }
    }
}

void printError(int result[]) {
}


#pragma clang diagnostic pop