#include "fourmi.h"

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
