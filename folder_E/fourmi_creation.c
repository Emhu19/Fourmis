#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    int sante;
    bool estCultivatrice; //Atta et Acromyrmex
    bool estNageuse; //Polyrhachis
    bool estEleveur; //Formica
    bool estAustralienne; //Camponotus
} FourmiTemplate;

const FourmiTemplate fourmi_templates[] = {
    {80, 90, 2, 2, 100, true, false, false, false}, // Atta
    {100, 100, 2, 1, 100, false, false, false, false}, // Cataglyphis
    {90, 80, 1, 1, 9, false, false, true, false}, // Messor
    {120, 100, 2, 2, 100, false, false, false, true}, // Camponotus
    {95, 95, 1, 1, 98, false, false, false, false}, // Formica
    {100, 80, 2, 1, 100, false, false, false, false}, // Pogonomyrmex
    {110, 100, 2, 2, 100, true, false, false, false}, // Acromyrmex
    {90, 120, 1, 2, 95, false, true, false, false},  // Polyrhachis
};

void initialiserFourmi(Fourmi* fourmi, const FourmiTemplate* template) {
    if (!fourmi || !template) return;

    fourmi->faim = template->faim;
    fourmi->eau = template->eau;
    fourmi->besoin_faim = template->besoin_faim;
    fourmi->besoin_eau = template->besoin_eau;
    fourmi->sante = template->sante;
    fourmi->cgt = 0.0f;
    fourmi->age = 1;
    fourmi->coord_x = 12;
    fourmi->coord_y = 12;

    fourmi->role_secondaire.estCultivatrice = template->estCultivatrice;
    fourmi->role_secondaire.estNageuse = template->estNageuse;
    fourmi->role_secondaire.estEleveur = template->estEleveur;
    fourmi->role_secondaire.estAustralienne = template->estAustralienne;
}

Fourmi* creationFourmi(int id, int espece_fourmi, bool sexe) {
    if (espece_fourmi < 1 || espece_fourmi > 8) {
        fprintf(stderr, "Erreur : espece de fourmi invalide.\n");
        return NULL;
    }
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (!nouvelle_fourmi) {
        perror("Erreur d'allocation mémoire pour la fourmi");
        return NULL;
    }
    nouvelle_fourmi->id_fourmi = id;
    nouvelle_fourmi->espece = espece_fourmi;

    nouvelle_fourmi->salle = 2; //faut modifier ?
    nouvelle_fourmi->sexe = sexe;
    initialiserFourmi(nouvelle_fourmi, &fourmi_templates[espece_fourmi - 1]);

    strcpy(nouvelle_fourmi->maladie, "Rien");
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
