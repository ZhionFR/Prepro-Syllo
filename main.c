#include "stdio.h"
#include "stdlib.h"

#include "interface.h"


int main() {

    // TODO : Definition des listes depuis save.c

    printf("Bienvenue au pays des merveilles ( surtout des syllogismes )\n"
           "Vous pouvez a chaque choix taper 0 pour l'annuler (sauf pour les noms pour l'instant)\n"
           "Credits : BABIN Celestin, DZIGUA Saba, MALHOUD Alexandre, MICHEL Thomas\n");
    // declarer 3 quantificateurs et 3 versions de chaque
    int q1, q2, q3;
    int v1 = 0, v2 = 0, v3 = 0;
    // definitions
    while (v1 < 1){
        q1 = getQuantif(1);
        if (isDead(q1)) exit(0);
        v1 = printQuantList(q1);
        if (isDead(v1)) exit(0);
    }
    while (v2 < 1){
        q2 = getQuantif(2);
        if (isDead(q2)) exit(0);
        v2 = printQuantList(q2);
        if (isDead(v2)) exit(0);
    }
    while (v3 < 1){
        q3 = getQuantif(3);
        if (isDead(q3)) exit(0);
        v3 = printQuantList(q3);
        if (isDead(v3)) exit(0);
    }


    // declarer + allouer les types et chaines des {predicats}
    char* propS = (char*)malloc(50 * sizeof(char));
    char* propM = (char*)malloc(50 * sizeof(char));
    char* propP = (char*)malloc(50 * sizeof(char));


    getName(S, propS);
    if (isDeadStr(propS)) exit(0);
    getName(M, propM);
    if (isDeadStr(propM)) exit(0);
    getName(P, propP);
    if (isDeadStr(propP)) exit(0);

    // Declaration et defintion de la figure
    printf("Choissisez votre figure : \n");
    printf("Figure 1 : \n");
    printfigureBeta(1, q1, q2, q3, v1, v2, v3, propS, propM, propP);
    printf("Figure 2 : \n");
    printfigureBeta(2, q1, q2, q3, v1, v2, v3, propS, propM, propP);
    printf("Figure 3 : \n");
    printfigureBeta(3, q1, q2, q3, v1, v2, v3, propS, propM, propP);
    printf("Figure 4 : \n");
    printfigureBeta(4, q1, q2, q3, v1, v2, v3, propS, propM, propP);
    int fig = 0;
    scanf("%i", &fig);


    // Verifications
	printf("Q1 : %c V%i ; ", QUANTLIST[q1], v1);
    printf("Q2 : %c V%i ; ", QUANTLIST[q2], v2);
    printf("Q3 : %c V%i", QUANTLIST[q3], v3);
    printf("\n");

    printf("S : %15s ; ", propS);
    printf("M : %15s ; ", propM);
    printf("P : %15s", propP);
    printf("\n");


    return 0;
}

