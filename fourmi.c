#include "fourmi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BASE_COOR_X 12
#define BASE_COOR_Y 12

Fourmi* creationFourmi(int id, int type_fourmi, bool sexe) {
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (!nouvelle_fourmi) {
        perror("Erreur d'allocation mémoire pour la fourmi");
        return NULL;
    }
    nouvelle_fourmi->id_fourmi = id;
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
    if (!newList) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    newList->fourmi = NULL;
    newList->prev = NULL;
    newList->next = NULL;
    return newList;
}

ListFourmi* ajout_fourmi(ListFourmi** liste, Fourmi* fourmi) {
    if (!liste || !fourmi) return NULL;

    ListFourmi* newList = (ListFourmi*)malloc(sizeof(ListFourmi));
    if (!newList) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }

    newList->fourmi = fourmi;
    newList->prev = NULL;
    newList->next = *liste;

    if (*liste) {
        (*liste)->prev = newList;
    }
    *liste = newList;
    return newList;
}

void afficher_Liste_fourmi(ListFourmi* liste) {
    if (!liste) {
        printf("Liste vide\n");
        return;
    }
    ListFourmi* current = liste;
    while (current) {
        afficher_fourmi(current->fourmi);
        current = current->next;
    }
}

void compter_Liste_fourmi(ListFourmi* liste) {
    if (!liste) {
        printf("Liste vide\n");
        return;
    }
    int count = 0;
    ListFourmi* current = liste;
    while (current) {
        count++;
        current = current->next;
    }
    printf("Il y a %d fourmis dans la fourmilière\n", count);
}

int compter_fourmi_salle(ListFourmi* liste, int salle) {
    if (!liste) {
        printf("Liste vide\n");
        return 0;
    }
    int count = 0;
    ListFourmi* current = liste;
    while (current) {
        if (current->fourmi->salle == salle) {
            count++;
        }
        current = current->next;
    }
    return count;
}

ListFourmi* retirer_fourmi(ListFourmi** liste, Fourmi* fourmi) {
    if (!liste || !*liste || !fourmi) return *liste;

    ListFourmi* current = *liste;
    while (current && current->fourmi != fourmi) {
        current = current->next;
    }

    if (!current) {
        fprintf(stderr, "Erreur : fourmi non trouvée.\n");
        return *liste;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        *liste = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }

    free(current);
    return *liste;
}

void liberer_liste(ListFourmi* liste) {
    ListFourmi* current = liste;
    while (current) {
        ListFourmi* next = current->next;
        free(current->fourmi);
        free(current);
        current = next;
    }
}

Fourmi* trouver_fourmi(ListFourmi* liste, int id) {
    ListFourmi* current = liste;
    while (current) {
        if (current->fourmi->id_fourmi == id) {
            return current->fourmi;
        }
        current = current->next;
    }
    return NULL;
}

ListFourmi* fusionner_listes(ListFourmi* liste1, ListFourmi* liste2) {
    if (!liste1) return liste2;
    if (!liste2) return liste1;

    ListFourmi* current = liste1;
    while (current->next) {
        current = current->next;
    }

    current->next = liste2;
    if (liste2) {
        liste2->prev = current;
    }

    return liste1;
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
void fourmi_go_base(Fourmi* fourmi, Environnement* map){
    int nombre_deplacement_jour = 5;
    // maps.chunks[i][j].type == 1
    for(int i = 0; i < nombre_deplacement_jour; i++){
        map->chunks[fourmi->coord_x][fourmi->coord_y].pheromones++;
        if (fourmi->coord_x != BASE_COOR_X) {
            fourmi->coord_x += (fourmi->coord_x > BASE_COOR_X) ? -1 : 1;
        }
        if (fourmi->coord_y != BASE_COOR_Y) {
            fourmi->coord_y += (fourmi->coord_y > BASE_COOR_Y) ? -1 : 1;
        }
    }
}

void fourmi_go_aléatoire(Fourmi* fourmi, Environnement* map) {
    map->chunks[fourmi->coord_x][fourmi->coord_y].pheromones++;
    if (fourmi->coord_x == 1 && fourmi->coord_y == 1) {
        srand(time(NULL));
        int random_number = rand() % 2;
        if (random_number == 0) {
            fourmi->coord_x++;
        } else {
            fourmi->coord_y++;
        }
        return;
    }
    if (fourmi->coord_x == 1 && fourmi->coord_y == 25) {
        srand(time(NULL));
        int random_number = rand() % 2;
        if (random_number == 0) {
            fourmi->coord_x++;
        } else {
            fourmi->coord_y--;
        }
        return;
    }
    if (fourmi->coord_x == 25 && fourmi->coord_y == 1) {
        srand(time(NULL));
        int random_number = rand() % 2;
        if (random_number == 0) {
            fourmi->coord_x--;
        } else {
            fourmi->coord_y++;
        }
        return;
    }
    if (fourmi->coord_x == 25 && fourmi->coord_y == 25) {
        srand(time(NULL));
        int random_number = rand() % 2;
        if (random_number == 0) {
            fourmi->coord_x--;
        } else {
            fourmi->coord_y--;
        }
        return;
    }
    if (fourmi->coord_x == 1) {
        srand(time(NULL));
        int random_number = rand() % 3;
        if (random_number == 0) {
            fourmi->coord_x++;
        } else if (random_number == 1) {
            fourmi->coord_y--;
        } else {
            fourmi->coord_y++;
        }
        return;
    }
    if (fourmi->coord_x == 25) {
        srand(time(NULL));
        int random_number = rand() % 3;
        if (random_number == 0) {
            fourmi->coord_x--;
        } else if (random_number == 1) {
            fourmi->coord_y--;
        } else {
            fourmi->coord_y++;
        }
        return;
    }
    if (fourmi->coord_y == 1) {
        srand(time(NULL));
        int random_number = rand() % 3;
        if (random_number == 0) {
            fourmi->coord_y++;
        } else if (random_number == 1) {
            fourmi->coord_x--;
        } else {
            fourmi->coord_x++;
        }
        return;
    }
    if (fourmi->coord_y == 25) {
        srand(time(NULL));
        int random_number = rand() % 3;
        if (random_number == 0) {
            fourmi->coord_y--;
        } else if (random_number == 1) {
            fourmi->coord_x--;
        } else {
            fourmi->coord_x++;
        }
        return;
    }
    srand(time(NULL));
    int random_number = rand() % 4;
    switch (random_number) {
        case 0:
            fourmi->coord_y--;
            break;
        case 1:
            fourmi->coord_y++;
            break;
        case 2:
            fourmi->coord_x--;
            break;
        case 3:
            fourmi->coord_x++;
            break;
    }
}

void deplacement_fourmi(Fourmi* fourmi, Environnement* map){

    if(fourmi->coord_x != BASE_COOR_X || fourmi->coord_y != BASE_COOR_Y){
        if(fourmi->role != EXPLORATRICE){
            //doit rentrer à la base
            fourmi_go_base(fourmi, map);
        }
        else{
            for(int i = 0; i < 5; i++){
            fourmi_go_aléatoire(fourmi, map);
            //se déplace de manière aléatoire
            }
        }
    }
    return;
}

void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map){
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
        retirer_fourmi(&liste, fourmi);
        return;
    }
    deplacement_fourmi(fourmi, map);
}

void update_day_liste_fourmi(ListFourmi* liste, Environnement* maps){
    ListFourmi* newList = liste;
    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return;
    }
    while(newList != NULL){
        update_day_fourmi(newList, newList->fourmi, maps);
        newList = newList->next;
    }
}
