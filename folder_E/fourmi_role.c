#include <stdlib.h>
#include "fourmi.h"

void devenir_POT_DE_MIEL(Fourmi* fourmi){
    fourmi->role = POT_DE_MIEL;
    fourmi->inventaire->nourriture = 200;
}

void devenir_AGRICOLE(Fourmi* fourmi){
    fourmi->role = AGRICOLE;
}
void devenir_ELEVEUR(Fourmi* fourmi){
    fourmi->role = ELEVEUR;
}

void ajuster_role(Fourmi* fourmi, ListFourmi* liste, Temps* saison) {
    if (fourmi->age < 10) {
        fourmi->role = NOURRICE;
    } else if (fourmi->age < 20) {
        fourmi->role = EXPLORATRICE;
    } else if (fourmi->age < 30) {
        if (fourmi->role == EXPLORATRICE && rand() % 2 == 0) {
            fourmi->role = COLLECTRICE_MIELLAT;
        }
    }
    else if (fourmi->age < 200) {
            fourmi->role = OUVRIERE;
    }
    else if (fourmi->age <= 1000) {
        if(fourmi->role_secondaire.estAustralienne && fourmi->role != POT_DE_MIEL){
             if(rand() % 2 == 0) {
                if( /*evaluerBesoinNourriture(liste, )*/ 1 == 1)
                    devenir_POT_DE_MIEL(fourmi);
             }
        }
        if(fourmi->role_secondaire.estEleveur && fourmi->role != ELEVEUR){
             if(rand() % 2 == 0) {
                devenir_ELEVEUR(fourmi);
             }
        }
        if(fourmi->role_secondaire.estCultivatrice && fourmi->role != AGRICOLE){
             if(rand() % 2 == 0) {
                devenir_AGRICOLE(fourmi);
             }
        }
        else if(fourmi->role != AGRICOLE && fourmi->role != ELEVEUR && fourmi->role != POT_DE_MIEL){
            fourmi->role = SOLDAT;
        }
    }
    else {

        int age_surplus = fourmi->age - 1000;
        int chance_de_mort = age_surplus / 10;
        if (rand() % 100 <= chance_de_mort) {
            // La fourmi meurt de vieillesse
            retirer_fourmi(&liste, fourmi);
            return;
        }
    }

    switch (saison->mois) {
        case 0:
            if (fourmi->role == OUVRIERE && rand() % 2 == 0) {
                fourmi->role = NOURRICE;
            }
            break;
        case 1:
            if (fourmi->role == OUVRIERE && rand() % 2 == 0) {
                fourmi->role = NOURRICE;
            }
            break;
        case 2:
            if (fourmi->role == OUVRIERE && rand() % 2 == 0) {
                fourmi->role = COLLECTRICE_MIELLAT;
            }
            break;
        case 3:
            if (fourmi->role == OUVRIERE && rand() % 2 == 0) {
                fourmi->role = EXPLORATRICE;
            }
            break;
        default:
            break;
    }
}
