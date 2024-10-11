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

int getType(char* name);
void getName(int type, char* name);

int getFig(int q1, int q2, int q3, char* propS, char* propM, char* propP);

void printPropoBeta(int q, int v, char* S, char* P);
void printPropo(int q, char* sentence, char* S, char* P, char* placeholderS, char* placeholderP);

void printfigureBeta(int figNum, int q1, int q2, int q3, int v1, int v2, int v3,
                 char* propS, char* propM, char* propP);

void remplacerPlaceholder(char *phrase, char *name, char *resultat, char* placeholder);

#endif
