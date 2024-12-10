#ifndef LISTE_FOURMIS_H
#define LISTE_FOURMIS_H

#include "fourmi.h"

typedef struct ListFourmis {
    Fourmi *fourmi;
    struct ListFourmis *suivant;
    struct ListFourmis *precedent;
} ListFourmis;

ListFourmis* ajouter_fourmi(ListFourmis* liste, Fourmi* fourmi);
void cycle_de_vie(ListFourmis* liste);
ListFourmis* supprimer_fourmi(ListFourmis* liste, Fourmi* fourmi);

#endif
