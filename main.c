#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "liste_fourmis.h"
#include "fourmi.h"
#include "reine.h"


int main() {

//     for(int i = 0; i < 7; i++)
//         afficher_fourmiliere(i);

    Reine* reine = creationReine(1, "Formica");
    if (reine != NULL) {
         afficher_Reine(reine);
    }

    free(reine);

    return 0;
}
