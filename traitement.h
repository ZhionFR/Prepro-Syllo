#ifndef PREPRO_SYLLO_TRAITEMENT_H
#define PREPRO_SYLLO_TRAITEMENT_H

#define QUANTIFS "XAEIO"
#define BOOL (const char*[]){"non valide","  valide  "}
#define BOOLD (const char*[]){"non","oui"}

int verify(int fig, int q1, int q2, int q3, int rules[]);
void translate(int q, int *p, int *u);

void printTable();
void printTableDetailled();

void printLign(int fig, int q1, int q2, int q3);
void printLignDetailled(int fig, int q1, int q2, int q3);

void exchange(char **wrd1, char **wrd2);

#endif
