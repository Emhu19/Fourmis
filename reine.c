#include "reine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fourmi.h"

typedef struct {
    int spermatec;
    int capacite_ponte;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    int sante;
} ReineTemplate;

const ReineTemplate reine_templates[] = {
    {40000000, 20, 80, 90, 2, 2, 100}, // Atta
    {1500000, 10, 100, 100, 2, 1, 100}, // Cataglyphis
    {2000000, 8, 90, 80, 1, 1, 95}, // Messor
    {50000000, 30, 120, 100, 2, 2, 100}, // Eciton
    {3000000, 12, 95, 95, 1, 1, 98}, // Formica
    {1500000, 10, 100, 80, 2, 1, 100}, // Pogonomyrmex
    {6000000, 25, 110, 100, 2, 2, 100}, // Acromyrmex
    {25000000, 15, 90, 120, 1, 2, 95}  // Polyrhachis
};

void initialiserReine(Reine* reine, const ReineTemplate* template) {
    if (!reine || !template) return;
    reine->salle = 1; //salle de la Reine
    reine->royale = false;
    strcpy(reine->role, "Reine");
    reine->spermatec = template->spermatec;
    reine->capacite_ponte = template->capacite_ponte;
    reine->age = 1;
    reine->cgt = 0.0f;
    reine->faim = template->faim;
    reine->eau = template->eau;
    reine->besoin_faim = template->besoin_faim;
    reine->besoin_eau = template->besoin_eau;
    reine->sante = template->sante;
    strcpy(reine->maladie, "Rien");
}

Reine* creationReine(int id, int type_reine) {
    if (type_reine < 1 || type_reine > 8) {
        fprintf(stderr, "Erreur : espece de reine invalide.\n");
        return NULL;
    }

    Reine* nouvelle_reine = (Reine*)malloc(sizeof(Reine));
    if (!nouvelle_reine) {
        perror("Erreur d'allocation mémoire pour la reine");
        return NULL;
    }

    nouvelle_reine->id_reine = id;
    nouvelle_reine->espece = type_reine;
    initialiserReine(nouvelle_reine, &reine_templates[type_reine - 1]);

    return nouvelle_reine;
}

void afficher_Reine(const Reine* reine) {
    if (!reine) return;
    printf("\n--- Reine %d ---\n", reine->id_reine);
    printf("Espèce : %d\n", reine->espece);
    printf("Ponte par jour : %d\n", reine->capacite_ponte);
    printf("Spermatec : %d\n", reine->spermatec);
    printf("Âge : %d\n", reine->age);
    printf("Faim : %d\n", reine->faim);
    printf("Eau : %d\n", reine->eau);
    printf("Santé : %d\n", reine->sante);
    printf("Maladie : %s\n", reine->maladie);
}

void update_day_Reine(Reine* reine) {
    if (!reine) return;
    reine->faim -= reine->besoin_faim;
    reine->eau -= reine->besoin_eau;
    reine->spermatec -= reine->capacite_ponte;
    if (reine->faim < 0) reine->faim = 0;
    if (reine->eau < 0) reine->eau = 0;
}

void update_year_Reine(Reine* reine) {
    if (!reine) return;
    reine->age++;
}

int calculer_ponte(Reine reine) {
    return (reine.age < 730) ? rand() % 20 + reine.capacite_ponte : rand() % 10 + reine.capacite_ponte;
}
