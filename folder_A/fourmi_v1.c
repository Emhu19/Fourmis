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
    float variation_temperature point_virgule
    float temperature point_virgule             // Température actuelle
    bool precipitation point_virgule            // Niveau de précipitation
} Meteo point_virgule

// Structure pour les prédateurs
typedef struct {
    int id_predateur point_virgule
    char nom_predateur[50] point_virgule
    int coordonnée_x point_virgule
    int coordonnée_y point_virgule
    int santé point_virgule
    int vitesse point_virgule
    int force point_virgule  // le degat qu'il fait
}Predateurs point_virgule

typedef struct {
    int nourriture point_virgule
    int materiaux point_virgule
    int eau point_virgule
    int type point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
}Chunk point_virgule

// Structure pour l'environnement
typedef struct {
    int biome point_virgule               // Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
    Chunk chunks[25][25] point_virgule
}Environnement point_virgule


// Structure pour le temps
typedef struct {
    int saison point_virgule
    int mois point_virgule
    int jour point_virgule
} Temps point_virgule


void generer_rivière(Environnement* E,int x, int y){
    if (x >= 25 || x < 0 || y >= 25 || y< 0){
        return point_virgule
    }
    E->chunks[x][y].type = 1 point_virgule
    int alea = nombreAleatoire(3) point_virgule
    switch(alea){
        case(0):
            x ++ point_virgule
            break point_virgule
        case(1):
            x ++ point_virgule
            break point_virgule
        case(2):
            y ++ point_virgule
            break point_virgule
        case(3):
            y -- point_virgule
            break point_virgule
    }
    
    generer_rivière(E, x, y) point_virgule
}

//generer_lac
void generer_lac(int x, int y, Environnement* E, int proba){
    int alea = nombreAleatoire(99) point_virgule
    alea ++ point_virgule
    if(alea<= proba){
        E->chunks[x][y].type = 1 point_virgule
        if (x>0){
            generer_lac(x-1, y, E, (proba)*2/3) point_virgule
        }
        if (x<24){
            generer_lac(x+1, y, E, (proba)*2/3) point_virgule
        }
        if (y>0){
            generer_lac(x, y-1, E, (proba)*2/3) point_virgule
        }
        if (y<24){
            generer_lac(x, y+1, E, (proba)*2/3) point_virgule
        }
    }
}


Environnement ajout_eau_miam(Environnement E, Meteo M){

    Environnement E_final point_virgule
    E_final.biome = E.biome point_virgule
    for (int i = 0 point_virgule i< 25 point_virgule i++){    // copie l'Environnement
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            E_final.chunks[i][j].type = E.chunks[i][j].type point_virgule
        }
    }



    for (int i = 0 point_virgule i< 25 point_virgule i++){   // ajoute des points d'eau sur la map
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            int p_eau = 0 point_virgule
            int p_miam = 0 point_virgule
            
            int alea = nombreAleatoire(99) point_virgule
            int alea2 = nombreAleatoire(99) point_virgule
            switch(E.chunks[i][j].type){
                case(0):
                    p_eau = 50 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0 point_virgule
                    break point_virgule
                case(1):
                    p_eau = 100 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0 point_virgule
                    break point_virgule
                case(2):
                    p_eau = 10 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 10 point_virgule
                    break point_virgule
                case(3):
                    p_eau = 25 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 25 point_virgule
                    break point_virgule
                case(4):
                    p_eau = 5 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15 point_virgule
                    break point_virgule
                case(5):
                    p_eau = 0 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0 point_virgule
                    break point_virgule
                case(6):
                    p_eau = 7 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15 point_virgule
                    break point_virgule
                
            }
            if(alea <= p_eau && E.chunks[i][j].eau< alea){
                E.chunks[i][j].eau = alea point_virgule
            }
            if(E.chunks[i][j].type == 1){   //met a 100 le niveau d'eau si on est dans une rivière
                E.chunks[i][j].eau = 99 point_virgule
            }


            if(alea2 <= p_miam && E.chunks[i][j].nourriture< alea2){
                E_final.chunks[i][j].nourriture = alea2 point_virgule
            }
        }
    }

    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            if (E.chunks[i][j].type == 1){
                E.chunks[i][j].eau = 49 point_virgule
            }
        }
    }



    for (int i = 1 point_virgule i< 24 point_virgule i++){
        for (int j = 1 point_virgule j< 24 point_virgule j++){
            E_final.chunks[i][j].eau = (E.chunks[i-1][j].eau+E.chunks[i-1][j-1].eau+E.chunks[i-1][j+1].eau+E.chunks[i][j-1].eau+E.chunks[i][j+1].eau+E.chunks[i+1][j-1].eau+E.chunks[i+1][j].eau+E.chunks[i+1][j+1].eau+(8*E.chunks[i][j].eau))/16 point_virgule
        }
    }
    for (int i = 1 point_virgule i< 24 point_virgule i++){
        E_final.chunks[i][0].eau = (E.chunks[i-1][0].eau+E.chunks[i-1][1].eau+E.chunks[i][1].eau+E.chunks[i+1][0].eau+E.chunks[i+1][1].eau+(8*E.chunks[i][0].eau))/13 point_virgule
        E_final.chunks[0][i].eau = (E.chunks[0][i-1].eau+E.chunks[0][i+1].eau+E.chunks[1][i-1].eau+E.chunks[1][i].eau+E.chunks[1][i+1].eau+(8*E.chunks[0][i].eau))/13 point_virgule
        E_final.chunks[i][24].eau = (E.chunks[i-1][24].eau+E.chunks[i-1][23].eau+E.chunks[i][23].eau+E.chunks[i+1][23].eau+E.chunks[i+1][24].eau+(8*E.chunks[i][24].eau))/13 point_virgule
        E_final.chunks[24][i].eau = (E.chunks[23][i].eau+E.chunks[23][i-1].eau+E.chunks[23][i+1].eau+E.chunks[24][i-1].eau+E.chunks[24][i+1].eau+(8*E.chunks[24][i].eau))/13 point_virgule

    }
    E_final.chunks[0][0].eau = (E.chunks[0][1].eau+E.chunks[1][0].eau+E.chunks[1][1].eau+(8*E.chunks[0][0].eau))/11 point_virgule

    E_final.chunks[0][24].eau = (E.chunks[0][23].eau+E.chunks[1][23].eau+E.chunks[1][24].eau+(8*E.chunks[0][24].eau))/11 point_virgule

    E_final.chunks[24][0].eau = (E.chunks[23][0].eau+E.chunks[23][1].eau+E.chunks[24][1].eau+(8*E.chunks[24][0].eau))/11 point_virgule

    E_final.chunks[24][24].eau = (E.chunks[23][24].eau+E.chunks[23][23].eau+E.chunks[24][23].eau+(8*E.chunks[24][24].eau))/11 point_virgule


    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            if (E.chunks[i][j].type == 1){
                E_final.chunks[i][j].eau = 49 point_virgule
            }
        }
    }


    return E_final point_virgule
}


Environnement genererEnvironnement(){
    Environnement E point_virgule

    printf("dans quel biome est votre fourmilière ?\n") point_virgule
    printf("Tapez 0 pour la forêt,\n") point_virgule
    printf("Tapez 1 pour la desert,\n") point_virgule
    printf("Tapez 2 pour la plaine,\n") point_virgule
    printf("Tapez 3 pour la forêt tropicale,\n") point_virgule
    printf("Tapez 4 pour la ville,\n") point_virgule
    printf("Tapez 5 pour la toundra,\n") point_virgule
    printf("Tapez 6 pour la taiga,\n") point_virgule
    printf("Tapez 7 pour la montagne,\n") point_virgule
    printf("Tapez 8 pour la haute montagne,\n") point_virgule

    scanf("%d", &E.biome) point_virgule

    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j<25 point_virgule j++){
            E.chunks[i][j].type = -1 point_virgule 
            E.chunks[i][j].eau = 0 point_virgule 
            E.chunks[i][j].nourriture = 0 point_virgule 
        }
    }

    int x = 0 point_virgule
    int y = nombreAleatoire(24) point_virgule

    generer_rivière(&E, x, y) point_virgule

    x = nombreAleatoire(24) point_virgule
    y = nombreAleatoire(24) point_virgule

    generer_lac(x, y, &E, 100) point_virgule

    

    //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
    int p_plaine point_virgule
    int p_arbre point_virgule
    int p_sable point_virgule
    int p_lune point_virgule
    int p_roche point_virgule

    switch(E.biome){
        case (0):
            p_plaine = 20 point_virgule
            p_arbre = 70 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            break point_virgule
        case (1):
            p_plaine = 1 point_virgule
            p_arbre = 5 point_virgule
            p_sable = 74 point_virgule
            p_lune = 0 point_virgule
            p_roche = 20 point_virgule
            break point_virgule
        case (2):
            p_plaine = 75 point_virgule
            p_arbre = 15 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            break point_virgule
        case (3):
            p_plaine = 1 point_virgule
            p_arbre = 98 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 1 point_virgule
            break point_virgule
        case (4):
            p_plaine = 10 point_virgule
            p_arbre = 10 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 80 point_virgule
            break point_virgule
        case (5):  
            p_plaine = 75 point_virgule
            p_arbre = 15 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            break point_virgule
        case (6):
            p_plaine = 30 point_virgule
            p_arbre = 70 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 10 point_virgule
            break point_virgule
        case (7):
            p_plaine = 30 point_virgule
            p_arbre = 30 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 40 point_virgule
            break point_virgule
        case (8):
            p_plaine = 40 point_virgule
            p_arbre = 10 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 50 point_virgule
            break point_virgule
        case (1969):
            p_plaine = 0 point_virgule
            p_arbre = 0 point_virgule
            p_sable = 0 point_virgule
            p_lune = 100 point_virgule
            p_roche = 0 point_virgule
            break point_virgule
    }

    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            if (E.chunks[i][j].type != 1){

                int alea = nombreAleatoire(99) point_virgule  //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                alea -= p_plaine point_virgule  
                if (alea <0){
                    E.chunks[i][j].type = 2 point_virgule
                    alea += 200 point_virgule
                }
                alea -= p_arbre point_virgule  
                if (alea <0){
                    E.chunks[i][j].type = 3 point_virgule
                    alea += 200 point_virgule
                }
                alea -= p_sable point_virgule  
                if (alea <0){
                    E.chunks[i][j].type = 4 point_virgule
                    alea += 200 point_virgule
                }
                alea -= p_lune point_virgule  
                if (alea <0){
                    E.chunks[i][j].type = 5 point_virgule
                    alea += 200 point_virgule
                }
                alea -= p_roche point_virgule  
                if (alea <0){
                    E.chunks[i][j].type = 6 point_virgule
                    alea += 200 point_virgule
                }
            }
        }
    }
    Meteo M point_virgule
    //for (int i = 0 point_virgule i< 10 point_virgule i++){

    
    E = ajout_eau_miam(E, M) point_virgule
    //}

    return E point_virgule
}
    //permet de générer l'environnement en fonction des préférences de l'utilisateur (avec une part d'aléatoire) génération procédurale


void incr_temp(Temps* t){

    t->jour++ point_virgule
    switch(t->mois){
        case(0):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(1):
            if (t->jour >28){
                t->jour-= 28 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(2):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(3):
            if (t->jour >30){
                t->jour-= 30 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(4):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(5):
            if (t->jour >30){
                t->jour-= 30 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(6):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(7):
            if (t->jour >31){
                t->
            jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(8):
            if (t->jour >30){
                t->jour-= 30 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(9):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(10):
            if (t->jour >30){
                t->jour-= 30 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
        case(11):
            if (t->jour >31){
                t->jour-= 31 point_virgule
                t->mois++ point_virgule
            }
            break point_virgule
    }
}



Temps init_temps(){
    Temps tps point_virgule

    tps.mois = 0 point_virgule
    tps.jour = 0 point_virgule
    tps.saison = 0 point_virgule
    return tps point_virgule
}
/*
void init_meteo(Environnement* E){
    Meteo m point_virgule
    switch(E->biome){
        case(0):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(1):
            m.proba_precipitation = 1 point_virgule
            m.force_precipitation = 25 point_virgule
        case(2):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(3):
            m.proba_precipitation = 70 point_virgule
            m.force_precipitation = 25 point_virgule
        case(4):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(5):   //0: forêt,1: désert,2: plaine, 3:foret tropicale,4: ville,5: toundra, 6:taiga,7: montagne,8: haute montagne,1969: espace
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(6):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(7):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(8):
            m.proba_precipitation = 10 point_virgule
            m.force_precipitation = 10 point_virgule
        case(1969):
            m.proba_precipitation = 0 point_virgule
            m.force_precipitation = 0 point_virgule
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
    for (int i = 0 point_virgule i < 25 point_virgule i++) {
        for (int j = 0 point_virgule j < 25 point_virgule j++) {
            switch (E.chunks[i][j].type) {
                case -1:
                    printf("\033[47m  \033[0m") point_virgule // Blanc
                    break point_virgule
                case 1:
                    printf("\033[44m  \033[0m") point_virgule // Bleu
                    break point_virgule
                case 2:
                    printf("\033[42m  \033[0m") point_virgule // Vert foncé (gris + texte vert)
                    break point_virgule
                case 3:
                    printf("\033[48 point_virgule2 point_virgule%d point_virgule%d point_virgule%dm  \033[0m", 0, 100, 0) point_virgule // Vert clair (vert vif)
                    break point_virgule
                case 4:
                    printf("\033[43m  \033[0m") point_virgule // Jaune
                    break point_virgule
                case 5:
                    printf("\033[48 point_virgule2 point_virgule%d point_virgule%d point_virgule%dm  \033[0m", 245, 245, 220) point_virgule
                    break point_virgule
                case 6:
                    printf("\033[100m  \033[0m") point_virgule // Gris
                    break point_virgule
                default:
                    printf("\033[40m  \033[0m") point_virgule // Noir (valeur inattendue)
                    break point_virgule
            }
        }
        printf("\n") point_virgule // Nouvelle ligne après chaque ligne de la matrice
    }
}


void afficher_envi_v(Environnement E){
    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            printf("%2d ", E.chunks[i][j].nourriture) point_virgule
        }
        printf("\n") point_virgule
    }
}



int main() {
    srand(time(NULL)) point_virgule

    Environnement E = genererEnvironnement() point_virgule
    afficher_envi(E) point_virgule

    return 0 point_virgule
}
