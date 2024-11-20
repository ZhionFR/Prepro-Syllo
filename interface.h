#ifndef INTERFACE_H
#define INTERFACE_H

enum {A, E, I, O};
enum {S, M, P, S1, P1, S2};
enum {KILL};
enum {NotAFig, Barbara, Barbari, Celarent, Celaront, Darii, Ferio, Cesare, Cesaro, Camestres, Camestrop, Festino,
        Baroco, Darapti, Felapton, Disamis, Datisi, Bocardo, Ferison, Bamalip, Calemes, Calemop, Dismatis,
        Fesapo, Fresison};

#define QUANTLIST "XAEIO"
#define STATUS (const char*[]){"Off","On"}

int isDead(int value);
int isDeadStr(char* name);

int getQuantif(int num, int len[4], int * ver, char ** fileA, char ** fileE, char ** fileI, char ** fileO);

void add_quantif(int len[], char ** fileA, char ** fileE, char ** fileI, char ** fileO);

int getFilter(int fA, int fE, int fI, int fO);
int printQuantList(char ** words, int index, int len);

int getType(char* name);
void getName(int type, char* name);

int getFig(int q1, int q2, int q3, char* propS, char* propM, char* propP);

void printPropo(char* sentence, char* S, char* P, char* placeholderS, char* placeholderP);
char *getSentence(char ** fileA, char ** fileE, char ** fileI, char ** fileO, int q, int v);
void printFigures(int figNum, char ** fileA, char ** fileE, char ** fileI, char ** fileO,
                  char *S, char *P, char *M, int q1, int q2, int q3, int v1, int v2, int v3);


void replacePlaceholder(char *phrase, char *name, char *result, char* placeholder);

int getRules(int rules[]);
void askRules(int rules[]);

void printError(int result[]);


#endif
