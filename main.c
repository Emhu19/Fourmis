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

ListFourmi* cycle_jour(int niveau, Population* population, Contexte* contexte) {
    if (!population->fourmis) return NULL;

    Reine* reine = population->reine;

    int ponte = (reine->age < 730) ? rand() % 100 + reine->capacite_ponte : rand() % 50 + reine->capacite_ponte;

    if (contexte->temps->saison == 2) {
        if (reine->royale) {
            for (int j = 0; j < 10; j++) {
                Fourmi* fourmi_male = creationFourmi(2000, reine->type, false);
                population->fourmis = ajout_fourmi(&population->fourmis, fourmi_male);
            }
        } else if (rand() % 100 == 19) {
            reine->royale = true;
        }
        if (contexte->meteo->precipitation && reine->royale) {
            reine->royale = false;
            Fourmi* fourmi_male_supp = trouver_fourmi(population->fourmis, 2000);
            if (fourmi_male_supp) retirer_fourmi(&population->fourmis, fourmi_male_supp);
        }
    }

    for (int i = 1; i <= ponte; i++) {
        Stade* stade = creationLarve(i, reine->type, true);
        if (stade) population->larves = ajout_larve(&population->larves, stade);
    }

    update_day_liste_larve(population->larves);

    int nbNymphe = compter_Liste_Nymphe(population->larves);
    for (int b = 0; b < nbNymphe; b++) {
        Fourmi* fourmi = creationFourmi(b, reine->type, true);
        if (fourmi) population->fourmis = ajout_fourmi(&population->fourmis, fourmi);
    }

    update_day_Reine(reine);
    update_day_liste_fourmi(population->fourmis, contexte->map);

    return population->fourmis;
}


void simulation() {

    Population population = { Initialisation_List(), Initialisation_List_Larve(), creationReine(1, 1) };
    if (!population.reine) {
        fprintf(stderr, "Erreur : Impossible de créer la reine.\n");
        exit(EXIT_FAILURE);
    }

    Environnement environnement = genererEnvironnement();
    Meteo meteo = init_meteo(environnement);
    Temps temps = init_temps();
    Predateur* predateurs = NULL;

    Contexte contexte = { &environnement, &temps, &meteo };

    srand(time(NULL));

    while (1) {
        population.fourmis = cycle_jour(5, &population, &contexte);
        journee(&environnement, &meteo, &temps, &predateurs);
    }

    liberer_liste(population.fourmis);
    liberer_liste_larves(population.larves);
    free(population.reine);

}


int main() {
    simulation();
    return 0;
}
