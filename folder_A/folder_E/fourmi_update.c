#include "fourmi.h"


void update_day_fourmi_inventaire(Fourmi* fourmi, Environnement* map){
    if(map->chunks[fourmi->coord_x][fourmi->coord_y].nourriture > 0 && fourmi->inventaire->nourriture < 6){
        map->chunks[fourmi->coord_x][fourmi->coord_y].nourriture--;
        fourmi->inventaire->nourriture++;
    }
}

void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map, Temps* saison){
    if (fourmi == NULL) {
        fprintf(stderr, "Erreur : le pointeur fourmi est NULL.\n");
        return;
    }
    fourmi->faim -= fourmi->besoin_faim;
    fourmi->eau -= fourmi->besoin_eau;
    // int besoin_nourriture = evaluerBesoinNourriture(liste, );
    // evaluerBesoinNourriture(ListFourmi *Fourmis, Ressource *Nourriture);
    if(1 <= 1){ //si ressource disponible // la fonction fonctionne bien!!
        fourmi->faim += 1;
        fourmi->eau += 1;
//         ressource--;
    }
    ajuster_role(fourmi, liste, saison);
    deplacement_fourmi(fourmi, map);
}

void update_day_liste_fourmi(ListFourmi* liste, Environnement* maps, Temps* saison){
    ListFourmi* newList = liste;
    if(newList->fourmi == NULL){
        printf("Liste vide\n");
        return;
    }
    while(newList != NULL){
         if(newList->fourmi == NULL){
            fprintf(stderr, "Erreur : y a pas de fourmi.\n");
            return;
        }
        update_day_fourmi(newList, newList->fourmi, maps, saison);
        newList = newList->next;
    }
}
