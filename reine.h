#ifndef REINE_H
#define REINE_H

#include <stdbool.h>
#include "liste_fourmis.h"

#define MAX_CHAR 50

typedef struct {
    int type;
    bool royale;
    int id_reine;
    char role[MAX_CHAR];
    int salle;
    int spermatec;
    int capacite_ponte;
    int age;
    float cgt;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    int sante;
    char maladie[MAX_CHAR];
} Reine;

Reine* creationReine(int id, int type_reine);
void afficher_Reine(const Reine* reine);
void update_day_Reine(Reine* reine);
void update_year_Reine(Reine* reine);

#endif
