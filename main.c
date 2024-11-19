#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "interface.h"
#include "save.h"
#include "traitement.h"

int main() {


    printf("Bienvenue au pays des merveilles ( surtout des syllogismes )\n"
           "Vous pouvez a chaque choix taper 0 pour quitter le programme\n"
           "Credits : BABIN Celestin, DZIGUA Saba, MALHOUD Alexandre, MICHEL Thomas\n");

    // get method
    int method = 1;
    int needCheck = 1;

    // declarer 3 quantificateurs et 3 versions de chaque
    int q1, q2, q3;
    int v1 = 0, v2 = 0, v3 = 0;

    // declarer + allouer les types et chaines des {predicats}
    char* propS = (char*)malloc(50 * sizeof(char));
    char* propM = (char*)malloc(50 * sizeof(char));
    char* propP = (char*)malloc(50 * sizeof(char));

    // declarer la figure
    int fig = 0;

    // file management
    char **fileA, **fileE, **fileI, **fileO;

    // load files
    int len[4];
    int ptr = 0;
    restore(&ptr, &fileA, "Chaines_A");
    len[0] = ptr;
    restore(&ptr, &fileE, "Chaines_E");
    len[1] = ptr;
    restore(&ptr, &fileI, "Chaines_I");
    len[2] = ptr;
    restore(&ptr, &fileO, "Chaines_O");
    len[3] = ptr;

    printf("Quelle methode choissez vous ?\n"
           "1 pour saisie simple.\n"
           "2 pour saisie avancee.\n"
           "3 pour le tableau.\n");
    scanf("%i", &method);

    switch (method) {
        case 1:
            q1 = getQuantif(1, len, &v1, fileA, fileE, fileI, fileO);
            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);

            getName(S, propS);
            if (isDeadStr(propS)) exit(0);
            getName(M, propM);
            if (isDeadStr(propM)) exit(0);
            getName(P, propP);
            if (isDeadStr(propP)) exit(0);

            // Declaration et defintion de la figure
            printf("Choissisez votre figure : \n");
            printf("Figure 1 : \n");
            printFigures(1, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 2 : \n");
            printFigures(2, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 3 : \n");
            printFigures(3, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 4 : \n");
            printFigures(4, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            scanf("%i", &fig);
            if (isDead(fig)) exit(0);
            break;

        case 2:
            q1 = getQuantif(1, len, &v1, fileA, fileE, fileI, fileO);
            getName(S1, propM);
            if (isDeadStr(propM)) exit(0);
            getName(P1, propP);
            if (isDeadStr(propP)) exit(0);

            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            printf("Est-ce le sujet de la deuxieme premice est :\n"
                   "1. %s\n 2. %s\n autre : ecrire votre sujet directement.\n",
                   propM, propP);
            scanf("%s", propS);
            if (isDeadStr(propS)) exit(0);
            if (strcmp(propS, "1")) {
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                getName(S, propS);
                fig = 3;
            } else if (strcmp(propS, "2")) {
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                propS = propP;
                propP = propM;
                propM = propS;
                fig = 4;
                getName(S, propS);
            } else {
                getName(S2, propS);
                printf("Quel est le predicat de la deuxieme premice :\n"
                       "1. %s\n2. %s\n", propM, propP);
                int choice;
                scanf("%i", &choice);
                switch (choice) {
                    case 0:
                        exit(0);
                    case 1 :
                        fig = 2;
                        break;
                    case 2 :
                        fig = 1;
                        break;
                }
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
            }

            // Declaration et defintion de la figure
            printf("Choissisez votre figure : \n");
            printf("Figure 1 : \n");
            printFigures(1, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 2 : \n");
            printFigures(2, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 3 : \n");
            printFigures(3, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            printf("Figure 4 : \n");
            printFigures(4, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            scanf("%i", &fig);
            if (isDead(fig)) exit(0);
            break;

        case 3:
            needCheck = 0;
            printTableau();
            break;
    }

    if (needCheck) {

    /*
        // Verifications
        printf("Q1 : %c V%i ; ", QUANTLIST[q1], v1);
        printf("Q2 : %c V%i ; ", QUANTLIST[q2], v2);
        printf("Q3 : %c V%i", QUANTLIST[q3], v3);
        printf("\n");


        printf("S : %s ;\n ", propS);
        printf("M : %s ;\n ", propM);
        printf("P : %s", propP);
        printf("\n");
    */

        // Valider (ou non) le syllogisme

        int rules[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        // dans l'ordre : Rmnt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint

        int loop = 1;
        while(loop) {

            printf("Votre syllogisme est :\n");
            printFigures(fig, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);

            askRules(rules);
            int res = verify(q1, q2, q3, rules);
            if (res) printf("\nLe syllogisme est valide avec ces regles.\n");
            else printf("\nLe syllogisme n'est pas valide avec ces regles.\n");
            printf("Continuer ? (1 pour oui, 0 pour finir)\n");
            scanf("%i", &loop);
        }
    }

    return 0;

}

