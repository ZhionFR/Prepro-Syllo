#ifndef PREPRO_SYLLO_TRAITEMENT_H
#define PREPRO_SYLLO_TRAITEMENT_H

#define QUANTIFS "XAEIO"
#define BOOL (const char*[]){"non valide","  valide  "}
#define BOOLD (const char*[]){"non", "oui"}


int verify(int fig, int q1, int q2, int q3, int rules[]);
void translate(int q, int *p, int *u);

void printTable();
void printDetailedTable();

void printLign(int fig, int q1, int q2, int q3);
void printDetailedLign(int fig, int q1, int q2, int q3);

void printWrongRules(int fig, int q1, int q2, int q3, int rules[]);
void printManual();

#endif
