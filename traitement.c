#include "stdio.h"

#include "traitement.h"

int verify(int q1, int q2, int q3, int rules[]){

    int u1, u2, u3; // Universal booleans
    int p1, p2, p3; // Positif booleans

    // Transform qx in two booleans px and ux according to the value they have
    translate(q1, &p1, &u1);
    translate(q2, &p2, &u2);
    translate(q3, &p3, &u3);

    int Rmnt, Rlh, Rnn, Rn, Rpp, Rp, Ruu, Raa, Inint; // Rules result

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

// Transform q in two booleans p and u according to the value they have 
void translate(int q, int *p, int *u) {
    // Check if q is valid beforehand  
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

