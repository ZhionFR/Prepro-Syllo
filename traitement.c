#include "stdio.h"

#include "traitement.h"

int verify(int q1, int q2, int q3, int rules[]){

    int u1, u2, u3; // universel bool
    int p1, p2, p3; // positif bool

    translate(q1, &p1, &u1);
    translate(q2, &p2, &u2);
    translate(q3, &p3, &u3);

    int Rmnt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint; // rules result

    Rmnt = !((!u1) && (!u2));
    Rlh = ((u1 && u3) || (u1 && !p3) || (!u1 && p3)) && (u2 && u3) || (!u2 && !u3);
    Rnn = ((!p1) && (!p2) && (!p3)) || p3;
    Rn = ((!p1) || (!p2)) && (!p3) || p3;
    Rpp = ((!u1) && (!u2) && (!u3)) || u3;
    Rp = (((!u1) || (!u2)) && (!u3)) || u3;
    Ruu = (u1 && u2 && u3) || !u3;
    Raa = (p1 && p2 && p3) || !p3;

    // Inint
    if (q3 == 3) Inint = verify(q1, q2, 1, rules);
    else if (q3 == 4) Inint = verify(q1, q2, 2, rules);

    int res = (Rmnt || !rules[0]) &&
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

void translate(int q, int *p, int *u) {
    if (q==0) {
        printf("error while inputing q");
    }
    if (q==1){
        *p = 1;
        *u = 1;
    }else{
        if (q==2){
            *p = 1;
            *u = 0;
        }else{
            if (q==3){
                *p = 0;
                *u = 1;
            }else{
                if (q==4){
                    *p = 0;
                    *u = 0;
                }
            }
        }
    }

}

