#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>

Fourmi* creationFourmi(int id, int espece_fourmi, bool sexe) {
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (!nouvelle_fourmi) {
        perror("Erreur d'allocation mémoire pour la fourmi");
        return NULL;
    }
    nouvelle_fourmi->id_fourmi = id;
    nouvelle_fourmi->espece = espece_fourmi;
    nouvelle_fourmi->age = 1;
    nouvelle_fourmi->salle = 2;
    nouvelle_fourmi->sexe = sexe;
    nouvelle_fourmi->cgt = 0.0f;
    nouvelle_fourmi->faim = 100;
    nouvelle_fourmi->eau = 100;
    nouvelle_fourmi->besoin_faim = 1;
    nouvelle_fourmi->besoin_eau = 1;
    nouvelle_fourmi->sante = true;
    strcpy(nouvelle_fourmi->maladie, "Rien");
    nouvelle_fourmi->coord_x = BASE_COOR_X;
    nouvelle_fourmi->coord_y = BASE_COOR_Y;
    return nouvelle_fourmi;
}

void afficher_fourmi(const Fourmi* fourmi) {
    if (!fourmi) return;
    printf("\n--- Fourmi %d ---\n", fourmi->id_fourmi);
    printf("Espèce : %d\n", fourmi->espece);
    printf("Âge : %d\n", fourmi->age);
    printf("Faim : %d\n", fourmi->faim);
    printf("Eau : %d\n", fourmi->eau);
    printf("Santé : %s\n", fourmi->sante ? "En bonne santé" : "Morte");
    printf("Maladie : %s\n", fourmi->maladie);
    printf("Coordonnées : (%d, %d)\n", fourmi->coord_x, fourmi->coord_y);
}
