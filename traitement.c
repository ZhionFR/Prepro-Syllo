#include "stdio.h"

#include "traitement.h"

int verify(int q1, int q2, int q3, int rules[]){

    int u1, u2, u3; // universel bool
    int p1, p2, p3; // positif bool

    translate(q1, &p1, &u1);
    translate(q2, &p2, &u2);
    translate(q3, &p3, &u3);

    int Rmnt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint; // rules result

    Rmnt = !rules[0] || (!((!u1) && (!u2)));
    Rlh = !rules[1] || (((u1 && u3) || (u1 && !p3) || (!u1 && p3)) && (u2 && u3) || (!u2 && !u3));
    Rnn = !rules[2] || (((!p1) && (!p2) && (!p3)) || p3);
    Rn = !rules[3] || (((!p1) || (!p2)) && (!p3) || p3);
    Rpp = !rules[4] || (((!u1) && (!u2) && (!u3)) || u3);
    Rp = !rules[5] || ((((!u1) || (!u2)) && (!u3)) || u3);
    Ruu = !rules[6] || ((u1 && u2 && u3) || !u3);
    Raa = !rules[7] || ((p1 && p2 && p3) || !p3);

    // Inint
    if (rules[8] && q3 == 3) Inint = verify(q1, q2, 1, rules);
    else if (rules[8] && q3 == 4) Inint = verify(q1, q2, 2, rules);

    int res = Rmnt && Rlh && Rnn && Rn && Rpp && Rp && Ruu && Raa && Inint;

    return res;
}

void translate(int q, int *p, int *u) {
    switch (q) {
        case 0 :
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
