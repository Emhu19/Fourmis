#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_COOR_X 25
#define BASE_COOR_Y 25

Fourmi* creationFourmi(int id, int type_fourmi) {
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (nouvelle_fourmi == NULL) {
        perror("Erreur d'allocation mémoire pour la fourmi");
        return NULL;
    }
    nouvelle_fourmi->id_fourmi = id;
    // strcpy(nouvelle_fourmi->role, role_fourmi);
    nouvelle_fourmi->age = 1;
    nouvelle_fourmi->salle = 2;
    nouvelle_fourmi->sexe = true;
    nouvelle_fourmi->cgt = 0.0f;
    nouvelle_fourmi->faim = 100;
    nouvelle_fourmi->eau = 100;
    nouvelle_fourmi->besoin_faim = 1;
    nouvelle_fourmi->besoin_eau = 1;
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

ListFourmi* Initialisation_List() {
    ListFourmi* newList = (ListFourmi*)malloc(sizeof(ListFourmi));
    if (newList == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    newList->fourmi = NULL;
    newList->prev = NULL;
    newList->next = NULL;
    return newList;
}

ListFourmi* ajout_fourmi(ListFourmi** liste, Fourmi* fourmi){
    ListFourmi* newList = (ListFourmi*)malloc(sizeof(ListFourmi));
    if (newList == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }

    newList->fourmi = fourmi;
    newList->prev = NULL;
    newList->next = *liste;

    if (*liste != NULL) {
        (*liste)->prev = newList;
    }
    *liste = newList;
    return newList;

}

void afficher_Liste_fourmi(ListFourmi* liste){
    ListFourmi* newList = liste;
    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return;
    }
    while(newList != NULL){
        afficher_fourmi(newList->fourmi);
        newList = newList->next;
    }
}

void compter_Liste_fourmi(ListFourmi* liste){
    ListFourmi* newList = liste;
    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return;
    }
    int i = 0;
    while(newList->next != NULL){
        i++;
        newList = newList->next;
    }
    printf("Il y a %d fourmis dans la fourmilières\n", i);
}

int compter_fourmi_salle(ListFourmi* liste, int salle){

    ListFourmi* newList = liste;

    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return 0;
    }
    int i = 0;
    while(newList->next != NULL){
        if(salle == newList->fourmi->salle){
            i++;
        }
        newList = newList->next;
    }
    return i;
}

ListFourmi* retirer_fourmi(ListFourmi** liste, Fourmi* fourmi) {

    if (liste == NULL || *liste == NULL) {
        fprintf(stderr, "Erreur : liste vide ou non initialisée.\n");
        return NULL;
    }

    ListFourmi* current = *liste;

    while (current != NULL && current->fourmi != fourmi) {
        current = current->next;
    }

    if (current == NULL) {
        fprintf(stderr, "Erreur : fourmi non trouvée.\n");
        return *liste;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *liste = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    return *liste;
}

void liberer_liste(ListFourmi* liste) {
    ListFourmi* courant = liste;
    while (courant != NULL) {
        ListFourmi* suivant = courant->next;
        free(courant->fourmi);
        free(courant);
        courant = suivant;
    }
}

Fourmi* trouver_fourmi(ListFourmi* liste, int id) {
    ListFourmi* courant = liste;
    while (courant != NULL) {
        if (courant->fourmi->id_fourmi == id) {
            return courant->fourmi;
        }
        courant = courant->next;
    }
    return NULL;
}


ListFourmi* fusionner_listes(ListFourmi* liste1, ListFourmi* liste2) { //utitile en cas de fusion de 2 fourmilières
    if (liste1 == NULL) return liste2;
    if (liste2 == NULL) return liste1;

    ListFourmi* courant = liste1;
    while (courant->next != NULL) {
        courant = courant->next;
    }

    courant->next = liste2;
    if (liste2 != NULL) {
        liste2->prev = courant;
    }

    return liste1;
}

void update_day_fourmi(Fourmi* fourmi, Environnement* map){
     if (fourmi == NULL) return;
    fourmi->faim -= fourmi->besoin_faim;
    fourmi->eau -= fourmi->besoin_eau;
    if(1 <= 1){ //si ressource disponible // la fonction fonctionne bien!!
        fourmi->faim += 1;
        fourmi->eau += 1;
//         ressource--;
    }
    if(fourmi->coord_x != BASE_COOR_X || fourmi->coord_y != BASE_COOR_Y){
        printf("Fourmi à l'extérieur\n");
        // pheromone_chunk(fourmi->coord_x, fourmi->coord_y);
    }

    if (fourmi->age < 10) {
        fourmi->role = NOURRICE;
    }
    else if (fourmi->age >= 10 && fourmi->age < 20) {
        fourmi->role = EXPLORATRICE;
    }
    else if (fourmi->age >= 20 && fourmi->age < 30) {
        fourmi->role = COLLECTRICE_MIELLAT;
    }

    else if (fourmi->age >= 30 && fourmi->age < 1001) {
        fourmi->role = SOLDAT;
    }
    else {
        //la fourmis doit mourir de veilleisse
        return;
    }
}

void ajuster_role_par_saison(Fourmi* fourmi) {
    // switch (saison) {
    //     case HIVER:
    //         if (fourmi->role == COLLECTRICE_MIELLAT) {
    //             fourmi->role = NOURRICE;
    //         }
    //         break;
    //     case PRINTEMPS:
    //         if (fourmi->role == NOURRICE) {
    //             fourmi->role = EXPLORATRICE;
    //         }
    //         break;
    //     case ETE:
    //         if (fourmi->role == NOURRICE) {
    //             fourmi->role = COLLECTRICE_MIELLAT;
    //         }
    //         break;
    //     case AUTOMNE:
    //         if (fourmi->role == COLLECTRICE_MIELLAT) {
    //             fourmi->role = SOLDAT;
    //         }
    //         break;
    // }
}

void update_day_liste_fourmi(ListFourmi* liste, Environnement* maps){
    ListFourmi* newList = liste;
    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return;
    }
    while(newList != NULL){
        update_day_fourmi(newList->fourmi, maps);
        newList = newList->next;
    }
}
