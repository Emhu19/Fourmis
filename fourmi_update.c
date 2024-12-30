#include "fourmi.h"


void update_day_fourmi_inventaire(Fourmi* fourmi, Environnement* map){
    if(map->chunks[fourmi->coord_x][fourmi->coord_y].p_miam > 0 && fourmi->inventaire->nourriture <= 5){
        map->chunks[fourmi->coord_x][fourmi->coord_y].p_miam--;
        fourmi->inventaire->nourriture++;
    }
    if(map->chunks[fourmi->coord_x][fourmi->coord_y].p_bois > 0 && fourmi->inventaire->bois <= 5){
        map->chunks[fourmi->coord_x][fourmi->coord_y].p_bois--;
        fourmi->inventaire->bois++;
    }
    if(map->chunks[fourmi->coord_x][fourmi->coord_y].p_seve > 0 && fourmi->inventaire->seve <= 5){
        map->chunks[fourmi->coord_x][fourmi->coord_y].p_seve--;
        fourmi->inventaire->seve++;
    }
    if(map->chunks[fourmi->coord_x][fourmi->coord_y].p_feuilles > 0 && fourmi->inventaire->feuilles <= 5){
        map->chunks[fourmi->coord_x][fourmi->coord_y].p_feuilles--;
        fourmi->inventaire->feuilles++;
    }
}

void update_day_fourmi_Miel(Fourmi* fourmi){
    //doit aller dans sa salle si n'y est pas si nan doit attendre
    return;
}

void update_day_fourmi_Agriculteur(Fourmi* fourmi){
    //doit aller dans sa salle si n'y est pas et cultiver des champignons
    return;
}

void update_day_fourmi_Eleveur(Fourmi* fourmi){
    //doit aller dans sa salle si n'y est pas et cultiver des elevers des pucerons
    return;
}

void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map, Temps* saison){
    if (fourmi == NULL) {
        fprintf(stderr, "Erreur : le pointeur fourmi est NULL.\n");
        return;
    }
    fourmi->age++;
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
    if(fourmi->role == AGRICOLE) update_day_fourmi_Miel(fourmi);
    if(fourmi->role == ELEVEUR) update_day_fourmi_Eleveur(fourmi);
    if(fourmi->role == POT_DE_MIEL) update_day_fourmi_Agriculteur(fourmi);
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
