#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"

#define JOUR_SIMULATION 6

ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine){

    for(int i = 1; i <= reine->spermatec; i++){

        Fourmi* fourmi1 = creationFourmi(i, "Formica", "Ouvrière");
        liste = ajout_fourmi(&liste, fourmi1);
    }
     afficher_fourmiliere(niveau, liste);
     return liste;
}

int main() {

    ListFourmi* liste = Initialisation_List();
    Reine* reine = creationReine(1, "Formica");
//     if (reine != NULL) {
//          afficher_Reine(reine);
//     }
    for(int i = 1; i <= JOUR_SIMULATION ; i++){
        liste = cycle_jour(i, liste, reine);
    }
    liberer_liste(liste);
    free(reine);

    return 0;
}
