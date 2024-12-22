#include "reine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fourmi.h"

void creationReine_Atta(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 40000000;
    nouvelle_reine->capacite_ponte = 20;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 80;
    nouvelle_reine->eau = 90;
    nouvelle_reine->besoin_faim = 2;
    nouvelle_reine->besoin_eau = 2;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");

}
void creationReine_Cataglyphis(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 1500000;
    nouvelle_reine->capacite_ponte = 10;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 100;
    nouvelle_reine->eau = 100;
    nouvelle_reine->besoin_faim = 2;
    nouvelle_reine->besoin_eau = 1;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");

}
void creationReine_Messor(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 2000000;
    nouvelle_reine->capacite_ponte = 8;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 90;
    nouvelle_reine->eau = 80;
    nouvelle_reine->besoin_faim = 1;
    nouvelle_reine->besoin_eau = 1;
    nouvelle_reine->sante = 95;
    strcpy(nouvelle_reine->maladie, "Rien");

}
void creationReine_Eciton(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 50000000;
    nouvelle_reine->capacite_ponte = 30;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 120;
    nouvelle_reine->eau = 100;
    nouvelle_reine->besoin_faim = 2;
    nouvelle_reine->besoin_eau = 2;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");

}
void creationReine_Formica(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 3000000;
    nouvelle_reine->capacite_ponte = 12;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 95;
    nouvelle_reine->eau = 95;
    nouvelle_reine->besoin_faim = 1;
    nouvelle_reine->besoin_eau = 1;
    nouvelle_reine->sante = 98;
    strcpy(nouvelle_reine->maladie, "Rien");

}
void creationReine_Pogonomyrmex(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 1500000;
    nouvelle_reine->capacite_ponte = 10;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 100;
    nouvelle_reine->eau = 80;
    nouvelle_reine->besoin_faim = 2;
    nouvelle_reine->besoin_eau = 1;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");
}
void creationReine_Acromyrmex(Reine* nouvelle_reine){
    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 6000000;
    nouvelle_reine->capacite_ponte = 25;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 110;
    nouvelle_reine->eau = 100;
    nouvelle_reine->besoin_faim = 2;
    nouvelle_reine->besoin_eau = 2;
    nouvelle_reine->sante = 100;
    strcpy(nouvelle_reine->maladie, "Rien");
}
void creationReine_Polyrhachis(Reine* nouvelle_reine){

    nouvelle_reine->salle = 1;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 25000000;
    nouvelle_reine->capacite_ponte = 15;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.0f;
    nouvelle_reine->faim = 90;
    nouvelle_reine->eau = 120;
    nouvelle_reine->besoin_faim = 1;
    nouvelle_reine->besoin_eau = 2;
    nouvelle_reine->sante = 95;
    strcpy(nouvelle_reine->maladie, "Rien");
}

Reine* creationReine(int id, int type_reine) {

    Reine* nouvelle_reine = (Reine*)malloc(sizeof(Reine));
    if (nouvelle_reine == NULL) {
        perror("Erreur d'allocation mémoire pour la reine");
        return NULL;
    }
    nouvelle_reine->type = type_reine;
    nouvelle_reine->id_reine = id;
    if(type_reine == 1){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 2){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 3){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 4){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 5){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 6){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 7){
        creationReine_Atta(nouvelle_reine);
    }
    else if(type_reine == 8){
        creationReine_Atta(nouvelle_reine);
    }
    return nouvelle_reine;
}

void afficher_Reine(const Reine* reine) {
    if (reine == NULL) return;
    printf("\n--- Reine %d ---\n", reine->id_reine);
    printf("Espèce : %d\n", reine->type);
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
