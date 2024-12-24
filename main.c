#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmiliereL.h"
#include "fourmi.h"
#include "reine.h"
#include "animation.h"
#include "environnement.h"
#include "larve.h"

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

void supp_predateurs_mort(Predateur** LP, Environnement* E){
    if (*LP == NULL){
        return;
    }
    Predateur* copie = *LP;
    Predateur* prev = NULL;
    while(copie != NULL){
        if(copie->sante <= 0){
            if (prev != NULL) {
                prev->suivant = copie->suivant; // Sauter l'élément à supprimer
            }
            switch(copie->type){
                case 0:
                    E->chunks[copie->x][copie->y].nourriture = 100;
                    break;
                case 1:
                    E->chunks[copie->x][copie->y].nourriture = 50;
                    break;
                case 2:
                    E->chunks[copie->x][copie->y].nourriture = 50;
                    break;
                case 3:
                    E->chunks[copie->x][copie->y].nourriture = 10;
                    break;
                case 4:
                    E->chunks[copie->x][copie->y].nourriture = 25;
                    break;
                case 5:
                    E->chunks[copie->x][copie->y].nourriture = 50;
                    break;
                case 6:
                    E->chunks[copie->x][copie->y].nourriture = 50;
            }
            free(copie); // Libérer la mémoire
        }
        prev = copie;       // Mettre à jour le pointeur précédent
        copie = copie->suivant; // Avancer au suivant
    }
}


void combat(Predateur** LP, Environnement* E, ListFourmi* LF){
    if (LP == NULL || LF == NULL){
        return;
    }
    Predateur* copieLP = *LP;
    ListFourmi* copieLF = LF;
    while(copieLP != NULL){
        while(copieLF != NULL){
            if (copieLF->fourmi == NULL){
                copieLF = copieLF->next;
                continue;
            }
            if( (copieLF->fourmi != NULL) && copieLP->x == copieLF->fourmi->coord_x && copieLP->y == copieLF->fourmi->coord_y && (copieLP->x!= 12 || copieLP->y != 12)){
                while(copieLF->fourmi->sante > 0 && copieLP->sante > 0){
                    copieLP->sante -= 10;
                    copieLF->fourmi->sante -= copieLP->force;
                }
                if(copieLP->sante <= 0){
                    break;
                }
                else{
                    copieLP->victimes++;
                }
            }
            copieLF = copieLF->next;
        }
        copieLP = copieLP->suivant;
    }
    supp_predateurs_mort(LP, E);
    // supp_fourmis_mort(LF, E);
}

ListFourmi* cycle_jour(Population* population, Contexte* contexte) {
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
        Stade* stade = creationLarve(i, reine->espece);
        if (stade) population->larves = ajout_larve(&population->larves, stade);
    }

    update_day_liste_larve(population->larves);

    int nbNymphe = compter_Liste_Nymphe(population->larves);
    for (int b = 0; b < nbNymphe; b++) {
        Fourmi* fourmi = creationFourmi(b, reine->espece, true);
        if (fourmi) population->fourmis = ajout_fourmi(&population->fourmis, fourmi);
    }

    update_day_Reine(reine);
    update_day_liste_fourmi(population->fourmis, contexte->map);

    return population->fourmis;
}


void journee(Environnement* E, Meteo* M, Temps* T, Predateur** LP, ListFourmi* LF) {


    incr_temp(T);
    ajout_eau_miam(E, *M);
    maj_meteo(M, *T);
    if (E->biome == 1969){
        M->temperature = 0;
    }
    bouger_predateurs(LP, *E);
    generer_predateur(*E, LP);
    combat(LP, E, LF);



    // Afficher les informations temporelles

    printf("\n=========================================================================== Informations Temps ===========================================================================\n");
    const char* saisons[] = {"Hiver", "Printemps", "Été", "Automne"};
    printf("Saison : %s\n", saisons[T->saison]);
    printf("Mois : %d\n", T->mois + 1); // Ajouter 1 pour afficher mois de 1 à 12
    printf("Jour : %d\n", T->jour);
    printf("année : %d\n", T->annee);
    printf("========================================================================\n");
    // Afficher les informations météorologiques
    printf("\n=========================================================================== Informations Météo ===========================================================================\n");
    printf("Température actuelle : %.2f °C\n", M->temperature);
    printf("Précipitations : %s\n", M->precipitation ? "Oui" : "Non");
    printf("Orages : %s\n", M->orage ? "Oui" : "Non");
    printf("========================================================================\n");
    printf("\n=== Informations Prédateurs ===\n");
    if (*LP == NULL) {
        printf("il n'y a aucun prédateur dans les environs\n");
    } else {
        Predateur* copie = *LP;
        while (copie != NULL) {
            printf("Il y a un %s en (%d, %d), qui a déjà fait %d victimes !\n", copie->nom_predateur,copie->x, copie->y, copie->victimes);
            copie = copie->suivant;
        }
    }

    printf("il y a un total de %d prédateurs", compter_predateurs(*LP));

    // Ligne de séparation
    printf("\n========================================================================\n");


    trouver_id_predateurs_loin(LP);
    //print_id(*LP);
    // getchar();
}

void simulation() {


    logo_1();
    printf("\033c");
    Environnement environnement = genererEnvironnement(logo_3());
    printf("\033c");
    int espece = logo_2();
    printf("\033c");
    printf("génération de l'environnement en cours\nCette opération peut prendre un certain temps\n");
    calculer_dist(&environnement);
    printf("\033c");
    printf("voici l'environnement généré aléatoirement :\n");
    afficher_envi(environnement);
    getchar();
    printf("\033c");
    Meteo meteo = init_meteo(environnement);
    
    Temps temps = init_temps();
    Predateur* predateurs = NULL;

    

    Contexte contexte = {&environnement, &temps, &meteo };


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

    Population population = { Initialisation_List(), Initialisation_List_Larve(), creationReine(1, espece) };
    if (!population.reine) {
        fprintf(stderr, "Erreur : Impossible de créer la reine.\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\033c");
        population.fourmis = cycle_jour(&population, &contexte);
        journee(contexte.map, contexte.meteo, contexte.temps, &predateurs, population.fourmis);
        // afficher_envi(environnement);
        cycleFourmiliere(ressources, T, pieces);
        getchar();
        
    }

    liberer_liste(population.fourmis);
    liberer_liste_larves(population.larves);
    free(population.reine);

}


int main() {
    simulation();
    return 0;
}
