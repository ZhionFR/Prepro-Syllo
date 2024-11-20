#include "stdio.h"

#include "traitement.h"

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

    // Rmt (Règle du moyen-terme) : The quantity of M need to be universal in one of the two premises at least.
    int Rmt = (((f1 || f3) && u1) || ((f2 || f4) && (!p1))) || (((f3 || f4) && u2) || ((f1 || f2) && (!p2)));

    // Rlh (Règle du latius hos) : The quantity of one term of the conclusion is universal only if it is in the premise where it belongs.

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

void printTableau() {
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
/*
void printTableauDetaille() {
    printf(""
           "::NumFig:: Q1 :: Q2 :: Q3 :: Rmt :: Rlh :: Rnn :: Rn :: Rpp :: Rp :: Ruu :: Raa ::\n"
           "::------::----::----::----::-----::-----::-----::----::-----::----::-----::-----::\n");
    for(int fig = 1; fig < 5; fig++) {
        for (int q1 = 1; q1 < 5; q1++) {
            for (int q2 = 1; q2 < 5; q2++) {
                for (int q3 = 1; q3 < 5; q3++) {
                    printLignDetailled(fig, q1, q2, q3);
                }
            }
        }
    }
}
*/

// In order : Rmt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint

const int ruleNoIn[9] = {1, 1, 1, 1, 1, 1, 1, 1, 0};
const int ruleNoInEx[9] = {1, 1, 1, 1, 1, 1, 0, 1, 0};
const int ruleAll[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};


void printLign(int fig, int q1, int q2, int q3) {
    if (verify(fig, q1, q2, q3, ruleNoInEx) || verify(fig, q1, q2, q3, ruleNoIn) || verify(fig, q1, q2, q3, ruleAll)) {
        printf("::   %i  ::  %c ::  %c ::  %c ::%s::       %s        ::      %s     ::\n",
               fig, QUANTIFS[q1], QUANTIFS[q2], QUANTIFS[q3],
                BOOL[verify(fig, q1, q2, q3, ruleNoIn)],
                BOOL[verify(fig, q1, q2, q3, ruleNoInEx)],
                BOOL[verify(fig, q1, q2, q3, ruleAll)]);
    }
}

/*

const int ruleRmt[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
const int ruleRlh[9] = {0, 1, 0, 0, 0, 0, 0, 0, 0};
const int ruleRnn[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};
const int ruleRn[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};
const int ruleRpp[9] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
const int ruleRp[9] = {0, 0, 0, 0, 0, 1, 0, 0, 0};
const int ruleRuu[9] = {0, 0, 0, 0, 0, 0, 1, 0, 0};
const int ruleRaa[9] = {0, 0, 0, 0, 0, 0, 0, 1, 0};


void printLignDetailled(int fig, int q1, int q2, int q3) {
    printf("::   %i  ::  %c ::  %c ::  %c :: %s :: %s :: %s :: %s :: %s :: %s :: %s :: %s ::\n",
           fig, QUANTIFS[q1], QUANTIFS[q2], QUANTIFS[q3],
           BOOL[verify(fig, q1, q2, q3, ruleRmt)],
           BOOL[verify(fig, q1, q2, q3, ruleRlh)],
           BOOL[verify(fig, q1, q2, q3, ruleRnn)],
           BOOL[verify(fig, q1, q2, q3, ruleRn)],
           BOOL[verify(fig, q1, q2, q3, ruleRpp)],
           BOOL[verify(fig, q1, q2, q3, ruleRp)],
           BOOL[verify(fig, q1, q2, q3, ruleRuu)],
           BOOL[verify(fig, q1, q2, q3, ruleRaa)]);
}
*/

void exchange(char **wrd1, char **wrd2) {
    char *temp = *wrd1;
    *wrd1 = *wrd2;
    *wrd2 = temp;
}
