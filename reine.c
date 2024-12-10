#include "reine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fourmi.h"

Reine* creationReine(int id, const char* espece) {
    Reine* nouvelle_reine = (Reine*)malloc(sizeof(Reine));
    if (nouvelle_reine == NULL) {
        perror("Erreur d'allocation mémoire pour la reine");
        return NULL;
    }
    strcpy(nouvelle_reine->espece, espece);
    nouvelle_reine->id_reine = id;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 5;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 0;
    nouvelle_reine->eau = 100;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");
    return nouvelle_reine;
}

void afficher_Reine(const Reine* reine) {
    if (reine == NULL) return;
    printf("\n--- Reine %d ---\n", reine->id_reine);
    printf("Espèce : %s\n", reine->espece);
    printf("Âge : %d\n", reine->age);
    printf("Faim : %d\n", reine->faim);
    printf("Eau : %d\n", reine->eau);
    printf("Santé : %d\n", reine->sante);
    printf("Maladie : %s\n", reine->maladie);
}
