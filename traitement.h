#ifndef PREPRO_SYLLO_TRAITEMENT_H
#define PREPRO_SYLLO_TRAITEMENT_H

#define QUANTIFS "XAEIO"
#define BOOL (const char*[]){"non valide","  valide  "}

int verify(int q1, int q2, int q3, int rules[]);
void translate(int q, int *p, int *u);

void printTableau();
void printLign(int fig, int q1, int q2, int q3);

#endif
