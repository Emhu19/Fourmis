#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"
#include "animation.h"
#include "environnement.h"
#include "larve.h"

#define JOUR_SIMULATION 6
#define BASE_COOR_X 12
#define BASE_COOR_Y 12

typedef struct {
    Environnement* map;
    Temps* temps;
    Meteo* meteo;
} Contexte;

typedef struct {
    ListFourmi* fourmis;
    ListLarve* larves;
    Reine* reine;
} Population;

ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine, Environnement* map, Temps* T, Meteo* M, ListLarve* liste_larve) {
    if (!liste) return NULL;

    int ponte = (reine->age < 730) ? rand() % 100 + reine->capacite_ponte : rand() % 50 + reine->capacite_ponte;

    if (T->saison == 2) {
        if (reine->royale) {
            for (int j = 0; j < 10; j++) {
                Fourmi* fourmi_male = creationFourmi(2000, reine->type, false);
                liste = ajout_fourmi(&liste, fourmi_male);
            }
        } else if (rand() % 100 == 19) {
            reine->royale = true;
        }
        if (M->precipitation && reine->royale) {
            reine->royale = false;
            Fourmi* fourmi_male_supp = trouver_fourmi(liste, 2000);
            if (fourmi_male_supp) retirer_fourmi(&liste, fourmi_male_supp);
        }
    }

    for (int i = 1; i <= ponte; i++) {
        Stade* stade = creationLarve(i, reine->type, true);
        if (stade) liste_larve = ajout_larve(&liste_larve, stade);
    }

    update_day_liste_larve(liste_larve);

    int nbNymphe = compter_Liste_Nymphe(liste_larve);
    for (int b = 0; b < nbNymphe; b++) {
        Fourmi* fourmi = creationFourmi(b, reine->type, true);
        if (fourmi) liste = ajout_fourmi(&liste, fourmi);
    }

    update_day_Reine(reine);
    update_day_liste_fourmi(liste, map);
    return liste;
}

void simulation() {
    ListFourmi* liste = Initialisation_List();
    ListLarve* liste_larve = Initialisation_List_Larve();
    Reine* reine = creationReine(1, 1);

    Environnement E = genererEnvironnement();
    Meteo M = init_meteo(E);
    Temps T = init_temps();
    Predateur* LP = NULL;

    while (1) {
        liste = cycle_jour(5, liste, reine, &E, &T, &M, liste_larve);
        journee(&E, &M, &T, &LP);
    }

    liberer_liste(liste);
    free(reine);
}

int main() {
    srand(time(NULL));
    simulation();
    return 0;
}
