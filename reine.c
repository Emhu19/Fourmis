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
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 50000000;
    nouvelle_reine->capacite_ponte = 15;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 100;
    nouvelle_reine->eau = 100;
    nouvelle_reine->besoin_faim = 1;
    nouvelle_reine->besoin_eau = 1;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");
    return nouvelle_reine;

}

void afficher_Reine(const Reine* reine) {
    if (reine == NULL) return;
    printf("\n--- Reine %d ---\n", reine->id_reine);
    printf("Espèce : %s\n", reine->espece);
    printf("Ponte par jour : %d\n", reine->capacite_ponte);
    printf("Spermatec : %d\n", reine->spermatec);
    printf("Âge : %d\n", reine->age);
    printf("Faim : %d\n", reine->faim);
    printf("Eau : %d\n", reine->eau);
    printf("Santé : %d\n", reine->sante);
    printf("Maladie : %s\n", reine->maladie);
}

void update_day_Reine(Reine* reine){

    reine->faim -= reine->besoin_faim;
    reine->eau -= reine->besoin_eau;
    reine->spermatec -=reine->capacite_ponte;
    if(1 <= 1){ //si ressource disponible
        reine->faim += 1;
        reine->eau += 1;
//         ressource--;
    }
//     return reine;
}

void update_year_Reine(Reine* reine){

    reine->age++;
}
