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

    int method = 1;
    int needCheck = 1;

    // Declaration of the 3 quantifiers and their 3 versions
    int q1 = 0, q2 = 0, q3 = 0;
    int v1 = 0, v2 = 0, v3 = 0;

    // Declaration and allocation of the types and chains of the {predicates}
    char* propS = (char*)malloc(50 * sizeof(char));
    char* propM = (char*)malloc(50 * sizeof(char));
    char* propP = (char*)malloc(50 * sizeof(char));

    // Declaration of the figure
    int fig = 0;

    // File management
    char **fileA, **fileE, **fileI, **fileO;

    // Load files
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

    // Ask for the method the user wants
    printf("Quelle methode choissez vous ?\n"
           "1 pour saisie simple;\n"
           "2 pour saisie avancee;\n"
           "3 pour le tableau simple;\n"
           "4 pour le tableau avance.\n");
    scanf("%i", &method);

    // The various methods
    switch (method) {
        // The simple entry
        case 1:
            // Receive the three quantifiers.
            q1 = getQuantif(1, len, &v1, fileA, fileE, fileI, fileO);
            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
            
            // Receive the subject, the middle term, and the predicate
            getName(S, propS);
            if (isDeadStr(propS)) exit(0);
            getName(M, propM);
            if (isDeadStr(propM)) exit(0);
            getName(P, propP);
            if (isDeadStr(propP)) exit(0);

            // Declaration and definition of the figure
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
        
        // The advanced entry
        case 2:
            q1 = getQuantif(1, len, &v1, fileA, fileE, fileI, fileO);
            getName(S1, propM);
            if (isDeadStr(propM)) exit(0);
            getName(P1, propP);
            if (isDeadStr(propP)) exit(0);
            
            
            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            printf("Est-ce le sujet de la deuxieme premice est :\n"
                   "1. %s\n2. %s\nAutre : ecrire votre sujet directement.\n",
                   propM, propP);
            scanf("%s", propS);
            if (isDeadStr(propS)) exit(0);
            if (!strcmp(propS, "1")) {
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                getName(S, propS);
                fig = 3;
            } else if (!strcmp(propS, "2")) {
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                // TODO exchange(&propM, &propP);
                exchange(propM, propP);
                fig = 4;
                getName(S, propS);
            } else {
                printf("Quel est le predicat de la deuxieme premice :\n"
                       "1. %s\n2. %s\n", propM, propP);
                int choice;
                scanf("%i", &choice);
                switch (choice) {
                    case 1 :
                        // TODO exchange(&propM, &propP);
                        exchange(propM, propP);
                        fig = 2;
                        break;
                    case 2 :
                        // TODO exchange(&propM, &propP);
                        exchange(propM, propP);
                        fig = 1;
                        break;
                    default :
                        printf("error while exchanging PropP and PropM");
                        exit(0);
                }
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
            }

            printf("votre syllogisme est : ");
            printFigures(fig, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);
            break;
        // The simple table
        case 3:
            needCheck = 0;
            printTable();
            break;

        // The advanced Table
        case 4 :
            needCheck = 0;
            printTableDetailled();
            break;

        case 5 :
            // test case
            printf("\e[1;34mThis is a blue text.\e[0m");
            break;
        default :
            // Check if q is valid beforehand
            printf("error while inputing method");
            exit(0);
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

        // Validate (or not) the syllogism 
        
        int rules[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        // In order : Rmt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint

        // Check if the syllogism is valid, and indicate the rules it broke if not
        int loop = 1;
        while(loop) {

            printf("Votre syllogisme est :\n");
            printFigures(fig, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);

            askRules(rules);

            int res = verify(fig, q1, q2, q3, rules);
            if (res) printf("\nLe syllogisme est valide avec ces regles.\n");
            else printf("\nLe syllogisme n'est pas valide avec ces regles.\n");
            printf("Continuer ? (1 pour oui, 0 pour finir)\n");
            scanf("%i", &loop);
        }
    }

    // save files in case of modification
    //save(len[0], fileA, "Chaine_A");
    //save(len[1], fileE, "Chaine_E");
    //save(len[2], fileI, "Chaine_I");
    //save(len[3], fileO, "Chaine_O");

    return 0;

}

