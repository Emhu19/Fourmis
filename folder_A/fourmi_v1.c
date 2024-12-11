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
    int nourriture;
    int materiaux;
    int eau;
    int type; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
}Chunk;

// Structure pour l'environnement
typedef struct {
    int biome;               // Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
    Chunk chunks[25][25];
}Environnement;


// Structure pour le temps
typedef struct {
    int saison;
    int mois;
    int jour;
} Temps;


void generer_rivière(Environnement* E,int x, int y){
    if (x >= 25 || x < 0 || y >= 25 || y< 0){
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
    
    generer_rivière(E, x, y);
}

//generer_lac
void generer_lac(int x, int y, Environnement* E, int proba){
    int alea = nombreAleatoire(99);
    alea ++;
    if(alea<= proba){
        E->chunks[x][y].type = 1;
        if (x>0){
            generer_lac(x-1, y, E, (proba)*2/3);
        }
        if (x<24){
            generer_lac(x+1, y, E, (proba)*2/3);
        }
        if (y>0){
            generer_lac(x, y-1, E, (proba)*2/3);
        }
        if (y<24){
            generer_lac(x, y+1, E, (proba)*2/3);
        }
    }
}


Environnement ajout_eau_miam(Environnement E, Meteo M){

    Environnement E_final;
    E_final.biome = E.biome;
    for (int i = 0; i< 25; i++){    // copie l'Environnement
        for (int j = 0; j< 25; j++){
            E_final.chunks[i][j].type = E.chunks[i][j].type;
        }
    }



    for (int i = 0; i< 25; i++){   // ajoute des points d'eau sur la map
        for (int j = 0; j< 25; j++){
            int p_eau = 0;
            int p_miam = 0;
            
            int alea = nombreAleatoire(99);
            int alea2 = nombreAleatoire(99);
            switch(E.chunks[i][j].type){
                case(0):
                    p_eau = 50; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0;
                    break;
                case(1):
                    p_eau = 100; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0;
                    break;
                case(2):
                    p_eau = 10; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 10;
                    break;
                case(3):
                    p_eau = 25; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 25;
                    break;
                case(4):
                    p_eau = 5; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15;
                    break;
                case(5):
                    p_eau = 0; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0;
                    break;
                case(6):
                    p_eau = 7; //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15;
                    break;
                
            }
            if(alea <= p_eau && E.chunks[i][j].eau< alea){
                E.chunks[i][j].eau = alea;
            }
            if(E.chunks[i][j].type == 1){   //met a 100 le niveau d'eau si on est dans une rivière
                E.chunks[i][j].eau = 99;
            }


            if(alea2 <= p_miam && E.chunks[i][j].nourriture< alea2){
                E_final.chunks[i][j].nourriture = alea2;
            }
        }
    }

    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            if (E.chunks[i][j].type == 1){
                E.chunks[i][j].eau = 49;
            }
        }
    }



    for (int i = 1; i< 24; i++){
        for (int j = 1; j< 24; j++){
            E_final.chunks[i][j].eau = (E.chunks[i-1][j].eau+E.chunks[i-1][j-1].eau+E.chunks[i-1][j+1].eau+E.chunks[i][j-1].eau+E.chunks[i][j+1].eau+E.chunks[i+1][j-1].eau+E.chunks[i+1][j].eau+E.chunks[i+1][j+1].eau+(8*E.chunks[i][j].eau))/16;
        }
    }
    for (int i = 1; i< 24; i++){
        E_final.chunks[i][0].eau = (E.chunks[i-1][0].eau+E.chunks[i-1][1].eau+E.chunks[i][1].eau+E.chunks[i+1][0].eau+E.chunks[i+1][1].eau+(8*E.chunks[i][0].eau))/13;
        E_final.chunks[0][i].eau = (E.chunks[0][i-1].eau+E.chunks[0][i+1].eau+E.chunks[1][i-1].eau+E.chunks[1][i].eau+E.chunks[1][i+1].eau+(8*E.chunks[0][i].eau))/13;
        E_final.chunks[i][24].eau = (E.chunks[i-1][24].eau+E.chunks[i-1][23].eau+E.chunks[i][23].eau+E.chunks[i+1][23].eau+E.chunks[i+1][24].eau+(8*E.chunks[i][24].eau))/13;
        E_final.chunks[24][i].eau = (E.chunks[23][i].eau+E.chunks[23][i-1].eau+E.chunks[23][i+1].eau+E.chunks[24][i-1].eau+E.chunks[24][i+1].eau+(8*E.chunks[24][i].eau))/13;

    }
    E_final.chunks[0][0].eau = (E.chunks[0][1].eau+E.chunks[1][0].eau+E.chunks[1][1].eau+(8*E.chunks[0][0].eau))/11;

    E_final.chunks[0][24].eau = (E.chunks[0][23].eau+E.chunks[1][23].eau+E.chunks[1][24].eau+(8*E.chunks[0][24].eau))/11;

    E_final.chunks[24][0].eau = (E.chunks[23][0].eau+E.chunks[23][1].eau+E.chunks[24][1].eau+(8*E.chunks[24][0].eau))/11;

    E_final.chunks[24][24].eau = (E.chunks[23][24].eau+E.chunks[23][23].eau+E.chunks[24][23].eau+(8*E.chunks[24][24].eau))/11;


    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            if (E.chunks[i][j].type == 1){
                E_final.chunks[i][j].eau = 49;
            }
        }
    }


    return E_final;
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

    for (int i = 0; i< 25; i++){
        for (int j = 0; j<25; j++){
            E.chunks[i][j].type = -1; 
            E.chunks[i][j].eau = 0; 
            E.chunks[i][j].nourriture = 0; 
        }
    }

    int x = 0;
    int y = nombreAleatoire(24);

    generer_rivière(&E, x, y);

    x = nombreAleatoire(24);
    y = nombreAleatoire(24);

    generer_lac(x, y, &E, 100);

    

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

    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
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
    Meteo M;
    //for (int i = 0; i< 10; i++){

    
    E = ajout_eau_miam(E, M);
    //}

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
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
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
    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            printf("%2d ", E.chunks[i][j].nourriture);
        }
        printf("\n");
    }
}



int main() {
    srand(time(NULL));

    Environnement E = genererEnvironnement();
    afficher_envi(E);

    return 0;
}
