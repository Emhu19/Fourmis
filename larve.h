#ifndef LARVE_H
#define LARVE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    OEUF,
    LARVE,
    NYMPHE
} Cycle;

typedef struct {
    Cycle cycle;
    int salle;
    int age;
    bool sante;
} Stade;

typedef struct ListLarve {
    Stade* stade;
    struct ListLarve* next;
} ListLarve;

Stade* creationLarve(int id, int type_fourmi, bool sexe);
ListLarve* Initialisation_List_Larve();
ListLarve* ajout_larve(ListLarve** liste, Stade* stade);
ListLarve* retirer_larve(ListLarve** liste, Stade* stade);
void liberer_liste_larve(ListLarve* liste);
void update_day_liste_larve(ListLarve* liste);
void update_day_larve(ListLarve* liste, Stade* stade);
int compter_Liste_Nymphe(ListLarve* liste);

#endif
