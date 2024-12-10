#ifndef REINE_H
#define REINE_H

#include <stdbool.h>

#define MAX_CHAR 50

typedef struct {
    char espece[MAX_CHAR];
    int id_reine;
    char role[MAX_CHAR];
    int spermatec;
    int age;
    float cgt;
    int faim;
    int eau;
    int sante;
    char maladie[MAX_CHAR];
} Reine;

Reine* creationReine(int id, const char* espece);
void afficher_Reine(const Reine* reine);

#endif
