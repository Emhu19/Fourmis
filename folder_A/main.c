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

// Liste des types de fourmilles
// 1 Fourmi coupeuse de feuilles : Atta
// 2 Fourmis des dunes : Cataglyphis
// 3 Fourmis des rochers : Messor
// 4 Fourmis amazoniennes : Eciton
// 5 Fourmis forestières : Formica
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis





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


// Fourmiliere init_fourmiliere(Environnement* E, int espece){
//     Fourmiliere F;
//     F.fourmi = NULL;
//     F.reine = NULL;
//     F.piece = NULL;
//     F.espece = espece;
//     F.x = 12;
//     F.y = 12;
//     //F.suivant = NULL;

//     E->chunks[F.coord_x][F.coord_y].type = 0;
//     return F;
// }


void simulation() {
    srand(time(NULL));

    Population population = { Initialisation_List(), Initialisation_List_Larve(), creationReine(1, 1) };
    if (!population.reine) {
        fprintf(stderr, "Erreur : Impossible de créer la reine.\n");
        exit(EXIT_FAILURE);
    }


    logo_1();
    printf("\033c");
    Environnement environnement = genererEnvironnement(logo_3());
    printf("\033c");

    int type = logo_2();
    //Fourmiliere F = init_fourmiliere(&environnement, type);

    printf("\033c");
    printf("chargement ...\n Cette opération peut prendre quelques secondes\n");
    calculer_dist(&environnement, 12, 12, 0);
    printf("\n");
    printf("\033c");


    afficher_envi(environnement) ;
    getchar();
    printf("\033c");

    
    Meteo meteo = init_meteo(environnement);
    Temps temps = init_temps();
    Predateur* predateurs = NULL;

    Contexte contexte = { &environnement, &temps, &meteo };

    

    while (1) {
        printf("\033c");
        population.fourmis = cycle_jour(5, &population, &contexte);
        journee(&environnement, &meteo, &temps, &predateurs);
        // getchar();
    }

    liberer_liste(population.fourmis);
    liberer_liste_larves(population.larves);
    free(population.reine);

}



// void simulation(){

//     srand(time(NULL)) ;
//     logo_1();
//     printf("\033c");
//     int biome = logo_3();
//     printf("\033c");
//     Environnement E = genererEnvironnement(biome) ;
//     //afficher_envi_v(&E) ;
//     int type = logo_2();

//     ListLarve* liste_larve = Initialisation_List_Larve();
//     ListFourmi* liste = Initialisation_List();
//     Reine* reine = creationReine(1, type);


//     Fourmiliere F = init_fourmiliere(&E, type);

//     printf("\033c");
//     printf("chargement ...\n Cette opération peut prendre quelques secondes\n");
//     calculer_dist(&E, 12, 12, 0);
//     printf("\n");
//     printf("\033c");


//     afficher_envi(E) ;
//     // afficher_envi_v(&E) ;
//     getchar();
//     printf("\033c");
    
//     Meteo M = init_meteo(E);
//     Temps T = init_temps();
//     Predateur* LP = NULL;

//     while(1){
//         printf("\033c");
//         liste = cycle_jour(5, liste, reine, &E, &T, &M, liste_larve);
//         journee(&E, &M, &T, &LP);
//         //afficher_envi_v(&E);
//         getchar();
//     //         sleep(5);
//     }
//     afficher_Reine(reine);
//     getchar();
// //     afficher_Liste_fourmi(liste);
//     liberer_liste(liste);
//     free(reine);
// }


int main() {
    simulation();
    // srand(time(NULL)) ;
    // logo_1();
    // printf("\033c");
    // int biome = logo_3();
    // printf("\033c");
    // Environnement E = genererEnvironnement(biome) ;
    // //afficher_envi_v(&E) ;
    // int type = logo_2();

    // Fourmiliere F = init_fourmiliere(&E, type);
    // printf("\033c");
    // printf("chargement ...\n Cette opération peut prendre quelques secondes\n");
    // calculer_dist(&E, 12, 12, 0);
    // printf("\n");
    // printf("\033c");

    // afficher_envi(E) ;
    // // afficher_envi_v(&E) ;
    // getchar();
    // printf("\033c");
    
    // Meteo M = init_meteo(E);
    // Temps T = init_temps();
    // Predateur* LP = NULL;
    
    // while(true){
    //     //printf("\033[H\033[J");
    //     printf("\033c");
    //     // afficher_envi(E) ;
    //     journee(&E, &M, &sT, &LP);
    //     //sleep(1);
    // }

//     logo_1();
    
    //Environnement E = genererEnvironnement();

    //simulation(type);


    return 0;
}
