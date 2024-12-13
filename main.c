#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"
#include "animation.h"

#define JOUR_SIMULATION 6

// Liste des types de fourmilles
// 1 Fourmi coupeuse de feuilles : Atta
// 2 Fourmis des dunes : Cataglyphis
// 3 Fourmis des rochers : Messor
// 4 Fourmis amazoniennes : Eciton
// 5 Fourmis forestières : Formica
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis


ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine){

    for(int i = 1; i <= reine->capacite_ponte ; i++){

        Fourmi* fourmi1 = creationFourmi(i, "Ouvrière", reine->type);
        liste = ajout_fourmi(&liste, fourmi1);
    }
     update_day_Reine(reine);
     update_day_liste_fourmi(liste);
     afficher_fourmiliere(niveau, liste, reine);
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
    for(int i = 1; i <= JOUR_SIMULATION ; i++){
        liste = cycle_jour(i, liste, reine);
    }
    afficher_Reine(reine);
    getchar();
//     afficher_Liste_fourmi(liste);
    liberer_liste(liste);
    free(reine);
}

int main() {
    logo_1();
    int biome = logo_3();
    int type = logo_2();
    simulation(type);

    return 0;
}
