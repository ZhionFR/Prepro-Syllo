#include "stdio.h"

#include "traitement.h"

int verify(int q1, int q2, int q3, int rules[]){

    int u1, u2, u3; // Universal booleans
    int p1, p2, p3; // Positif booleans

    // Transform qx in two booleans px and ux according to the value they have
    translate(q1, &p1, &u1);
    translate(q2, &p2, &u2);
    translate(q3, &p3, &u3);

    int Rmt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint; // Rules result


    // Rmt (Règle du moyen-terme) : The quantity of M need to be universal in one of the two premises at least.
    Rmt = !((!u1) && (!u2));
    
    // Rlh (Règle du latius hos) : The quantity of one term of the conclusion can't be universal if it is in the premise where he belongs.
    Rlh = ((u1 && u3) || (u1 && !p3) || (!u1 && p3)) && (u2 && u3) || (!u2 && !u3);
    
    // Rnn : Two negative premises can't give a negative conclusion
    Rnn = ((!p1) && (!p2) && (!p3)) || p3;
    
    // Rn : If a premise is negative, the conclusion is negative too
    Rn = ((!p1) || (!p2)) && (!p3) || p3;
    
    // Raa : Two affirmative premises give an affirmative conclusion
    Raa = (p1 && p2 && p3) || !p3;
    
    // Rpp : Two particular premises can't give a conclusion
    Rpp = ((!u1) && (!u2) && (!u3)) || u3;
    
    // Rp : If a premise is particular 
    Rp = (((!u1) || (!u2)) && (!u3)) || u3;
    
    // Ruu : Two universal premises can't give a particular conclusion
    Ruu = (u1 && u2 && u3) || !u3;

    // Check if a syllogism with an existential conclusion is still valid after changing to an universal conclusion ; in which case the original syllogism is uninteresting
    if (q3 == 3) Inint = verify(q1, q2, 1, rules);
    else if (q3 == 4) Inint = verify(q1, q2, 2, rules);

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
        case 0 :
            // Check if q is valid beforehand
            printf("error while inputing q");
            break;
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

const int ruleNoIn[9] = {1, 1, 1, 1, 1, 1, 1, 1, 0};
const int ruleNoInEx[9] = {1, 1, 1, 1, 1, 1, 0, 1, 0};
const int ruleAll[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

void printLign(int fig, int q1, int q2, int q3) {
    printf("::   %i  ::  %c ::  %c ::  %c ::%s::       %s        ::      %s     ::\n",
           fig, QUANTIFS[q1], QUANTIFS[q2], QUANTIFS[q3],
           BOOL[verify(q1, q2, q3, ruleNoIn)],
           BOOL[verify(q1, q2, q3, ruleNoInEx)],
           BOOL[verify(q1, q2, q3, ruleAll)]);
}

