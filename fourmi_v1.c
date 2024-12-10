#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define point_virgule ;

// Fonction pour générer un nombre aléatoire entre 0 et n
int nombreAleatoire(int n) {
    return rand() % (n + 1)point_virgule
}


typedef struct {
    int proba_precipitation point_virgule
    int force_precipitation point_virgule
    float temperature_moyenne point_virgule
    float variation_temperature;
    float temperature;             // Température actuelle
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
    int type; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
}Chunk;

// Structure pour l'environnement
typedef struct {
    int biome;               // Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
    Chunk chunks[50][50];
}Environnement;


// Structure pour le temps
typedef struct {
    int saison;
    int mois;
    int jour;
} Temps;


void generer_rivière(Environnement* E,int x, int y){
    if (x >= 50 || x < 0 || y >= 50 || y< 0){
        return;
    }
    E->chunks[x][y].type = 1;
    int alea = nombreAleatoire(3);
    switch(alea){
        case(0):
            x ++;
            break;
        case(1):
            x ++;
            break;
        case(2):
            y ++;
            break;
        case(3):
            y --;
            break;
    }
    //printf("%d ", alea);
    
    generer_rivière(E, x, y);
}


Environnement genererEnvironnement(){
    Environnement E;
    printf("dans quel biome est votre fourmilière ?\n");
    printf("Tapez 0 pour la forêt,\n");
    printf("Tapez 1 pour la desert,\n");
    printf("Tapez 2 pour la plaine,\n");
    printf("Tapez 3 pour la forêt tropicale,\n");
    printf("Tapez 4 pour la ville,\n");
    printf("Tapez 5 pour la toundra,\n");
    printf("Tapez 6 pour la taiga,\n");
    printf("Tapez 7 pour la montagne,\n");
    printf("Tapez 8 pour la haute montagne,\n");

    scanf("%d", &E.biome);

    for (int i = 0; i< 50; i++){
        for (int j = 0; j<50; j++){
            E.chunks[i][j].type = -1;  
        }
    }

    int x = 0;
    int y = nombreAleatoire(49);

    generer_rivière(&E, x, y);

    

    //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
    int p_plaine;
    int p_arbre;
    int p_sable;
    int p_lune;
    int p_roche;

    switch(E.biome){
        case (0):
            p_plaine = 20;
            p_arbre = 70;
            p_sable = 1;
            p_lune = 0;
            p_roche = 9;
            break;
        case (1):
            p_plaine = 1;
            p_arbre = 5;
            p_sable = 74;
            p_lune = 0;
            p_roche = 20;
            break;
        case (2):
            p_plaine = 75;
            p_arbre = 15;
            p_sable = 1;
            p_lune = 0;
            p_roche = 9;
            break;
        case (3):
            p_plaine = 1;
            p_arbre = 98;
            p_sable = 0;
            p_lune = 0;
            p_roche = 1;
            break;
        case (4):
            p_plaine = 10;
            p_arbre = 10;
            p_sable = 0;
            p_lune = 0;
            p_roche = 80;
            break;
        case (5):  
            p_plaine = 75;
            p_arbre = 15;
            p_sable = 1;
            p_lune = 0;
            p_roche = 9;
            break;
        case (6):
            p_plaine = 30;
            p_arbre = 70;
            p_sable = 0;
            p_lune = 0;
            p_roche = 10;
            break;
        case (7):
            p_plaine = 30;
            p_arbre = 30;
            p_sable = 0;
            p_lune = 0;
            p_roche = 40;
            break;
        case (8):
            p_plaine = 40;
            p_arbre = 10;
            p_sable = 0;
            p_lune = 0;
            p_roche = 50;
            break;
        case (1969):
            p_plaine = 0;
            p_arbre = 0;
            p_sable = 0;
            p_lune = 100;
            p_roche = 0;
            break;
    }

    for (int i = 0; i< 50; i++){
            for (int j = 0; j< 50; j++){
                if (E.chunks[i][j].type != 1){

                    int alea = nombreAleatoire(99);  //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    alea -= p_plaine;  
                    if (alea <0){
                        E.chunks[i][j].type = 2;
                        alea += 200;
                    }
                    alea -= p_arbre;  
                    if (alea <0){
                        E.chunks[i][j].type = 3;
                        alea += 200;
                    }
                    alea -= p_sable;  
                    if (alea <0){
                        E.chunks[i][j].type = 4;
                        alea += 200;
                    }
                    alea -= p_lune;  
                    if (alea <0){
                        E.chunks[i][j].type = 5;
                        alea += 200;
                    }
                    alea -= p_roche;  
                    if (alea <0){
                        E.chunks[i][j].type = 6;
                        alea += 200;
                    }
                }
            }
    }


    return E;
}
    //permet de générer l'environnement en fonction des préférences de l'utilisateur (avec une part d'aléatoire) génération procédurale


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

    tps.mois = 0;
    tps.jour = 0;
    tps.saison = 0;
    return tps;
}
/*
void init_meteo(Environnement* E){
    Meteo m;
    switch(E->biome){
        case(0):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(1):
            m.proba_precipitation = 1;
            m.force_precipitation = 25;
        case(2):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(3):
            m.proba_precipitation = 70;
            m.force_precipitation = 25;
        case(4):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(5):   //0: forêt,1: désert,2: plaine, 3:foret tropicale,4: ville,5: toundra, 6:taiga,7: montagne,8: haute montagne,1969: espace
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(6):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(7):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(8):
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
        case(1969):
            m.proba_precipitation = 0;
            m.force_precipitation = 0;
    }
}
*/
/*
void maj_meteo(Meteo* m, Environnement* e, Temps* t){
    //printf("%d\n", nombreAleatoire(10));
}
*/
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


void afficher_envi(Environnement E) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            switch (E.chunks[i][j].type) {
                case -1:
                    printf("\033[47m  \033[0m"); // Blanc
                    break;
                case 1:
                    printf("\033[44m  \033[0m"); // Bleu
                    break;
                case 2:
                    printf("\033[42m  \033[0m"); // Vert foncé (gris + texte vert)
                    break;
                case 3:
                    printf("\033[48;2;%d;%d;%dm  \033[0m", 0, 100, 0); // Vert clair (vert vif)
                    break;
                case 4:
                    printf("\033[43m  \033[0m"); // Jaune
                    break;
                case 5:
                    printf("\033[48;2;%d;%d;%dm  \033[0m", 245, 245, 220);
                    break;
                case 6:
                    printf("\033[100m  \033[0m"); // Gris
                    break;
                default:
                    printf("\033[40m  \033[0m"); // Noir (valeur inattendue)
                    break;
            }
        }
        printf("\n"); // Nouvelle ligne après chaque ligne de la matrice
    }
}


void afficher_envi_v(Environnement E){
    for (int i = 0; i< 50; i++){
        for (int j = 0; j< 50; j++){
            printf("%2d ", E.chunks[i][j].type);
        }
        printf("\n");
    }
}



int main() {
    srand(time(NULL));

    //printf("%d\n", nombreAleatoire(10));

    Environnement E = genererEnvironnement();
    afficher_envi(E);

    return 0;
}






