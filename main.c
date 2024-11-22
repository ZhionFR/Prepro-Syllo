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

    int *lentPtr[4];
    for (int i = 0; i < 4; i++){
        lentPtr[i] = &len[i];
    }

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
            if (q1 == -2) {
                addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                goto save;
            }
            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            if (q2 == -2) {
                addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                goto save;
            }
            q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
            if (q3 == -2) {
                addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                goto save;
            }

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
            // S1 et P1
            char* propS1 = (char*)malloc(50 * sizeof(char));
            char* propP1 = (char*)malloc(50 * sizeof(char));

            q1 = getQuantif(1, len, &v1, fileA, fileE, fileI, fileO);
            if (q1 == -2) {
                addQuantif( lentPtr, fileA, fileE, fileI, fileO);
                goto save;
            }
            getName(S1, propS1);
            if (isDeadStr(propM)) exit(0);
            getName(P1, propP1);
            if (isDeadStr(propP)) exit(0);
            
            
            q2 = getQuantif(2, len, &v2, fileA, fileE, fileI, fileO);
            if (q2 == 2) {
                addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                goto save;
            }
            printf("Est-ce le sujet de la deuxieme premice est :\n"
                   "1. %s\n2. %s\nAutre : ecrire votre sujet directement.\n",
                   propS1, propP1);
            scanf("%s", propS);
            if (isDeadStr(propS)) exit(0);
            if (!strcmp(propS, "1")) {
                getName(S, propS);
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                if (q3 == -2) {
                    addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                    goto save;
                }
                propM = propS1;
                propP = propP1;
                fig = 3;
            } else if (!strcmp(propS, "2")) {
                getName(S, propS);
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                if (q3 == -2) {
                    addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                    goto save;
                }
                propM = propP1;
                propP = propS1;
                fig = 4;
            } else {
                printf("Quel est le predicat de la deuxieme premice :\n"
                       "1. %s\n2. %s\n", propS1, propP1);
                int choice;
                scanf("%i", &choice);
                switch (choice) {
                    case 1 :
                        propM = propS1;
                        propP = propP1;
                        fig = 2;
                        break;
                    case 2 :
                        propM = propP1;
                        propP = propS1;
                        fig = 1;
                        break;
                    default :
                        printf("error while exchanging PropP and PropM");
                        exit(0);
                }
                q3 = getQuantif(3, len, &v3, fileA, fileE, fileI, fileO);
                if (q3 == -2) {
                    addQuantif(lentPtr, fileA, fileE, fileI, fileO);
                    goto save;
                }
            }

            break;
        // The simple table
        case 3:
            needCheck = 0;
            printTable();
            break;

        // The advanced Table
        case 4 :
            needCheck = 0;
            printDetailedTable();
            break;

        case 5 :
            // test case
            goto save;
            // test case end
            needCheck = 0;
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
        int stop = 0;
        while(!stop) {

            printf("Votre syllogisme est :\n");
            printFigures(fig, fileA, fileE, fileI, fileO, propS, propP, propM,
                         q1, q2, q3, v1, v2, v3);

            askRules(rules);

            int res = verify(fig, q1, q2, q3, rules);
            if (res) printf("\nLe syllogisme est valide avec ces regles.\n");
            else {
                printf("\nLe syllogisme n'est pas valide avec ces regles.\n");
                printf(""
                       "::NumFig:: Q1 :: Q2 :: Q3 :: Rmt :: Rlh :: Rnn :: Rn  :: Rpp :: Rp  :: Ruu :: Raa ::\n"
                       "::------::----::----::----::-----::-----::-----::-----::-----::-----::-----::-----::\n");
                printDetailedLign(fig, q1, q2, q3);
                printf("Pour l'explication des regles non respectees, taper -1.\n");
            }
            printf("Continuer ? (0 pour oui, 1 pour finir, 2 pour le manuel des regles)\n");
            scanf("%i", &stop);
            if (stop == -1){
                printWrongRules(fig, q1, q2, q3, rules);
            }
            if (stop == 2){
                printManual();
            }
        }
    }

    // save files in case of modification

save:

    /*
    printf("Quantificateurs sauvegardes : \n");
    int index = 1;
    printf("\n=== Universel positif (A) : \n");
    index = printQuantList(fileA, index, len[0]);
    printf("\n=== Universel negatif (E) : \n");
    index = printQuantList(fileE, index, len[1]);
    printf("\n=== Existentiel positif (I) : \n");
    index = printQuantList(fileI, index, len[2]);
    printf("\n=== Existentiel negatif (O) : \n");
    index = printQuantList(fileO, index, len[3]);
    */

    printf("Saving\n");
    save(len[0], fileA, "Chaines_A");
    save(len[1], fileE, "Chaines_E");
    save(len[2], fileI, "Chaines_I");
    save(len[3], fileO, "Chaines_O");
    printf("Saved\n");

    return 0;

}

