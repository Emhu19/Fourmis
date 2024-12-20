#include <stdio.h>
#include <stdlib.h>
#include "fourmiliere.h"
#include "fourmi.h"
#include "reine.h"
#include "animation.h"
#include "environnement.h"
#include "larve.h"

#define JOUR_SIMULATION 6
#define BASE_COOR_X 12
#define BASE_COOR_Y 12

// Liste des types de fourmilles
/* 1 Fourmi coupeuse de feuilles : Atta
        1 Reine fondatrice de champignon
        2 Ouvrière transporteur de feuilles
        3 Soldat protecteur des colonnes
        4 Ouvrière nettoyeuse des champignons
        5 Ouvrière mineure pour le jardinage de champignons
*/
/* 2 Fourmis des dunes : Cataglyphis
    Exploratrice de chaleur extrême
    Messagère rapide
    Chercheuse d’ombre
    Ouvrière éclaireuse
    Reine migratrice
    Fourmi stérile pour fouille des sables
*/
// 3 Fourmis des rochers : Messor
// 4 Fourmis amazoniennes : Eciton
// 5 Fourmis forestières : Formica
    // Ouvrière constructrice de nids en bois ou aiguilles
        // Exploratrice forestière
        // Soldat défensif avec acide formique
        // Transporteur de petits insectes
        //Reine des sous-bois
        // Collectrice de miellat des pucerons
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis



ListFourmi* cycle_jour(int niveau, ListFourmi* liste, Reine* reine, Environnement* map, Temps* T, Meteo* M, ListLarve* liste_larve){
    if (liste == NULL)
        return NULL;

    int ponte = 0;
    if(T->saison == 1 || T->saison == 2){
        if (reine->age < 730) {
            ponte = rand() % 100 + reine->capacite_ponte;
        } else {
            ponte = rand() % 50 + reine->capacite_ponte;
        }
        if(T->saison == 2){ //SAISON ETE
            if(reine->royale == true){
                int i = 2000;
                for(int j = 0; j < 10; j++){
                    Fourmi* fourmi_male = creationFourmi(i, reine->type, false);
                    liste = ajout_fourmi(&liste, fourmi_male);
                }

            }
            else{
                // srand(time(NULL));
                int random_number = rand() % 100;
                if(random_number == 19){
                    reine->royale = true;
                }
            }
            if(M->precipitation && reine->royale){ //pdt l'orage c'est le vol nuptial
                reine->royale = false;
                Fourmi* fourmi_male_supp = trouver_fourmi(liste, 2000);
                if (fourmi_male_supp != NULL) {
                    retirer_fourmi(&liste, fourmi_male_supp);
                }
                //envol nultiale
            }
        }
        int nbNymphe = 0;
        for (int i = 1; i <= ponte; i++) {
            Stade* stade = creationLarve(i, reine->type, true);
            if (stade != NULL) {
                update_day_larve(liste_larve, stade);
                if (stade->age > 25) {
                    nbNymphe++;
                }
            }
        }
        for (int b = 0; b < nbNymphe; b++) {
            Fourmi* fourmi1 = creationFourmi(b, reine->type, true);
            if (fourmi1 != NULL) {
                liste = ajout_fourmi(&liste, fourmi1);
            }
        }
        nbNymphe = 0;
    }
     update_day_Reine(reine);
     update_day_liste_fourmi(liste, map);
     // afficher_fourmiliere(3, liste, reine);
     return liste;
}

void simulation(){
    ListFourmi* liste = Initialisation_List();
    ListLarve* liste_larve = Initialisation_List_Larve();
    Reine* reine = creationReine(1, 1);
//     getchar();
//     afficher_Reine(reine);
//     getchar();
//     if (reine != NULL) {
//          afficher_Reine(reine);
//     }
    srand(time(NULL)) ;

    Environnement E = genererEnvironnement() ;
    afficher_envi(E) ;
    Meteo M = init_meteo(E);
    Temps T = init_temps();
    Predateur* LP = NULL;
    int b = 0;
    while(b < 5){
         liste = cycle_jour(5, liste, reine, &E, &T, &M, liste_larve);
         journee(&E, &M, &T, &LP);
         b++;
//         sleep(5);
    }
    afficher_Reine(reine);
    getchar();
    afficher_Liste_fourmi(liste);
    getchar();
    liberer_liste(liste);
    free(reine);
}

int main() {
    srand(time(NULL)) ;
    // logo_1();
    simulation();
    int biome = logo_3();
    Environnement E = genererEnvironnement(biome) ;
    afficher_envi(E) ;
    int type = logo_2();

    afficher_envi(E) ;
    sleep(2);

    Meteo M = init_meteo(E);
    Temps T = init_temps();
    Predateur* LP = NULL;

    while(true){
        printf("\033[H\033[J");
        //afficher_envi(E) ;
        journee(&E, &M, &T, &LP);
        //sleep(1);
    }
    return 0;
}
