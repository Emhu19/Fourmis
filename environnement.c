#include "environnement.h"
#include "fourmi.h"
//#define entier int


// Fonction pour générer un nombre aléatoire entre 0 et n
int nombreAleatoire(int n) {
    return rand() % (n + 1)point_virgule
}

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


void ajout_eau_miam(Environnement* E, Meteo M){
    int tab_eau[25][25] point_virgule

    for (int i = 0 point_virgule i< 25 point_virgule i++){   // ajoute des points d'eau sur la map
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            int p_eau = 0 point_virgule
            int p_miam = 0 point_virgule
            int p_bois = 0;
            int p_roche = 0;
            int p_feuille = 0;
            int p_seve = 0;
            int p_champignon = 0;

            int alea = nombreAleatoire(99) point_virgule
            int alea2 = nombreAleatoire(99) point_virgule
            int alea3 = nombreAleatoire(99) point_virgule
            int alea4 = nombreAleatoire(99) point_virgule
            int alea5 = nombreAleatoire(99) point_virgule
            int alea6 = nombreAleatoire(99) point_virgule
            int alea7 = nombreAleatoire(99) point_virgule


            switch(E->chunks[i][j].type){
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
                    p_bois = 0;
                    p_roche = 0;
                    p_feuille = 5;
                    p_seve = 0;
                    p_champignon = 0;
                    break point_virgule
                case(3):
                    p_eau = 25 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 25 point_virgule
                    p_bois = 10;
                    p_roche = 0;
                    p_feuille = 15;
                    p_seve = 5;
                    p_champignon = 2;
                    break point_virgule
                case(4):
                    p_eau = 5 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15 point_virgule
                    p_bois = 0;
                    p_roche = 10;
                    p_feuille = 0;
                    p_seve = 0;
                    p_champignon = 0;
                    break point_virgule
                case(5):
                    p_eau = 0 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 0 point_virgule
                    break point_virgule
                case(6):
                    p_eau = 7 point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
                    p_miam = 15 point_virgule
                    p_bois = 0;
                    p_roche = 15;
                    p_feuille = 5;
                    p_seve = 0;
                    p_champignon = 0;
                    break point_virgule

            }
            if(alea <= p_eau && E->chunks[i][j].eau< alea){
                E->chunks[i][j].eau = alea point_virgule
            }
            if(E->chunks[i][j].type == 1){   //met a 100 le niveau d'eau si on est dans une rivière
                E->chunks[i][j].eau = 49 point_virgule
            }


            if(alea2 <= p_miam && E->chunks[i][j].nourriture< alea2){  // la nourriture aussi peut etre au dessus de 1
                E->chunks[i][j].nourriture = alea2 point_virgule
            }

            if(alea3 <= p_bois){   // les materiaux ne peuvent pas etre a plus que 1 par case
                E->chunks[i][j].bois = 1 point_virgule
            }

            if(alea4 <= p_feuille){
                E->chunks[i][j].feuille = 1 point_virgule
            }

            if(alea5 <= p_roche){
                E->chunks[i][j].roche = 1 point_virgule
            }

            if(alea6 <= p_seve){
                E->chunks[i][j].seve = 1 point_virgule
            }

            if(alea7 <= p_champignon){
                E->chunks[i][j].champignon = 1 point_virgule
            }
        }
    }


    for (int i = 1; i < 24; i++) {
        for (int j = 1; j < 24; j++) {
            tab_eau[i][j] = (E->chunks[i-1][j].eau + E->chunks[i-1][j-1].eau + E->chunks[i-1][j+1].eau +E->chunks[i][j-1].eau + E->chunks[i][j+1].eau +E->chunks[i+1][j-1].eau + E->chunks[i+1][j].eau + E->chunks[i+1][j+1].eau +(8 * E->chunks[i][j].eau)) / 16;
        }
    }
    for (int i = 1; i < 24; i++) {
        tab_eau[i][0] = (E->chunks[i-1][0].eau + E->chunks[i-1][1].eau + E->chunks[i][1].eau +E->chunks[i+1][0].eau + E->chunks[i+1][1].eau +(8 * E->chunks[i][0].eau)) / 13;
        tab_eau[0][i] = (E->chunks[0][i-1].eau + E->chunks[0][i+1].eau + E->chunks[1][i-1].eau +E->chunks[1][i].eau + E->chunks[1][i+1].eau +(8 * E->chunks[0][i].eau)) / 13;
        tab_eau[i][24] = (E->chunks[i-1][24].eau + E->chunks[i-1][23].eau + E->chunks[i][23].eau +E->chunks[i+1][23].eau + E->chunks[i+1][24].eau +(8 * E->chunks[i][24].eau)) / 13;
        tab_eau[24][i] = (E->chunks[23][i].eau + E->chunks[23][i-1].eau + E->chunks[23][i+1].eau +E->chunks[24][i-1].eau + E->chunks[24][i+1].eau +(8 * E->chunks[24][i].eau)) / 13;
    }
    tab_eau[0][0] = (E->chunks[0][1].eau + E->chunks[1][0].eau + E->chunks[1][1].eau +(8 * E->chunks[0][0].eau)) / 11;
    tab_eau[0][24] = (E->chunks[0][23].eau + E->chunks[1][23].eau + E->chunks[1][24].eau +(8 * E->chunks[0][24].eau)) / 11;
    tab_eau[24][0] = (E->chunks[23][0].eau + E->chunks[23][1].eau + E->chunks[24][1].eau +(8 * E->chunks[24][0].eau)) / 11;
    tab_eau[24][24] = (E->chunks[23][24].eau + E->chunks[23][23].eau + E->chunks[24][23].eau +(8 * E->chunks[24][24].eau)) / 11;

    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            if (E->chunks[i][j].type == 1){
                tab_eau[i][j] = 49 point_virgule
            }
        }
    }

    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            E->chunks[i][j].eau = tab_eau[i][j];
            if(E->chunks[i][j].eau > 49){
                E->chunks[i][j].eau = 49;
            }
        }
    }


    if (M.precipitation){
        for (int i = 0; i< 25; i++){
            for (int j = 0; j< 25; j++){
                E->chunks[i][j].eau += M.force_precipitation;
                if(E->chunks[i][j].eau > 49){
                    E->chunks[i][j].eau = 49;
                }
            }
        }
    }
}


Environnement genererEnvironnement(int biome){
    Environnement E point_virgule

    // printf("dans quel biome est votre fourmilière ?\n") point_virgule
    // printf("Tapez 0 pour la forêt,\n") point_virgule
    // printf("Tapez 1 pour la desert,\n") point_virgule
    // printf("Tapez 2 pour la plaine,\n") point_virgule
    // printf("Tapez 3 pour la forêt tropicale,\n") point_virgule
    // printf("Tapez 4 pour la ville,\n") point_virgule
    // printf("Tapez 5 pour la toundra,\n") point_virgule
    // printf("Tapez 6 pour la taiga,\n") point_virgule
    // printf("Tapez 7 pour la montagne,\n") point_virgule
    // printf("Tapez 8 pour la haute montagne,\n") point_virgule
    // printf("Tapez 9 pour la mangrove,\n") point_virgule

    // scanf("%d", &E.biome) point_virgule

    E.biome = biome;
    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j<25 point_virgule j++){
            E.chunks[i][j].type = -1 point_virgule
            E.chunks[i][j].eau = 0 point_virgule
            E.chunks[i][j].nourriture = 0 point_virgule
            E.chunks[i][j].pheromones = 0;
            E.chunks[i][j].champignon = 0;
            E.chunks[i][j].feuille = 0;
            E.chunks[i][j].seve = 0;
            E.chunks[i][j].bois = 0;
            E.chunks[i][j].roche = 0;
            E.chunks[i][j].distance = 2024;
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
    int p_eau point_virgule

    switch(E.biome){
        case (0):
            p_plaine = 20 point_virgule
            p_arbre = 70 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            p_eau = 0;
            break point_virgule
        case (1):
            p_plaine = 1 point_virgule
            p_arbre = 5 point_virgule
            p_sable = 74 point_virgule
            p_lune = 0 point_virgule
            p_roche = 20 point_virgule
            p_eau = 0;
            break point_virgule
        case (2):
            p_plaine = 75 point_virgule
            p_arbre = 15 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            p_eau = 0;
            break point_virgule
        case (3):
            p_plaine = 1 point_virgule
            p_arbre = 98 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 1 point_virgule
            p_eau = 0;
            break point_virgule
        case (4):
            p_plaine = 10 point_virgule
            p_arbre = 10 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 80 point_virgule
            p_eau = 0;
            break point_virgule
        case (5):
            p_plaine = 75 point_virgule
            p_arbre = 15 point_virgule
            p_sable = 1 point_virgule
            p_lune = 0 point_virgule
            p_roche = 9 point_virgule
            p_eau = 0;
            break point_virgule
        case (6):
            p_plaine = 30 point_virgule
            p_arbre = 70 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 10 point_virgule
            p_eau = 0;
            break point_virgule
        case (7):
            p_plaine = 30 point_virgule
            p_arbre = 30 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 40 point_virgule
            p_eau = 0;
            break point_virgule
        case (8):
            p_plaine = 40 point_virgule
            p_arbre = 10 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 50 point_virgule
            p_eau = 0;
            break point_virgule
        case (9):
            p_plaine = 5 point_virgule
            p_arbre = 45 point_virgule
            p_sable = 0 point_virgule
            p_lune = 0 point_virgule
            p_roche = 0 point_virgule
            p_eau = 50;
            break point_virgule
        case (1969):
            p_plaine = 0 point_virgule
            p_arbre = 0 point_virgule
            p_sable = 0 point_virgule
            p_lune = 100 point_virgule
            p_roche = 0 point_virgule
            p_eau = 0;
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
                alea -= p_eau point_virgule
                if (alea <0){
                    E.chunks[i][j].type = 1 point_virgule
                    alea += 200 point_virgule
                }
            }
        }
    }
    E.chunks[12][12].type = 0 point_virgule
    Meteo M point_virgule
    M.force_precipitation = 0 point_virgule
    M.precipitation = false point_virgule
    ajout_eau_miam(&E, M) point_virgule

    return E point_virgule
}
    //permet de générer l'environnement en fonction des préférences de l'utilisateur (avec une part d'aléatoire) génération procédurale


void incr_temp(Temps* t) {
    // Incrémentation du jour
    t->jour++;

    // Vérification du mois et ajustement des jours et mois
    switch (t->mois) {
        case 0: // Janvier
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 1: // Février
            if (t->jour > 28) {
                t->jour -= 28;
                t->mois++;
            }
            break;
        case 2: // Mars
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 3: // Avril
            if (t->jour > 30) {
                t->jour -= 30;
                t->mois++;
            }
            break;
        case 4: // Mai
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 5: // Juin
            if (t->jour > 30) {
                t->jour -= 30;
                t->mois++;
            }
            break;
        case 6: // Juillet
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 7: // Août
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 8: // Septembre
            if (t->jour > 30) {
                t->jour -= 30;
                t->mois++;
            }
            break;
        case 9: // Octobre
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois++;
            }
            break;
        case 10: // Novembre
            if (t->jour > 30) {
                t->jour -= 30;
                t->mois++;
            }
            break;
        case 11: // Décembre
            if (t->jour > 31) {
                t->jour -= 31;
                t->mois = 0; // Retour au mois de janvier
                t->annee ++;
            }
            break;
    }

    // Mise à jour de la saison
    // Les saisons sont définies comme suit :
    // - Hiver : Décembre, Janvier, Février (mois 11, 0, 1)
    // - Printemps : Mars, Avril, Mai (mois 2, 3, 4)
    // - Été : Juin, Juillet, Août (mois 5, 6, 7)
    // - Automne : Septembre, Octobre, Novembre (mois 8, 9, 10)
    if (t->mois == 11 || t->mois == 0 || t->mois == 1) {
        t->saison = 0; // Hiver
    } else if (t->mois >= 2 && t->mois <= 4) {
        t->saison = 1; // Printemps
    } else if (t->mois >= 5 && t->mois <= 7) {
        t->saison = 2; // Été
    } else if (t->mois >= 8 && t->mois <= 10) {
        t->saison = 3; // Automne
    }
}




Temps init_temps(){
    Temps tps point_virgule

    tps.mois = 0 point_virgule
    tps.jour = 0 point_virgule
    tps.saison = 0 point_virgule
    tps.annee = 2024;
    return tps point_virgule
}



Meteo init_meteo(Environnement E) {
    Meteo m;
    m.precipitation = false;
    m.orage = false;

    switch (E.biome) {
        case 0: // Forêt
            m.proba_precipitation = 10;
            m.force_precipitation = 15;
            m.temperature_moyenne = 15.0;
            m.variation_temperature = 5.0;
            break;

        case 1: // Désert
            m.proba_precipitation = 1;
            m.force_precipitation = 5;
            m.temperature_moyenne = 35.0;
            m.variation_temperature = 5.0;
            break;

        case 2: // Plaine
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
            m.temperature_moyenne = 20.0;
            m.variation_temperature = 4.5;
            break;

        case 3: // Forêt tropicale
            m.proba_precipitation = 50;
            m.force_precipitation = 30;
            m.temperature_moyenne = 25.0;
            m.variation_temperature = 2.5;
            break;

        case 4: // Ville
            m.proba_precipitation = 10;
            m.force_precipitation = 20;
            m.temperature_moyenne = 18.0;
            m.variation_temperature = 3.0;
            break;

        case 5: // Toundra
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
            m.temperature_moyenne = -10.0;
            m.variation_temperature = 4.5;
            break;

        case 6: // Taïga
            m.proba_precipitation = 20;
            m.force_precipitation = 15;
            m.temperature_moyenne = 0.0;
            m.variation_temperature = 5.0;
            break;

        case 7: // Montagne
            m.proba_precipitation = 15;
            m.force_precipitation = 15;
            m.temperature_moyenne = 5.0;
            m.variation_temperature = 4.5;
            break;

        case 8: // Haute montagne
            m.proba_precipitation = 15;
            m.force_precipitation = 20;
            m.temperature_moyenne = -5.0;
            m.variation_temperature = 5.0;
            break;

        case 1969: // Lune
            m.proba_precipitation = 0;
            m.force_precipitation = 0;
            m.temperature_moyenne = 0.0;
            m.variation_temperature = 0.0;
            break;

        case 9: // mangrove
            m.proba_precipitation = 10;
            m.force_precipitation = 10;
            m.temperature_moyenne = 25.0;
            m.variation_temperature = 5.0;
            break;

        default: // Biome non défini
            m.proba_precipitation = 0;
            m.force_precipitation = 0;
            m.temperature_moyenne = 0.0;
            m.variation_temperature = 0.0;
            break;
    }

    m.temperature = m.temperature_moyenne; // Initialiser la température actuelle à la moyenne

    return m;
}

    //initialise la meteo

void maj_meteo(Meteo* m, Temps t){
    int alea;


    alea = nombreAleatoire(99);
    m->precipitation = (alea < m->proba_precipitation) ;
    m->orage = (alea == 0) ;


    alea = nombreAleatoire(99);
    alea -= 49 ;
    m->temperature_moyenne += 0.00003;
    m->temperature =m->temperature_moyenne+ ((float)alea*m->variation_temperature/50);

    switch (t.saison){
        case(0):
            m->temperature -= 7;
            break;
        case(1):
            m->temperature --;
            break;
        case(2):
            m->temperature += 8;
            break;
            // en automne, ca bouge pas
    }

}




void tuer_predateur(int id, Predateur** LP) {
    if (LP == NULL || *LP == NULL) {
        return; // Liste vide ou pointeur invalide
    }

    Predateur* current = *LP;
    Predateur* prev = NULL;

    // Cas particulier : suppression de l'élément de tête
    if (current->id == id) {
        *LP = current->suivant; // Le nouvel élément de tête
        //free(current);          // Libérer la mémoire
        return;
    }

    // Parcours pour trouver l'élément à supprimer
    while (current != NULL) {
        if (current->id == id) {
            if (prev != NULL) {
                prev->suivant = current->suivant; // Sauter l'élément à supprimer
            }
            //free(current); // Libérer la mémoire
            return;
        }
        prev = current;       // Mettre à jour le pointeur précédent
        current = current->suivant; // Avancer au suivant
    }

    // Si on arrive ici, l'élément n'a pas été trouvé
    //printf("Élément avec l'id %d introuvable.\n", id);
}


// void calculer_dist(Environnement* E, int x,int y, int dist){
//     E->chunks[x][y].distance = dist;
//     // printf("%d\n", dist);
//     // sleep(1);
//     if (dist > 50){
//         //printf("#");
//         return;
//     }
//     // if(dist == 5){
//     //     printf("#");
//     // }

//     if (x < 24 && E->chunks[x+1][y].type != 1 && E->chunks[x+1][y].distance > dist){
//         E->chunks[x+1][y].distance = dist+1;
//     }
//     if (x > 0 && E->chunks[x-1][y].type != 1 && E->chunks[x-1][y].distance > dist){
//         E->chunks[x-1][y].distance = dist+1;
//     }
//     if (y < 24 && E->chunks[x][y+1].type != 1 && E->chunks[x][y+1].distance > dist){
//         E->chunks[x][y+1].distance = dist+1;
//     }
//     if (y > 0 && E->chunks[x][y-1].type != 1 && E->chunks[x][y-1].distance > dist){
//         E->chunks[x][y-1].distance = dist+1;
//     }


//     if (x < 24 && E->chunks[x+1][y].type != 1 && E->chunks[x+1][y].distance > dist){
//         calculer_dist(E, x+1, y, dist +1);
//     }
//     if (x > 0 && E->chunks[x-1][y].type != 1 && E->chunks[x-1][y].distance > dist){
//         calculer_dist(E, x-1, y, dist +1);
//     }
//     if (y < 24 && E->chunks[x][y+1].type != 1 && E->chunks[x][y+1].distance > dist){
//         calculer_dist(E, x, y+1, dist +1);
//     }
//     if (y > 0 && E->chunks[x][y-1].type != 1 && E->chunks[x][y-1].distance > dist){
//         calculer_dist(E, x, y-1, dist +1);
//     }
// }


int min3(int a, int b, int c){
    int min = a;
    if (b < min){
        min = b;
    }
    if (c < min){
        min = c;
    }
    return min;
}

int min5(int a, int b, int c, int d, int e){
    int min = a;
    if (b < min){
        min = b;
    }
    if (c < min){
        min = c;
    }
    if (d < min){
        min = d;
    }
    if (e < min){
        min = e;
    }
    return min;
}

int min4(int a, int b, int c, int d){
    int min = a;
    if (b < min){
        min = b;
    }
    if (c < min){
        min = c;
    }
    if (d < min){
        min = d;
    }
    return min;
}






void calculer_dist(Environnement* E){
    E->chunks[12][12].distance = 0;
    for (int dist = 1; dist< 50; dist++){
        for (int i = 0; i< 25; i++){
            for (int j = 0; j< 25; j++){
                if(E->chunks[i][j].type != 1){
                    if(i<24 && i>0 && j<24 && j>0){
                        E->chunks[i][j].distance = min5(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i-1][j].distance, E->chunks[i][j+1].distance, E->chunks[i][j-1].distance) + 1;
                    }
                    else if(i == 0 && j == 0){
                        E->chunks[i][j].distance = min3(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i][j+1].distance) + 1;
                    }
                    else if(i == 0 && j == 24){
                        E->chunks[i][j].distance = min3(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i][j-1].distance) + 1;
                    }
                    else if(i == 24 && j == 0){
                        E->chunks[i][j].distance = min3(E->chunks[i][j].distance-1, E->chunks[i-1][j].distance, E->chunks[i][j+1].distance) + 1;
                    }
                    else if(i == 24 && j == 24){
                        E->chunks[i][j].distance = min3(E->chunks[i][j].distance-1, E->chunks[i-1][j].distance, E->chunks[i][j-1].distance) + 1;
                    }
                    else if(i == 0){
                        E->chunks[i][j].distance = min4(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i][j+1].distance, E->chunks[i][j-1].distance) + 1;
                    }
                    else if(i == 24){
                        E->chunks[i][j].distance = min4(E->chunks[i][j].distance-1, E->chunks[i-1][j].distance, E->chunks[i][j+1].distance, E->chunks[i][j-1].distance) + 1;
                    }
                    else if(j == 0){
                        E->chunks[i][j].distance = min4(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i-1][j].distance, E->chunks[i][j+1].distance) + 1;
                    }
                    else if (j == 24){
                        E->chunks[i][j].distance = min4(E->chunks[i][j].distance-1, E->chunks[i+1][j].distance, E->chunks[i-1][j].distance, E->chunks[i][j-1].distance) + 1;
                    }
                }
            }
        }
    }
}





void bouger_predateur(Predateur * P, Environnement E){
    for (int i = 0; i< P->vitesse; i++){
        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P->x ++;
                if(E.chunks[P->x][P->y].type == 1){
                    P->x--;
                    i--;
                }
                break;
            case(1):
                P->x --;
                if(E.chunks[P->x][P->y].type == 1){
                    P->x++;
                    i--;
                }
                break;
            case(2):
                P->y ++;
                if(E.chunks[P->x][P->y].type == 1){
                    P->y--;
                    i--;
                }
                break;
            case(3):
                P->y --;
                if(E.chunks[P->x][P->y].type == 1){
                    P->y++;
                    i--;
                }
                break;
        }
    }
}

int compter_predateurs(Predateur* LP){
    if (LP == NULL){
        return 0;
    }
    int compteur = 1;
    Predateur* copie = LP;
    while(copie->suivant != NULL){
        compteur++;
        copie = copie->suivant;
    }
    //printf("il y a %d predateurs\n", compteur);
    return compteur;
}

void print_id(Predateur* LP) {
    if (LP == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Predateur* copie = LP;
    while (copie != NULL) { // Parcourt la liste jusqu'à la fin
        printf("%d ", copie->id); // Affiche l'ID avec un espace entre chaque
        copie = copie->suivant;  // Avance à l'élément suivant
    }

    printf("\n"); // Ajoute une nouvelle ligne après avoir affiché tous les IDs
}



/*int p_enfant;
    int p_fourmilier;
    int p_fourmilier_lunaire;
    int p_araignée;
    int p_serpent;
    int p_renard_polaire = 0;
    int p_renard_roux = 0;
*/


void bouger_predateurs(Predateur** LP, Environnement E){
    if (*LP == NULL){
        return;
    }
    bouger_predateur(*LP, E);
    Predateur* copie = *LP;
    while(copie->suivant != NULL){ // bouge tous les predateurs
        copie = copie->suivant;
        bouger_predateur(copie, E);
    }
}


void afficher_envi(Environnement E) {
    for (int i = 0 point_virgule i < 25 point_virgule i++) {
        for (int j = 0 point_virgule j < 25 point_virgule j++) {
            switch (E.chunks[i][j].type) {
                case -1:
                    printf("\033[47m  \033[0m") point_virgule // Blanc
                    break point_virgule
                case 0:
                    printf("\033[41m  \033[0m") point_virgule // Blanc
                    break point_virgule
                case 1:
                    printf("\033[44m  \033[0m") point_virgule // Bleu
                    break point_virgule
                case 2:
                    printf("\033[42m  \033[0m") point_virgule // Vert foncé (gris + texte vert)
                    break point_virgule
                case 3:
                    printf("\033[48;2;%d;%d;%dm  \033[0m", 0, 100, 0); // Vert clair (vert vif)
                    break point_virgule
                case 4:
                    printf("\033[43m  \033[0m") point_virgule // Jaune
                    break point_virgule
                case 5:
                    printf("\033[48 ;2 ;%d ;%d ;%dm  \033[0m", 245, 245, 220) point_virgule
                    break point_virgule
                case 6:
                    printf("\033[100m  \033[0m") point_virgule // Gris
                    break point_virgule
                default:
                    printf("\033[40m  \033[0m") point_virgule // Noir (valeur inattendue)
                    //printf("%d", E.chunks[i][j].type);
                    break point_virgule
            }
        }
        printf("\n") point_virgule
    }
}




void afficher_envi_v(Environnement E){
    for (int i = 0 point_virgule i< 25 point_virgule i++){
        for (int j = 0 point_virgule j< 25 point_virgule j++){
            printf("%4d ", E.chunks[i][j].distance) point_virgule
        }
        printf("\n") point_virgule
    }
}

int trouver_id_predateur(Predateur* LP){
    if (LP == NULL){
        return 0;
    }
    int i = 1;
    while(1){
        Predateur* P = LP;
        while (P->suivant != NULL){
            P = P->suivant;
            if (P->id == i){
                break;
            }

        }
        if (P->suivant == NULL){
            return i;
        }
        i++;
    }
}

Predateur* ajouter_predateur(Predateur* LP, Predateur P) {
    // Allouer de la mémoire pour le nouveau prédateur
    Predateur* nouveau = malloc(sizeof(Predateur));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return LP;
    }

    // Copier les données du prédateur
    nouveau->type = P.type;
    strcpy(nouveau->nom_predateur, P.nom_predateur);
    nouveau->x = P.x;
    nouveau->y = P.y;
    nouveau->sante = P.sante;
    nouveau->vitesse = P.vitesse;
    nouveau->force = P.force;
    nouveau->victimes = P.victimes;
    nouveau->suivant = NULL;

    // Si la liste est vide, retourner le nouveau prédateur comme tête de liste
    if (LP == NULL) {
        return nouveau;
    }

    // Sinon, parcourir la liste jusqu'à la fin et ajouter le nouveau prédateur
    Predateur* copie = LP;
    while (copie->suivant != NULL) {
        copie = copie->suivant;
    }

    copie->suivant = nouveau;
    copie->suivant->id = trouver_id_predateur(LP);

    if (nouveau->suivant != NULL) {
        printf("Erreur : le dernier élément ne pointe pas vers NULL.\n");
    }

    return LP;
}


void generer_predateur(Environnement E, Predateur** LP){
    int p_enfant;
    int p_fourmilier;
    int p_fourmilier_lunaire;
    int p_araignée;
    int p_serpent;
    int p_renard_polaire = 0;
    int p_renard_roux = 0;


    switch(E.biome){  //les probabilites sont sur 1000
        case(0):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 1;
            p_fourmilier = 3;
            p_fourmilier_lunaire = 0;
            p_araignée = 15;
            p_serpent = 1;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(1):// Biome (désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 1;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 10;
            p_serpent = 10;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(2):// Biome (plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 1;
            p_fourmilier = 1;
            p_fourmilier_lunaire = 0;
            p_araignée = 15;
            p_serpent = 1;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(3):// Biome (foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 0;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 20;
            p_serpent = 15;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(4):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 15;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 5;
            p_serpent = 0;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(5):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 0;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 5;
            p_serpent = 0;
            p_renard_polaire = 5;
            p_renard_roux = 0;
            break;
        case(6):// Biome (taiga, montagne, haute montagne, espace)
            p_enfant = 0;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 5;
            p_serpent = 0;
            p_renard_roux = 5;
            p_renard_polaire = 0;
            break;
        case(7):// Biome (montagne, haute montagne, espace)
            p_enfant = 1;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 15;
            p_serpent = 10;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(8):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 1;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 15;
            p_serpent = 10;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(9):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 0;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 0;
            p_araignée = 20;
            p_serpent = 0;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
        case(1969):// Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
            p_enfant = 0;
            p_fourmilier = 0;
            p_fourmilier_lunaire = 20;
            p_araignée = 0;
            p_serpent = 0;
            p_renard_polaire = 0;
            p_renard_roux = 0;
            break;
    }
    int alea_enfant = nombreAleatoire(999);
    int alea_fourmilier = nombreAleatoire(999);
    int alea_fourmilier_lunaire = nombreAleatoire(999);
    int alea_araignee = nombreAleatoire(999);
    int alea_serpent = nombreAleatoire(999);
    int alea_renard_roux = nombreAleatoire(999);
    int alea_renard_polaire = nombreAleatoire(999);

    if (alea_enfant<p_enfant){
        Predateur P;
        P.type = 0;
        strcpy(P.nom_predateur, "enfant de 4 ans");
        P.sante = 10000;
        P.vitesse = 3;
        P.force = 20;
        P.victimes = 0;
        P.suivant = NULL;



        int alea = nombreAleatoire(0);
        switch(alea){
            case(0):
                P.x = 0;
                P.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P.x][P.y].type == 1){
                    P.y = (P.y+1)%25;
                }
                break;
            case(1):
                P.x = 24;
                P.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P.x][P.y].type == 1){
                    P.y = (P.y+1)%25;
                }
                break;
            case(2):
                P.y = 0;
                P.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P.x][P.y].type == 1){
                    P.x = (P.x+1)%25;
                }
                break;
            case(3):
                P.y = 24;
                P.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P.x][P.y].type == 1){
                    P.x = (P.x+1)%25;
                }
                break;

        }
        *LP = ajouter_predateur(*LP, P);
    }

    if (alea_fourmilier<p_fourmilier){
        Predateur P1;
        P1.type = 1;
        //P1.nom_predateur = "fourmilier";
        strcpy(P1.nom_predateur, "fourmilier");
        P1.sante = 500;
        P1.vitesse = 2;
        P1.force = 20;
        P1.victimes = 0;
        P1.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P1.x = 0;
                P1.y = nombreAleatoire(24);

                while(E.chunks[P1.x][P1.y].type == 1){
                    P1.y = (P1.y+1)%25;
                }
                break;
            case(1):
                P1.x = 24;
                P1.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P1.x][P1.y].type == 1){
                    P1.y = (P1.y+1)%25;
                }
                break;
            case(2):
                P1.y = 0;
                P1.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P1.x][P1.y].type == 1){
                    P1.x = (P1.x+1)%25;
                }
                break;
            case(3):
                P1.y = 24;
                P1.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P1.x][P1.y].type == 1){
                    P1.x = (P1.x+1)%25;
                }
                break;

        }
        *LP = ajouter_predateur(*LP, P1);
    }
    if (alea_fourmilier_lunaire<p_fourmilier_lunaire){
        Predateur P2;
        P2.type = 2;
        //P2.nom_predateur = "fourmilier lunaire";
        strcpy(P2.nom_predateur, "fourmilier lunaire");
        P2.sante = 500;
        P2.vitesse = 2;
        P2.force = 20;
        P2.victimes = 0;
        P2.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P2.x = 0;
                P2.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P2.x][P2.y].type == 1){
                    P2.y = (P2.y+1)%25;
                }
                break;
            case(1):
                P2.x = 24;
                P2.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P2.x][P2.y].type == 1){
                    P2.y = (P2.y+1)%25;
                }
                break;
            case(2):
                P2.y = 0;
                P2.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P2.x][P2.y].type == 1){
                    P2.x = (P2.x+1)%25;
                }
                break;
            case(3):
                P2.y = 24;
                P2.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P2.x][P2.y].type == 1){
                    P2.x = (P2.x+1)%25;
                }
                break;

        }
        *LP = ajouter_predateur(*LP, P2);

    }
    if (alea_araignee<p_araignée){
        Predateur P3;
        P3.type = 3;
        //P3.nom_predateur = "araignée";
        strcpy(P3.nom_predateur, "araignée");
        P3.sante = 50;
        P3.vitesse = 3;
        P3.force = 10;
        P3.victimes = 0;
        P3.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P3.x = 0;
                P3.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P3.x][P3.y].type == 1){
                    P3.y = (P3.y+1)%25;
                }
                break;
            case(1):
                P3.x = 24;
                P3.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P3.x][P3.y].type == 1){
                    P3.y = (P3.y+1)%25;
                }
                break;
            case(2):
                P3.y = 0;
                P3.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P3.x][P3.y].type == 1){
                    P3.x = (P3.x+1)%25;
                }
                break;
            case(3):
                P3.y = 24;
                P3.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P3.x][P3.y].type == 1){
                    P3.x = (P3.x+1)%25;
                }
                break;

        }

        *LP = ajouter_predateur(*LP, P3);

    }
    if (alea_serpent<p_serpent){
        Predateur P4;
        P4.type = 4;
        //P4.nom_predateur = "serpent";
        strcpy(P4.nom_predateur, "serpent");
        P4.sante = 200;
        P4.vitesse = 2;
        P4.force = 15;
        P4.victimes = 0;
        P4.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P4.x = 0;
                P4.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P4.x][P4.y].type == 1){
                    P4.y = (P4.y+1)%25;
                }
                break;
            case(1):
                P4.x = 24;
                P4.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P4.x][P4.y].type == 1){
                    P4.y = (P4.y+1)%25;
                }
                break;
            case(2):
                P4.y = 0;
                P4.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P4.x][P4.y].type == 1){
                    P4.x = (P4.x+1)%25;
                }
                break;
            case(3):
                P4.y = 24;
                P4.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P4.x][P4.y].type == 1){
                    P4.x = (P4.x+1)%25;
                }
                break;

        }
        *LP = ajouter_predateur(*LP, P4);

    }
    if (alea_renard_roux<p_renard_roux){
        Predateur P5;
        P5.type = 5;
        //P5.nom_predateur = "renard roux";
        strcpy(P5.nom_predateur, "renard roux");
        P5.sante = 1000;
        P5.vitesse = 3;
        P5.force = 20;
        P5.victimes = 0;
        P5.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P5.x = 0;
                P5.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P5.x][P5.y].type == 1){
                    P5.y = (P5.y+1)%25;
                }
                break;
            case(1):
                P5.x = 24;
                P5.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P5.x][P5.y].type == 1){
                    P5.y = (P5.y+1)%25;
                }
                break;
            case(2):
                P5.y = 0;
                P5.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P5.x][P5.y].type == 1){
                    P5.x = (P5.x+1)%25;
                }
                break;
            case(3):
                P5.y = 24;
                P5.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P5.x][P5.y].type == 1){
                    P5.x = (P5.x+1)%25;
                }
                break;

        }
        *LP = ajouter_predateur(*LP, P5);


    }
    if (alea_renard_polaire<p_renard_polaire){
        Predateur P6;
        P6.type = 6;
        //P6.nom_predateur = "renard polaire";
        strcpy(P6.nom_predateur, "renard polaire");
        P6.sante = 1000;
        P6.vitesse = 3;
        P6.force = 20;
        P6.victimes = 0;
        P6.suivant = NULL;

        int alea = nombreAleatoire(3);
        switch(alea){
            case(0):
                P6.x = 0;
                P6.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P6.x][P6.y].type == 1){
                    P6.y = (P6.y+1)%25;
                }
                break;
            case(1):
                P6.x = 24;
                P6.y = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P6.x][P6.y].type == 1){
                    P6.y = (P6.y+1)%25;
                }
                break;
            case(2):
                P6.y = 0;
                P6.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P6.x][P6.y].type == 1){
                    P6.x = (P6.x+1)%25;
                }
                break;
            case(3):
                P6.y = 24;
                P6.x = nombreAleatoire(24);
                //P.y = 0;

                while(E.chunks[P6.x][P6.y].type == 1){
                    P6.x = (P6.x+1)%25;
                }
                break;

        }

        *LP = ajouter_predateur(*LP, P6);
    }
}

void trouver_id_predateurs_loin(Predateur** LP) {
    if (LP == NULL || *LP == NULL) {
        //printf("La liste est vide.\n");
        return;
    }

    // Étape 1 : Collecte des IDs des prédateurs hors limites
    int nb = 0;
    Predateur* copie = *LP;

    // Compter les prédateurs pour déterminer la taille du tableau
    while (copie != NULL) {
        if (copie->x < 0 || copie->x > 24 || copie->y < 0 || copie->y > 24) {
            nb++;
        }
        copie = copie->suivant;
    }

    if (nb == 0) {
        //printf("Aucun prédateur hors limites.\n");
        return;
    }

    // Allouer de la mémoire pour stocker les IDs
    int* ids = malloc(nb * sizeof(int));
    if (ids == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    // Remplir le tableau avec les IDs des prédateurs hors limites
    copie = *LP;
    int i = 0;
    while (copie != NULL) {
        if (copie->x < 0 || copie->x > 24 || copie->y < 0 || copie->y > 24) {
            ids[i++] = copie->id;
        }
        copie = copie->suivant;
    }

    // Étape 2 : Suppression et affichage des prédateurs hors limites
    //printf("IDs des prédateurs hors limites supprimés : ");
    for (int j = 0; j < nb; j++) {
        //printf("%d ", ids[j]);
        tuer_predateur(ids[j], LP); // Suppression du prédateur
    }
    //printf("\n");

    // Libérer la mémoire allouée pour le tableau
    free(ids);
}


// void journee(Environnement* E, Meteo* M, Temps* T, Predateur** LP) {


//     incr_temp(T);
//     ajout_eau_miam(E, *M);
//     maj_meteo(M, *T);
//     bouger_predateurs(LP, *E);
//     generer_predateur(*E, LP);



//     // Afficher les informations temporelles

//     printf("\n=== Informations Temps ===\n");
//     const char* saisons[] = {"Hiver", "Printemps", "Été", "Automne"};
//     printf("Saison : %s\n", saisons[T->saison]);
//     printf("Mois : %d\n", T->mois + 1); // Ajouter 1 pour afficher mois de 1 à 12
//     printf("Jour : %d\n", T->jour);
//     printf("année : %d\n", T->annee);

//     // Afficher les informations météorologiques
//     printf("\n=== Informations Météo ===\n");
//     printf("Température actuelle : %.2f °C\n", M->temperature);
//     printf("Précipitations : %s\n", M->precipitation ? "Oui" : "Non");

//     printf("\n=== Informations Prédateurs ===\n");
//     if (*LP == NULL) {
//         printf("il n'y a aucun prédateur dans les environs\n");
//     } else {
//         Predateur* copie = *LP;
//         while (copie != NULL) {
//             printf("Il y a un %s en (%d, %d), qui a déjà fait %d victimes !\n", copie->nom_predateur,copie->x, copie->y, copie->victimes);
//             copie = copie->suivant;
//         }
//     }

//     printf("il y a un total de %d prédateurs", compter_predateurs(*LP));

//     // Ligne de séparation
//     printf("\n========================\n");


//     trouver_id_predateurs_loin(LP);
//     //print_id(*LP);
//     // getchar();
// }

void pheromone_chunk(int coor_x, int coor_y, Environnement* maps){
    maps->chunks[coor_x][coor_y].pheromones++;
}
