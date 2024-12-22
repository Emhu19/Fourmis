#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmiliereL.h"
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

    int ponte = calculer_ponte(reine);

    if (contexte->temps->saison == 2 && reine->royale) {
        gerer_creation_fourmis_males(&population->fourmis, reine);
        reine->royale = false;
    }

    if (contexte->meteo->precipitation) {
        supprimer_fourmis_males(population->fourmis);

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

    ArbrePiece *T;
    Piece A;
    ListRessource *ressources;
    ListPiece *pieces;
    Ressource *metal;
    Ressource *bois;
    Piece stockBois;
    Piece stockMetal;
    metal = initRessource(1, 10, "metal");
    ressources = initListR(metal);
    bois = initRessource(2, 10, "bois");
    ressources = ajouteRessource(ressources, bois);
    stockBois = initPiece(2, bois, 5,  "stockBois", bois);
    pieces = initListP(stockBois);
    stockMetal = initPiece(3, metal, 5,  "stockMetal", metal);
    pieces = ajoutePieceList(pieces, stockMetal);
    A = initPiece(1, bois, 0, "Principale", bois);
    T = init(A);

    srand(time(NULL));

    while (1) {
        population.fourmis = cycle_jour(5, &population, &contexte);
        journee(&environnement, &meteo, &temps, &predateurs);
        cycleFourmiliere(ressources, T, pieces);
    }

    liberer_liste(population.fourmis);
    liberer_liste_larves(population.larves);
    free(population.reine);

}


int main() {
    simulation();
    return 0;
}
