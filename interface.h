#ifndef INTERFACE_H
#define INTERFACE_H

enum {A, E, I, O};
enum {S, M, P};
enum {KILL};
enum {NotAFig, Barbara, Barbari, Celarent, Celaront, Darii, Ferio, Cesare, Cesaro, Camestres, Camestrop, Festino,
        Baroco, Darapti, Felapton, Disamis, Datisi, Bocardo, Ferison, Bamalip, Calemes, Calemop, Dismatis,
        Fesapo, Fresison};

extern char * FIGLIST[25];

#define QUANTLIST "XAEIO"

int isDead(int value);
int isDeadStr(char* name);

int getQuantif(int num);
int printQuantList(int quantNum);

int getType();
void getName(int type, char* name);

int getFig(int q1, int q2, int q3, char* propS, char* propM, char* propP);

#endif
