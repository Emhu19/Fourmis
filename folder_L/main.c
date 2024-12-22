#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"
#include "animation.h"
#include "environnement.h"

#define JOUR_SIMULATION 6
#define BASE_COOR_X 25
#define BASE_COOR_Y 25

// Liste des types de fourmilles
/* 1 Fourmi coupeuse de feuilles : Atta
        1 Reine fondatrice de champignon
        2 Ouvrière transporteur de feuilles
        3 Soldat protecteur des colonnes
        4 Ouvrière nettoyeuse des champignons
        5 Ouvrière mineure pour le jardinage de champignons
*/
/* 2 Fourmis des dunes : Cataglyphis
    Exploratrice de chaleur extrême
    Messagère rapide
    Chercheuse d’ombre
    Ouvrière éclaireuse
    Reine migratrice
    Fourmi stérile pour fouille des sables
*/
// 3 Fourmis des rochers : Messor
// 4 Fourmis amazoniennes : Eciton
// 5 Fourmis forestières : Formica
    // Ouvrière constructrice de nids en bois ou aiguilles
        // Exploratrice forestière
        // Soldat défensif avec acide formique
        // Transporteur de petits insectes
        //Reine des sous-bois
        // Collectrice de miellat des pucerons
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis


ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine, Environnement* map){

    // if (saison == PRINTEMPS || saison == ETE) { à relier avec le système de saison
    int ponte = 0;
    if(1==1){
        if (reine->age < 730) {
            ponte = rand() % 100 + reine->capacite_ponte;
        } else {
            ponte = rand() % 50 + reine->capacite_ponte;
        }

        for(int i = 1; i <= ponte ; i++){
            Fourmi* fourmi1 = creationFourmi(i, reine->type);
            liste = ajout_fourmi(&liste, fourmi1);
        }
    }
     update_day_Reine(reine);
     update_day_liste_fourmi(liste, map);
     afficher_fourmiliere(3, liste, reine);
     return liste;
}

void simulation(int type){
    ListFourmi* liste = Initialisation_List();
    Reine* reine = creationReine(1, type);
//     getchar();
//     afficher_Reine(reine);
//     getchar();
//     if (reine != NULL) {
//          afficher_Reine(reine);
//     }
    srand(time(NULL)) ;

    Environnement E = genererEnvironnement() ;
    afficher_envi(E) ;
    Meteo M = init_meteo(E);
    Temps T = init_temps();
    Predateur* LP = NULL;

    while(1){
         liste = cycle_jour(5, liste, reine, &E);
        journee(&E, &M, &T, &LP);
//         sleep(5);
    }
    afficher_Reine(reine);
    getchar();
//     afficher_Liste_fourmi(liste);
    liberer_liste(liste);
    free(reine);
}

int main() {
    srand(time(NULL)) ;
    // logo_1();
    int biome = logo_3();
    Environnement E = genererEnvironnement(biome) ;
    afficher_envi(E) ;
    int type = logo_2();

    afficher_envi(E) ;
    sleep(2);

    Meteo M = init_meteo(E);
    Temps T = init_temps();
    Predateur* LP = NULL;

    while(true){
        printf("\033[H\033[J");
        //afficher_envi(E) ;
        journee(&E, &M, &T, &LP);
        //sleep(1);
    }
    return 0;
}
