#include "fourmiliere.h"
#include <stdio.h>
#include <unistd.h>





ArbrePiece *init(Piece e){
    ArbrePiece *result;
    result = malloc(sizeof(ArbrePiece));
    result->salle = e;
    result->filsD = NULL;
    result->filsG = NULL;
    result->taille = 1;
    result->profondeur = 0;
    return result;
}

int puiss2(int n){
    int result = 1;
    for(int i = 0; i<n; i++){
        result *= 2;
    }
    return result;
}

ArbrePiece *ajoutePiece(ArbrePiece *T, Piece R){
    // permet d'ajouter une salle
    // printf("id : %d\n", R.id);
    if(T == NULL){
        T = init(R);
        return T;
    }
    if(T->filsG == NULL){
        T->taille++;
        T->profondeur++;
        T->filsG = ajoutePiece(T->filsG, R);
        return T;
    }
    if(T->filsD == NULL){
        T->taille++;
        T->filsD = ajoutePiece(T->filsD, R);
        return T;
    }
    int testFD = puiss2(T->filsD->profondeur);
    int testFG = puiss2(T->filsG->profondeur);
    if(testFD >= 2){
        testFD--;
    }
    if(testFG >= 2){
        testFG--;
    }
    // printf("%d %d\n", T->filsG->taille, testFG);
    if(T->filsG->taille == testFG){
        T->taille++;
        if(T->filsD->taille <= T->filsG->taille){
            T->filsD = ajoutePiece(T->filsD, R);
            return T;
        }
        else{
            T->profondeur++;
            T->filsG = ajoutePiece(T->filsG, R);
            return T;
        }
    }
    else{
        T->taille++;
        if(T->filsG->taille <= T->filsD->taille){
            T->filsG = ajoutePiece(T->filsG, R);
            return T;
        }
        else{
            T->profondeur++;
            T->filsD = ajoutePiece(T->filsD, R);
            return T;
        }
    }
}

void afficheArbre(ArbrePiece *T){
    if(T->filsG != NULL){
        afficheArbre(T->filsG);
    }
    if(T != NULL){
        if(T->salle.etat == 1){
            printf("%d ", T->salle.id);
        }
    }
    if(T->filsD != NULL){
        afficheArbre(T->filsD);
    }
}

void detruitPiece(ArbrePiece *T){
// permet de détruire une salle renvoie les matériaux que la destrucion donne
    if(T != NULL){
        if(T->salle.etat != 0 && T->salle.id != 1){
            T->salle.vie -= 5000;
            if(T->salle.vie < 0){
                printf("la salle est détruite frérot c'est dommage\n");
                T->salle.etat = 0;
                T->salle.ressourceNecessaire->quantiteMax -= 50000;
                if(T->salle.ressourceNecessaire->quantiteRessource > T->salle.ressourceNecessaire->quantiteMax){
                    T->salle.ressourceNecessaire->quantiteRessource -= T->salle.ressourceNecessaire->quantiteMax - T->salle.ressourceNecessaire->quantiteRessource;
                }
            }
        }
        detruitPiece(T->filsD);
        detruitPiece(T->filsG);
    }
}

Maladie genereMaladie();
// permet de generer des maladie au sein de la fourmilière de manière aléatoire

// void effetMaladie(Fourmis *A, Maladie *S);
//donne a la fourmi infecté les effet de la maladie qui l'infecte peut être faire une fonction par maladie?

// void soigneMaladie();
//permet de soigner les maladie

// void stock(Fourmis *A, Piece *T);
// permet a une fourmi de stocker les materiaux qu'elle a récupere si la salle le permet

void clear_terminal() {
    printf("\033[H\033[J");
}

void afficher_titre(const char *titre) {
    printf("\n\033[1;34m===== %s =====\033[0m\n\n", titre);
}

void afficher_salle_simple(const char *nom) {
    printf("+-----------------+\n");
    printf("|                 |\n");
    printf("|     %-10s  |\n", nom);
    printf("|                 |\n");
    printf("+-----------------+\n");
}

void afficher_salle_simple_milieu(const char *nom) {
    printf("                            +-----------------+\n");
    printf("                            |                 |\n");
    printf("                            |     %-10s  |\n", nom);
    printf("                            |                 |\n");
    printf("                            +-----------------+\n");
}

void afficher_connexion_simple() {
    printf("        |\n");
}

void afficher_connexion_simple_milieu() {
    printf("                                  |\n");
}

void afficher_connexion_double() {
    printf("        |                            |\n");
}

void afficher_salles_alignees(const char *nom1, const char *nom2) {
    printf("+-----------------+         +-----------------+\n");
    printf("|                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |\n", nom1, nom2);
    printf("|                 |         |                 |\n");
    printf("+-----------------+         +-----------------+\n");
}

void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3) {
    printf("+-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3);
    printf("|                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+\n");
}

void afficher_fourmiliere_niveau(int niveau) {
    switch (niveau) {
        case 1:
            afficher_salles_alignees("R", "N");
            break;
        case 2:
            afficher_salles_alignees("R", "N");
            afficher_connexion_simple();
            afficher_salle_simple("L");
            break;
        case 3:
            afficher_salles_alignees("R", "N");
            afficher_connexion_double();
            afficher_salles_alignees("L", "R");
            break;
        case 4:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees("L", "R");
            break;
        case 5:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees_3("L", "R", "R");
            break;
        case 6:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees_3("L", "R", "R");
            afficher_connexion_simple_milieu();
            afficher_salle_simple_milieu("L");
            break;
        default:
            printf("Niveau %d non pris en charge.\n", niveau);
            break;
    }
}

int salle_reine(Reine* reine){
    if(reine->salle == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void afficher_legende(ListFourmi* liste, Reine* reine) {
    printf("\n\033[1;33mLégende :\033[0m\n");
    printf("Reine : Salle de la reine (%d/1)\n", salle_reine(reine));
    printf("Nourriture : Stockage de nourriture(0/120)\n");
    printf("Larves : Salle des larves(%d/125)\n", compter_fourmi_salle(liste, 2));
    printf("Ressources : Stockage de ressources(0/100)\n");
    printf("Exterieur : (%d)\n", compter_fourmi_salle(liste, 0));
}

void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine) {
    clear_terminal();
    afficher_titre("Fourmilière");
    afficher_fourmiliere_niveau(niveau);
    afficher_legende(liste, reine);
    compter_Liste_fourmi(liste);
//     printf("\n\033[1;32mAppuyez sur Entrée pour continuer...\033[0m\n");
    usleep(500000);
//     getchar();
}



// ArbrePiece *init(Piece e){
//     ArbrePiece *result;
//     result = malloc(sizeof(ArbrePiece));
//     result->salle = e;
//     result->filsD = NULL;
//     result->filsG = NULL;
//     result->taille = 1;
//     result->profondeur = 0;
//     return result;
// }




// ArbrePiece *ajoutePiece(ArbrePiece *T, Piece R){
//     // permet d'ajouter une salle
//     // printf("id : %d\n", R.id);
//     if(T == NULL){
//         T = init(R);
//         return T;
//     }
//     if(T->filsG == NULL){
//         T->taille++;
//         T->profondeur++;
//         T->filsG = ajoutePiece(T->filsG, R);
//         return T;
//     }
//     if(T->filsD == NULL){
//         T->taille++;
//         T->filsD = ajoutePiece(T->filsD, R);
//         return T;
//     }
//     int testFD = puiss2(T->filsD->profondeur);
//     int testFG = puiss2(T->filsG->profondeur);
//     if(testFD >= 2){
//         testFD--;
//     }
//     if(testFG >= 2){
//         testFG--;
//     }
//     // printf("%d %d\n", T->filsG->taille, testFG);
//     if(T->filsG->taille == testFG){
//         T->taille++;
//         if(T->filsD->taille <= T->filsG->taille){
//             T->filsD = ajoutePiece(T->filsD, R);
//             return T;
//         }
//         else{
//             T->profondeur++;
//             T->filsG = ajoutePiece(T->filsG, R);
//             return T;
//         }
//     }
//     else{
//         T->taille++;
//         if(T->filsG->taille <= T->filsD->taille){
//             T->filsG = ajoutePiece(T->filsG, R);
//             return T;
//         }
//         else{
//             T->profondeur++;
//             T->filsD = ajoutePiece(T->filsD, R);
//             return T;
//         }
//     }
// }

// void afficheArbre(ArbrePiece *T){
//     if(T->filsG != NULL){
//         afficheArbre(T->filsG);
//     }
//     if(T != NULL){
//         printf("%d\n", T->salle.id);
//     }
//     if(T->filsD != NULL){
//         afficheArbre(T->filsD);
//     }
// }

// Resource *detruitPiece(ArbrePiece *T, Piece *R);
// // permet de détruire une salle renvoie les matériaux que la destrucion donne

// Maladie genereMaladie();
