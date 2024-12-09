#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Fonction pour générer un nombre aléatoire entre 0 et n
int nombreAleatoire(int n) {
    return rand() % (n + 1);
}


typedef struct {
    int proba_precipitation;
    int force_precipitation;
    float temperature_moyenne;
    float variation_temperature;
    float temperature;     // Température actuelle
    bool precipitation;            // Niveau de précipitation
} Meteo;

// Structure pour les prédateurs
typedef struct {
    int id_predateur;
    char nom_predateur[50];
    int coordonnée_x;
    int coordonnée_y;
    int santé;
    int vitesse;
    int force;  // le degat qu'il fait
}Predateurs;

typedef struct {
    int quantite_nourriture;
    int quantite_materiaux;
    int quantite_eau;
    char type[50]; //rivière, flaque d'eau, sable, fourmilière ...
}Chunk;

typedef struct {
    Chunk chunk;
    Chunk* gauche;
    Chunk* droite;
    Chunk* haut;
    Chunk* bas;
}Liste_chunk;

// Structure pour l'environnement
typedef struct {
    int biome;               // Biome (ex: espace, forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne)
    Liste_chunk chunks;
}Environnement;


// Structure pour le temps
typedef struct {
    int saison;
    int mois;
    int jour;
} Temps;

/*
Environnement genererEnvironnement()
    //permet de générer l'environnement en fonction des préférences de l'utilisateur (avec une part d'aléatoire) génération procédurale
*/

void incr_temp(Temps* t){

    t->jour++;
    switch(t->mois){
        case(0):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
        case(1):
            if (t->jour >28){
                t->jour-= 28;
                t->mois++;
            }
            break;
        case(2):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
        case(3):
            if (t->jour >30){
                t->jour-= 30;
                t->mois++;
            }
            break;
        case(4):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
        case(5):
            if (t->jour >30){
                t->jour-= 30;
                t->mois++;
            }
            break;
        case(6):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
        case(7):
            if (t->jour >31){
                t->
            jour-= 31;
                t->mois++;
            }
            break;
        case(8):
            if (t->jour >30){
                t->jour-= 30;
                t->mois++;
            }
            break;
        case(9):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
        case(10):
            if (t->jour >30){
                t->jour-= 30;
                t->mois++;
            }
            break;
        case(11):
            if (t->jour >31){
                t->jour-= 31;
                t->mois++;
            }
            break;
    }
}



Temps init_temps(){
    Temps tps;
    printf("de quelle taille voulez faire les saut de temps ? en minutes\n");
    scanf("%d", &tps.saut_temps);
    strcpy(tps.mois, "janvier");
    tps.jour = 0;
    tps.heure = 0;
    tps.minute = 0;
    strcpy(tps.saison, "hiver");
    return tps;
}



void init_meteo(Meteo* m, Environnement* e){
    int proba_precipitation;
    if (!strcmp(e->Biome, "espace")){
        m->proba_precipitation = 0;
        m->force_precipitation = 0;
    }

    if (!strcmp(e->Biome, "foret")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "desert")){
        m->proba_precipitation = 100;
        m->force_precipitation = 25;
    }

    if (!strcmp(e->Biome, "plaine")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "foret tropicale")){
        m->proba_precipitation = 2;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "ville")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "toundra")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "taiga")){//espace, forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "montagne")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }

    if (!strcmp(e->Biome, "haute montagne")){
        m->proba_precipitation = 10;
        m->force_precipitation = 10;
    }
}


void maj_meteo(Meteo* m, Environnement* e, Temps* t){
    //printf("%d\n", nombreAleatoire(10));
}

    //initialise le temps
/*
void maj_meteo(Meteo m, Environnement e, Temps t)
    //met à jour la meteo en fonction des informations contenus dans Meteo, en fonction du biome dans Environnement, et du temps Temps(mois,saison...)
*/
/*
void maj_environnement(Meteo m, Environnement e, Temps t)
    //met a jour l'envuronnement en fonction de la météo, du temps (par exemple s'il pleut, les chunks vont se remplir d'eau)
*/
/*
void maj_predateur(Predateur p, Environnement e, Temps t, Liste_fourmilière fl)
    //met a jour les infos du predateur (position, dort ou pas, traverse la rivière ou pas etc...), et gère les combats avec les fourmis s'ils se rencontrent 
*/



int main() {
    srand(time(NULL));

    printf("%d\n", nombreAleatoire(10));
    return 0;
}






