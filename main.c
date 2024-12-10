#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "liste_fourmis.h"
#include "fourmi.h"
#include "reine.h"

#define JOUR_SIMULATION 10

void cycle_jour(int niveau){

    afficher_fourmiliere(niveau);
}

int main() {

//      for(int i = 0; i < 7; i++)
//         afficher_fourmiliere(i);

    Reine* reine = creationReine(1, "Formica");
    if (reine != NULL) {
         afficher_Reine(reine);
    }
    for(int i = 0; i < 7; i++)
        cycle_jour(i);

    free(reine);

    return 0;
}
