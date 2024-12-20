#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "larve.h"

Stade* creationLarve(int id, int type_fourmi, bool sexe) {
    Stade* nouvelle_larve = (Stade*)malloc(sizeof(Stade));
    if (!nouvelle_larve) {
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
    if (!stade) return *liste;
    ListLarve* newNode = (ListLarve*)malloc(sizeof(ListLarve));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->stade = stade;
    newNode->next = *liste;
    *liste = newNode;
    return *liste;
}

ListLarve* retirer_larve(ListLarve** liste, Stade* stade) {
    if (!liste || !*liste) return NULL;
    ListLarve *current = *liste, *prev = NULL;
    while (current && current->stade != stade) {
        prev = current;
        current = current->next;
    }
    if (!current) return *liste;
    if (prev) prev->next = current->next;
    else *liste = current->next;
    free(current->stade);
    free(current);
    return *liste;
}

void liberer_liste_larves(ListLarve* liste) {
    while (liste) {
        ListLarve* suivant = liste->next;
        free(liste->stade);
        free(liste);
        liste = suivant;
    }
}

void update_day_larve(Stade* stade) {
    if (!stade) return;
    stade->age++;
    if (stade->age > 10) stade->cycle = LARVE;
    if (stade->age > 20) stade->cycle = NYMPHE;
}

int compter_Liste_Nymphe(ListLarve* liste) {
    int count = 0;
    while (liste) {
        if (liste->stade->cycle == NYMPHE) count++;
        liste = liste->next;
    }
    return count;
}

void update_day_liste_larve(ListLarve* liste) {
    while (liste) {
        update_day_larve(liste->stade);
        liste = liste->next;
    }
}
