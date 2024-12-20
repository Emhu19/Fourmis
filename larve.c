#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "larve.h"

Stade* creationLarve(int id, int type_fourmi, bool sexe) {
    Stade* nouvelle_larve = (Stade*)malloc(sizeof(Stade));
    if (nouvelle_larve == NULL) {
        perror("Erreur d'allocation mémoire pour la larve");
        return NULL;
    }
    nouvelle_larve->cycle = OEUF;
    nouvelle_larve->salle = 2;
    nouvelle_larve->age = 1;
    nouvelle_larve->sante = true;

    return nouvelle_larve;
}

ListLarve* Initialisation_List_Larve() {
    return NULL;
}

ListLarve* ajout_larve(ListLarve** liste, Stade* stade) {
    if (stade == NULL) {
        fprintf(stderr, "Erreur : la larve à ajouter est NULL.\n");
        return *liste;
    }

    ListLarve* newNode = (ListLarve*)malloc(sizeof(ListLarve));
    if (newNode == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }

    newNode->stade = stade;
    newNode->next = *liste;
    *liste = newNode;

    return *liste;
}

ListLarve* retirer_larve(ListLarve** liste, Stade* stade) {
    if (liste == NULL || *liste == NULL) {
        fprintf(stderr, "Erreur : liste vide ou non initialisée.\n");
        return NULL;
    }

    ListLarve* current = *liste;
    ListLarve* prev = NULL;

    while (current != NULL && current->stade != stade) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        fprintf(stderr, "Erreur : larve non trouvée.\n");
        return *liste;
    }

    if (prev != NULL) {
        prev->next = current->next;
    } else {
        *liste = current->next;
    }

    free(current->stade);
    free(current);
    return *liste;
}

void liberer_liste_larve(ListLarve* liste){
    ListLarve* courant = liste;
    while (courant != NULL) {
        ListLarve* suivant = courant->next;
        free(courant->stade);
        free(courant);
        courant = suivant;
    }
}
