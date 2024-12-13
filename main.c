#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"

#define JOUR_SIMULATION 6

ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine){

    for(int i = 1; i <= reine->capacite_ponte ; i++){

        Fourmi* fourmi1 = creationFourmi(i, "Formica", "Ouvrière");
        liste = ajout_fourmi(&liste, fourmi1);
    }
     update_day_Reine(reine);
     update_day_liste_fourmi(liste);
     afficher_fourmiliere(niveau, liste, reine);
     return liste;
}

int main() {

    ListFourmi* liste = Initialisation_List();
    Reine* reine = creationReine(1, "Formica");
//     getchar();
//     afficher_Reine(reine);
//     getchar();
//     if (reine != NULL) {
//          afficher_Reine(reine);
//     }
    for(int i = 1; i <= JOUR_SIMULATION ; i++){
        liste = cycle_jour(i, liste, reine);
    }
//     afficher_Reine(reine);
    getchar();
//     afficher_Liste_fourmi(liste);
    liberer_liste(liste);
    free(reine);

    return 0;
}
