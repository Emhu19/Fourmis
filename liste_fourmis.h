#ifndef LISTE_FOURMIS_H
#define LISTE_FOURMIS_H

#include "fourmi.h"


typedef struct ListFourmis {
    Fourmi *fourmi;
    struct ListFourmis *suivant;
    struct ListFourmis *precedent;
} ListFourmis;

#endif
