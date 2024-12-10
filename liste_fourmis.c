#include "liste_fourmis.h"
#include <stdio.h>
#include <stdlib.h>

ListFourmis* ajouter_fourmi(ListFourmis* liste, Fourmi* fourmi) {
    ListFourmis* nouvel_element = (ListFourmis*)malloc(sizeof(ListFourmis));
    if (nouvel_element == NULL) {
        perror("Erreur d'allocation pour la liste des fourmis");
        return liste;
    }
    nouvel_element->fourmi = fourmi;
    nouvel_element->suivant = liste;
    nouvel_element->precedent = NULL;
    if (liste != NULL) {
        liste->precedent = nouvel_element;
    }
    return nouvel_element;
}

void cycle_de_vie(ListFourmis* liste) {
    ListFourmis* courant = liste;
    while (courant != NULL) {
        mise_a_jour_fourmi(courant->fourmi);
        afficher_fourmi(courant->fourmi);
        courant = courant->suivant;
    }
}

ListFourmis* supprimer_fourmi(ListFourmis* liste, Fourmi* fourmi) {
    ListFourmis* courant = liste;
    while (courant != NULL) {
        if (courant->fourmi == fourmi) {
            if (courant->precedent) {
                courant->precedent->suivant = courant->suivant;
            }
            if (courant->suivant) {
                courant->suivant->precedent = courant->precedent;
            }
            if (courant == liste) {
                liste = courant->suivant;
            }
            free(courant);
            break;
        }
        courant = courant->suivant;
    }
    return liste;
}
