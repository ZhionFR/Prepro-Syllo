#include "stdio.h"

#include "traitement.h"


// pas de panique
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"


int verify(int fig, int q1, int q2, int q3, int rules[]){

    int u1, u2, u3; // Universal booleans
    int p1, p2, p3; // Positif booleans
    // Figure booleans
    int f1 = (fig == 1);
    int f2 = (fig == 2);
    int f3 = (fig == 3);
    int f4 = (fig == 4);

    // Transform qx in two booleans px and ux according to the value they have
    translate(q1, &p1, &u1);
    translate(q2, &p2, &u2);
    translate(q3, &p3, &u3);

    // Rmt (Regle du moyen-terme) : The quantity of M need to be universal in one of the two premises at least.
    int Rmt = (((f1 || f3) && u1) || ((f2 || f4) && (!p1))) || (((f3 || f4) && u2) || ((f1 || f2) && (!p2)));

    // Rlh (Regle du latius hos) : The quantity of one term of the conclusion is universal only if it is in the premise where it belongs.

    // Check if the conclusion's subject is universal and if so, if in the second premise, the word is universal too
    int s;
    if(u3) s = (((f1 || f2) && u2) || ((f3 || f4) && (!p2)));
    else s = 1;
    // Check if the conclusion's predicate is universal and if so, if in the first premise, the word is universal too
    int p;
    if(!p3) p = (((f2 || f4) && (u1)) || ((f1 || f3) && (!p1)));
    else p = 1;

    // Check if both the conditions are required for the rule
    int Rlh = (s && p);

    // Rnn : Two negative premises can't give a conclusion
    int Rnn = (p1 || p2);
    
    // Rn : If a premise is negative, the conclusion is negative too
    int Rn;
    if((!p1) || (!p2)) Rn = (!p3);
    else Rn = 1;

    // Rpp : Two particular premises can't give a conclusion
    int Rpp = u1 || u2;
    
    // Rp : If a premise is particular the conclusion is particular too
    int Rp;
    if((!u1) || (!u2)) Rp =(!u3);
    else Rp = 1;
    
    // Ruu : Two universal premises can't give a particular conclusion
    int Ruu = !(u1 && u2 && !u3);

    // Raa : Two affirmative premises give an affirmative conclusion
    int Raa;
    if(p1 && p2) Raa = p3;
    else Raa = 1;

    int Inint;

    // Check if a syllogism with an existential conclusion is still valid after changing to a universal conclusion ; in which case the original syllogism is uninteresting

    if (q3 == 3) Inint = verify(fig, q1, q2, 1, rules);
    else if (q3 == 4) Inint = verify(fig, q1, q2, 2, rules);
    else Inint = 1;

    // Check which rules are on or not
    int res = (Rmt || !rules[0]) &&
              (Rlh || !rules[1]) &&
              (Rnn || !rules[2]) &&
              (Rn || !rules[3]) &&
              (Rpp || !rules[4]) &&
              (Rp || !rules[5]) &&
              (Ruu || !rules[6]) &&
              (Raa || !rules[7]) &&
              (Inint || !rules[8]);

    return res;
}
// Transform q in two booleans p and u according to the value they have 
void translate(int q, int *p, int *u) {
    switch (q) {
        case 1 :
            *p = 1;
            *u = 1;
            break;
        case 2 :
            *p = 0;
            *u = 1;
            break;
        case 3 :
            *p = 1;
            *u = 0;
            break;
        case 4 :
            *p = 0;
            *u = 0;
            break;
        default :
            // Check if q is valid beforehand
                printf("error while inputing q");
            break;
    }
}

void printTable() {
    printf(""
           "::NumFig:: Q1 :: Q2 :: Q3 :: validite :: validite sans existence :: validite avec inint ::\n"
           "::------::----::----::----::----------::-------------------------::---------------------::\n");
    for(int fig = 1; fig < 5; fig++) {
        for (int q1 = 1; q1 < 5; q1++) {
            for (int q2 = 1; q2 < 5; q2++) {
                for (int q3 = 1; q3 < 5; q3++) {
                    printLign(fig, q1, q2, q3);
                }
            }
        }
    }
}

void printDetailedTable() {
    printf(""
           "::NumFig:: Q1 :: Q2 :: Q3 :: Rmt :: Rlh :: Rnn :: Rn  :: Rpp :: Rp  :: Ruu :: Raa ::\n"
           "::------::----::----::----::-----::-----::-----::-----::-----::-----::-----::-----::\n");
    for(int fig = 1; fig < 5; fig++) {
        for (int q1 = 1; q1 < 5; q1++) {
            for (int q2 = 1; q2 < 5; q2++) {
                for (int q3 = 1; q3 < 5; q3++) {
                    printDetailedLign(fig, q1, q2, q3);
                }
            }
        }
    }
}

// In order : Rmt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint

const int ruleNoIn[9] = {1, 1, 1, 1, 1, 1, 1, 1, 0};
const int ruleNoInEx[9] = {1, 1, 1, 1, 1, 1, 0, 1, 0};
const int ruleAll[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};


void printLign(int fig, int q1, int q2, int q3) {
    printf("::   %i  ::  %c ::  %c ::  %c ::%s::       %s        ::      %s     ::\n",
            fig, QUANTIFS[q1], QUANTIFS[q2], QUANTIFS[q3],
            BOOL[verify(fig, q1, q2, q3, ruleNoIn)],
            BOOL[verify(fig, q1, q2, q3, ruleNoInEx)],
            BOOL[verify(fig, q1, q2, q3, ruleAll)]);
}

const int ruleRmt[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
const int ruleRlh[9] = {0, 1, 0, 0, 0, 0, 0, 0, 0};
const int ruleRnn[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};
const int ruleRn[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};
const int ruleRpp[9] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
const int ruleRp[9] = {0, 0, 0, 0, 0, 1, 0, 0, 0};
const int ruleRuu[9] = {0, 0, 0, 0, 0, 0, 1, 0, 0};
const int ruleRaa[9] = {0, 0, 0, 0, 0, 0, 0, 1, 0};

void printDetailedLign(int fig, int q1, int q2, int q3) {
    printf("::   %i  ::  %c ::  %c ::  %c :: %s :: %s :: %s :: %s :: %s :: %s :: %s :: %s ::\n",
            fig, QUANTIFS[q1], QUANTIFS[q2], QUANTIFS[q3],
            BOOLD[verify(fig, q1, q2, q3, ruleRmt)],
            BOOLD[verify(fig, q1, q2, q3, ruleRlh)],
            BOOLD[verify(fig, q1, q2, q3, ruleRnn)],
            BOOLD[verify(fig, q1, q2, q3, ruleRn)],
            BOOLD[verify(fig, q1, q2, q3, ruleRpp)],
            BOOLD[verify(fig, q1, q2, q3, ruleRp)],
            BOOLD[verify(fig, q1, q2, q3, ruleRuu)],
            BOOLD[verify(fig, q1, q2, q3, ruleRaa)]);
}

void printWrongRules(int fig, int q1, int q2, int q3, int rules[]) {
    int ruleInint[9] = { rules[0], rules[1], rules[2], rules[3],
                         rules[4], rules[5], rules[6], rules[7], 1};
    int Rmt = rules[0] && verify(fig, q1, q2, q3, ruleRmt);
    int Rlh = rules[1] && verify(fig, q1, q2, q3, ruleRlh);
    int Rnn = rules[2] && verify(fig, q1, q2, q3, ruleRnn);
    int Rn = rules[3] && verify(fig, q1, q2, q3, ruleRn);
    int Rpp = rules[4] && verify(fig, q1, q2, q3, ruleRpp);
    int Rp = rules[5] && verify(fig, q1, q2, q3, ruleRp);
    int Ruu = rules[6] && verify(fig, q1, q2, q3, ruleRuu);
    int Raa = rules[7] && verify(fig, q1, q2, q3, ruleRaa);
    int Inint = rules[8] && verify(fig, q1, q2, q3, ruleInint);

    if (!Rmt) {
        printf("\nPour la regle Rmt :\n"
               "\n"
               "La premiere premisse debute par un quantificateur particulier;\n"
               "la seconde premisse debute egalement par un quantificateur particulier.\n"
               "Comme deux premisses particulieres ne peuvent donner de conclusion,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Rlh) {
        printf("\nPour la regle Rlh :\n"
               "\n"
               "Au moins l\'un des deux termes de la conclusion est universel;\n"
               "Ce meme terme est particulier dans la premisse a laquelle il appartient.\n"
               "Comme la quantite d\'un terme de la conclusion ne peut etre universelle que si elle l\'est dans la premisse contenant ce terme.\n"
               "La conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Rnn) {
        printf("\nPour la regle Rnn :\n"
               "\n"
               "La premiere premisse debute par un quantificateur negatif ;\n"
               "la seconde premisse debute par egalement par un quantificateur negatif.\n"
               "Comme deux premisses negatives ne peuvent donner de conclusion,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Rn) {
        printf("\nPour la regle Rn :\n"
               "\n"
               "L\'une des deux premiere premisses est negative ;\n"
               "la conclusion debute par une premisse positive.\n"
               "Comme une la presence d\'une premisse negative donne une conclusion positive,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Rpp) {
        printf("\nPour la regle Rpp :\n"
               "\n"
               "La premiere premisse debute par un quantificateur positif ;\n"
               "la seconde premisse debute egalement par un quantificateur positif;\n"
               "la conclusion debute par un quantificateur negatif.\n"
               "Comme deux premisses positives ne peuvent donner une conclusion positive,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Rp) {
        printf("\nPour la regle Rp :\n"
               "\n"
               "L\'une des premisses debute par un quantificateur particulier.\n"
               "Comme une premisse particuliere donnent une conclusion particuliere,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Ruu) {
        printf("\nPour la regle Ruu :\n"
               "\n"
               "La premiere premisse debute par un quantificateur universel ;\n"
               "la seconde premisse debute egalement par un quantificateur universel ;\n"
               "la conclusion debute par un quantificateur particulier.\n"
               "Comme deux premisses universelles ne donnent pas de conclusion particuliere,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide\n");
    }
    if (!Raa) {
        printf("\nPour la regle Raa :\n"
               "\n"
               "La premiere premisse debute par un quantificateur positif;\n"
               "la seconde premisse debute egalement par un quantificateur positif ;\n"
               "la conclusion debute par un quantificateur negatif.\n"
               "Comme deux premisses positives donnent une conclusion positive,\n"
               "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    }
    if (!Inint) {
        printf("\nPour la regle Inint :\n"
               "\n"
               "Le syllogisme est ininteressant.\n"
               "En effet, on peut trouver un syllogisme plus fort avec une conclusion universelle.\n");
    }


}


void printManual() {
    printf("\nPour la regle Rmt :\n"
           "\n"
           "La premiere premisse debute par un quantificateur particulier;\n"
           "la seconde premisse debute egalement par un quantificateur particulier.\n"
           "Comme deux premisses particulieres ne peuvent donner de conclusion,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Rlh :\n"
           "\n"
           "Au moins l\'un des deux termes de la conclusion est universel;\n"
           "Ce meme terme est particulier dans la premisse a laquelle il appartient.\n"
           "Comme la quantite d\'un terme de la conclusion ne peut etre universelle que si elle l\'est dans la premisse contenant ce terme.\n"
           "La conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Rnn :\n"
           "\n"
           "La premiere premisse debute par un quantificateur negatif ;\n"
           "la seconde premisse debute par egalement par un quantificateur negatif.\n"
           "Comme deux premisses negatives ne peuvent donner de conclusion,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Rn :\n"
           "\n"
           "L\'une des deux premiere premisses est negative ;\n"
           "la conclusion debute par une premisse positive.\n"
           "Comme une la presence d\'une premisse negative donne une conclusion positive,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Rpp :\n"
           "\n"
           "La premiere premisse debute par un quantificateur positif ;\n"
           "la seconde premisse debute egalement par un quantificateur positif;\n"
           "la conclusion debute par un quantificateur negatif.\n"
           "Comme deux premisses positives ne peuvent donner une conclusion positive,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Rp :\n"
           "\n"
           "L\'une des premisses debute par un quantificateur particulier.\n"
           "Comme une premisse particuliere donnent une conclusion particuliere,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Ruu :\n"
           "\n"
           "La premiere premisse debute par un quantificateur universel ;\n"
           "la seconde premisse debute egalement par un quantificateur universel ;\n"
           "la conclusion debute par un quantificateur particulier.\n"
           "Comme deux premisses universelles ne donnent pas de conclusion particuliere,\n"
           "la conclusion saisie n\'est pas deductible des deux premisses et le syllogisme n\'est donc pas valide\n");
    printf("\nPour la regle Raa :\n"
           "\n"
           "La premiere premisse debute par un quantificateur positif;\n"
           "la seconde premisse debute egalement par un quantificateur positif ;\n"
           "la conclusion debute par un quantificateur negatif.\n"
           "Comme deux premisses positives donnent une conclusion positive,\n"
           "la conclusion saisie n\'est pas deeductible des deux premisses et le syllogisme n\'est donc pas valide.\n");
    printf("\nPour la regle Inint :\n"
           "\n"
           "Le syllogisme est ininteressant.\n"
           "En effet, on peut trouver un syllogisme plus fort avec une conclusion universelle.\n");

}


#pragma clang diagnostic pop