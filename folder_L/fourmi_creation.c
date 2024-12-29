#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>
#include "fourmiliereL.h"

typedef struct {
    int spermatec;
    int capacite_ponte;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    int sante;
} ReineTemplate;

// const ReineTemplate reine_templates[] = {
    // {40000000, 20, 80, 90, 2, 2, 100}, // Atta
    // {1500000, 10, 100, 100, 2, 1, 100}, // Cataglyphis
    // {2000000, 8, 90, 80, 1, 1, 95}, // Messor
    // {50000000, 30, 120, 100, 2, 2, 100}, // Eciton
    // {3000000, 12, 95, 95, 1, 1, 98}, // Formica
    // {1500000, 10, 100, 80, 2, 1, 100}, // Pogonomyrmex
    // {6000000, 25, 110, 100, 2, 2, 100}, // Acromyrmex
    // {25000000, 15, 90, 120, 1, 2, 95}  // Polyrhachis
// };

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
    nouvelle_fourmi->maladie = initMaladie(0, "rien");
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
    printf("besoin_faim : %d\n", fourmi->besoin_faim);
    printf("besoin_eau : %d\n", fourmi->besoin_eau);
    printf("Eau : %d\n", fourmi->eau);
    printf("Santé : %s\n", fourmi->sante ? "En bonne santé" : "Morte");
    printf("Maladie : %s\n", fourmi->maladie.typeMaladie);
    printf("Coordonnées : (%d, %d)\n", fourmi->coord_x, fourmi->coord_y);
}
