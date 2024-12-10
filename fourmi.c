#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Fourmi* creationFourmi(int id, const char* espece_fourmi, const char* role_fourmi) {
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (nouvelle_fourmi == NULL) {
        perror("Erreur d'allocation mémoire pour la fourmi");
        return NULL;
    }
    strcpy(nouvelle_fourmi->espece, espece_fourmi);
    nouvelle_fourmi->id_fourmi = id;
    strcpy(nouvelle_fourmi->role, role_fourmi);
    nouvelle_fourmi->age = 1;
    nouvelle_fourmi->sexe = true;
    nouvelle_fourmi->cgt = 0.0f;
    nouvelle_fourmi->faim = 0;
    nouvelle_fourmi->eau = 100;
    nouvelle_fourmi->sante = true;
    strcpy(nouvelle_fourmi->maladie, "Rien");
    nouvelle_fourmi->coord_x = 0;
    nouvelle_fourmi->coord_y = 0;
    return nouvelle_fourmi;
}

void afficher_fourmi(const Fourmi* fourmi) {
    if (fourmi == NULL) return;
    printf("\n--- Fourmi %d ---\n", fourmi->id_fourmi);
    printf("Espèce : %s\n", fourmi->espece);
    printf("Âge : %d\n", fourmi->age);
    printf("Faim : %d\n", fourmi->faim);
    printf("Eau : %d\n", fourmi->eau);
    printf("Santé : %s\n", fourmi->sante ? "En bonne santé" : "Morte");
    printf("Maladie : %s\n", fourmi->maladie);
    printf("Coordonnées : (%d, %d)\n", fourmi->coord_x, fourmi->coord_y);
}

void mise_a_jour_fourmi(Fourmi* fourmi) {
    if (fourmi == NULL) return;
    fourmi->age++;
    fourmi->faim += 5;
    fourmi->eau -= 2;
    if (fourmi->faim > 100 || fourmi->eau <= 0) {
        fourmi->sante = false;
        strcpy(fourmi->maladie, "Mort");
    } else if (fourmi->faim > 70) {
        strcpy(fourmi->maladie, "Sous-alimentation");
    }
}

void nourrir_fourmi(Fourmi* fourmi) {
    if (fourmi == NULL) return;
    fourmi->faim -= 30;
    if (fourmi->faim < 0) fourmi->faim = 0;
    strcpy(fourmi->maladie, "Rien");
}

void deplacer_fourmi(Fourmi* fourmi, int x, int y) {
    if (fourmi == NULL) return;
    fourmi->coord_x = x;
    fourmi->coord_y = y;
    printf("Fourmi %d déplacée à (%d, %d).\n", fourmi->id_fourmi, x, y);
}
