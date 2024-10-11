#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "interface.h"

char* FIGLIST[25] = {"NotAFig", "Barbara", "Barbari", "Celarent", "Celaront", "Darii", "Ferio", "Cesare", \
                    "Cesaro", "Camestres", "Camestrop", "Festino", "Baroco", "Darapti", "Felapton", "Disamis", \
                    "Datisi", "Bocardo", "Ferison", "Bamalip", "Calemes", "Calemop", "Dismatis", "Fesapo",  \
                    "Fresison"};

int isDead(int value) {
    return value == KILL;
}

int isDeadStr(char* name) {
    return (strcmp(name, "0")) == KILL;
}

int getQuantif(int num) {
    int q = 0;
    printf("Quel est votre quantificateur numero %i ? \n"
           " 1. A : universel positif\n"
           " 2. E : universel negatif\n"
           " 3. I : existentiel positif\n"
           " 4. O : existentiel negatif\n", num);
    scanf("%i", &q);
    return q;
}

int printQuantList(int quantNum) {
    int q;
    int n = 5; // n is len of list but 5 for test
    printf("Quel formulation est adaptee a votre %c sur Q%i ? (-1 pour faire retour) \n", QUANTLIST[quantNum], quantNum);
    for (int i = 0; i < n; i++) {
        printf("%2i. Quant %c example\n", i, QUANTLIST[quantNum]);
    }
    scanf("%i", &q);
    return q;
}

int getType(char* name) {
    int t;
    printf("Quel est le type de votre proposition %s ?\n", name);
    scanf("%i", &t);
    return t;
}

void getName(int type, char* name) {
    if (type == S) printf("Quel est le sujet de la conclusion ?");
    if (type == P) printf("Quel est le predicat de la conclusion ?");
    if (type == M) printf("Quel est le moyen-terme ?");
    printf(" Votre choix : (max 50 caracteres)\n");
    scanf("%s", name);
}

int getFig(int q1, int q2, int q3, char* propS, char* propM, char* propP) {
    int fig;
    printf("Quel est le type de figure concerné ? \n\n");
    for (int i = 1; i < 24; i++) printf("%2i. Figure %10s. \n", i, FIGLIST[i]);
    scanf("%i", &fig);
    return fig;
}
