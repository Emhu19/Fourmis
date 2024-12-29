#include "fourmi.h"
#include <stdlib.h>
#include <time.h>

bool fourmi_est_dans_base(Fourmi fourmi){
    if(fourmi.coord_x != BASE_COOR_X || fourmi.coord_y != BASE_COOR_Y) return false;
    return true;
}

void fourmi_go_base(Fourmi* fourmi, Environnement* map){
    int nombre_deplacement_jour = 5;
    // maps.chunks[i][j].type == 1
    for(int i = 0; i < nombre_deplacement_jour; i++){
        if(fourmi_est_dans_base(*fourmi)) return;
        map->chunks[fourmi->coord_x][fourmi->coord_y].pheromones++;
        if (fourmi->coord_x != BASE_COOR_X) {
            fourmi->coord_x += (fourmi->coord_x > BASE_COOR_X) ? -1 : 1;
        }
        if (fourmi->coord_y != BASE_COOR_Y) {
            fourmi->coord_y += (fourmi->coord_y > BASE_COOR_Y) ? -1 : 1;
        }
    }
}

void un_deplacement_fourmi_aléatoire(Fourmi* fourmi){
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

void fourmi_go_aléatoire(Fourmi* fourmi, Environnement* map) {
    map->chunks[fourmi->coord_x][fourmi->coord_y].pheromones++;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    double probabilités[4] = {0};
    double somme_pheromones = 0.0;

    for (int i = 0; i < 4; i++) {
        int nx = fourmi->coord_x + dx[i];
        int ny = fourmi->coord_y + dy[i];

        if (nx >= 1 && nx <= 25 && ny >= 1 && ny <= 25) {
            probabilités[i] = map->chunks[nx][ny].pheromones;
            somme_pheromones += probabilités[i];
        } else {
            probabilités[i] = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (somme_pheromones > 0) {
            probabilités[i] /= somme_pheromones;
        }
    }

    double rand_val = (double)rand() / RAND_MAX;
    double seuil = 0.0;

    for (int i = 0; i < 4; i++) {
        seuil += probabilités[i];
        if (rand_val <= seuil) {
            fourmi->coord_x += dx[i];
            fourmi->coord_y += dy[i];
            return;
        }
    }
    // printf("AWWWWWWWWWWWWWWWWWWWWWWWW\n");
}


void deplacement_ronde(Fourmi* fourmi, Environnement* map){
    if(fourmi_est_dans_base(*fourmi)){
        un_deplacement_fourmi_aléatoire(fourmi);
    }
    else fourmi_go_base(fourmi, map);
}

void deplacement_fourmi(Fourmi* fourmi, Environnement* map){

    if(fourmi->role == SOLDAT){
        deplacement_ronde(fourmi, map);
        return;
    }
    if(!fourmi_est_dans_base(*fourmi)){
        if(fourmi->role == EXPLORATRICE || fourmi->role == COLLECTRICE_MIELLAT){
            for(int i = 0; i < 5; i++){
                    update_day_fourmi_inventaire(fourmi, map);
                    fourmi_go_aléatoire(fourmi, map); //se déplace de manière aléatoire
                }
        }
        else{
            fourmi_go_base(fourmi, map);
        }
    }
    else{
        if(fourmi->role == EXPLORATRICE || fourmi->role == COLLECTRICE_MIELLAT){
            for(int i = 0; i < 5; i++){
                    // update_day_fourmi_inventaire(fourmi, map);
                    if(fourmi == NULL)
                        return;
                    fourmi_go_aléatoire(fourmi, map); //se déplace de manière aléatoire
                }
        }
    }
}
