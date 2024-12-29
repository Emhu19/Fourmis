#include <stdlib.h>
#include "fourmi.h"

void ajuster_role(Fourmi* fourmi, ListFourmi* liste, Temps* saison) {
    if (fourmi->age < 10) {
        fourmi->role = NOURRICE;
    } else if (fourmi->age < 20) {
        fourmi->role = EXPLORATRICE;
    } else if (fourmi->age < 30) {
        if (fourmi->role == EXPLORATRICE && rand() % 2 == 0) {
            fourmi->role = COLLECTRICE_MIELLAT;
        }
    } else if (fourmi->age <= 1000) {
        if(fourmi->role_secondaire.estAustralienne){
            // if(evaluerBesoinNourriture(liste, ))
            fourmi->role = POT_DE_MIEL;
        }
        else{
            fourmi->role = SOLDAT;
        }
    } else {
        // La fourmi meurt de vieillesse
        retirer_fourmi(&liste, fourmi);
        return;
    }

    switch (saison->mois) {
        case 0:
            if (fourmi->role == SOLDAT && rand() % 2 == 0) {
                fourmi->role = NOURRICE;
            }
            break;
        case 1:
            if (fourmi->role == SOLDAT && rand() % 2 == 0) {
                fourmi->role = NOURRICE;
            }
            break;
        case 2:
            if (fourmi->role == SOLDAT && rand() % 2 == 0) {
                fourmi->role = COLLECTRICE_MIELLAT;
            }
            break;
        case 3:
            if (fourmi->role == SOLDAT && rand() % 2 == 0) {
                fourmi->role = EXPLORATRICE;
            }
            break;
        default:
            break;
    }
}
