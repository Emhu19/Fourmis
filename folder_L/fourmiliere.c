// #include "fourmiliere.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct ListFourmi ListFourmi;
typedef struct ListReine ListReine;
typedef struct ArbrePiece ArbrePiece;
typedef struct ListRessource ListRessource;

struct ListFourmi{
    // Fourmis *fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
    ListFourmi *suivant;
    ListFourmi *precedent; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente 
};

struct ListReine{
    // Reine *reine;
    ListReine *suivant;
    ListReine *precedent; //même raison que pour ListFourmi
};

typedef struct{
    char *typeRessource;
    int id;
    int quantiteRessource;
    int quantiteMax;
}Resource;

// struct ListRessource{
    // Resource *resource;
    // ListRessource *suivant;
    // ListRessource *precedent;
// };

typedef struct{
    ListFourmi *fourmi; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de fourmis
    ListReine *reine; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de reine (il est possible qu'il y ait plusieur reine dans la fourmilière)
    ArbrePiece *piece; //plus simple a parcourir pour savoir quelle salle mêne a ou
}Fourmilière;

typedef struct{
    int taille;
    int id;
    char *typePiece;
    int capaciteMax;
    Resource *ressourceNecessaire;
    int quantiteRessourceNecessaire;
    int vie;
    int etat;
}Piece;

struct ArbrePiece{
    Piece salle;
    int taille;
    int profondeur;
    ArbrePiece *filsG;
    ArbrePiece *filsD;
};

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

typedef struct{
    char *typeMaladie;
    int id;
}Maladie;

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
    if(T->salle.id == R.id && T->salle.etat == 0){
        T->salle.etat = 1;
        T->salle.vie = R.vie;
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

void detruitPiece(ArbrePiece *T, int *niveau){
// permet de détruire une salle renvoie les matériaux que la destrucion donne
    if(T != NULL){
        if(T->salle.etat != 0 && T->salle.id != 1){
            T->salle.vie -= 50;
            if(T->salle.vie < 0){
                printf("la salle %s est détruite c'est dommage\n", T->salle.typePiece);
                T->salle.etat = 0;
                T->salle.ressourceNecessaire->quantiteMax -= 50;
                if(T->salle.ressourceNecessaire->quantiteRessource > T->salle.ressourceNecessaire->quantiteMax){
                    T->salle.ressourceNecessaire->quantiteRessource -= T->salle.ressourceNecessaire->quantiteMax - T->salle.ressourceNecessaire->quantiteRessource;
                }
            }
        }
        detruitPiece(T->filsD, niveau);
        detruitPiece(T->filsG, niveau);
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

void afficher_connexion_triple() {
    printf("        |                            |                            |\n");
}
void afficher_connexion_simple_fin() {
    printf("                                                                  |\n");
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

void affiche_auto(int niveau, ArbrePiece *piece){
    if(piece != NULL){
        if(piece->taille == 1){
            if(piece->salle.etat != 0){
                afficher_salle_simple(piece->salle.typePiece);
                afficher_connexion_simple();
            }
        }
        else if(piece->taille== 2){
            if(piece->filsD != NULL){
                if(piece->salle.etat != 0){
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsD->salle.typePiece);
                    afficher_connexion_double();
                }
                else if(piece->filsD->salle.etat != 0){
                    afficher_salle_simple(piece->filsD->salle.typePiece);
                    afficher_connexion_simple();
                }
            }
            else if(piece->filsG != NULL){
                if(piece->salle.etat != 0){
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsG->salle.typePiece);
                    afficher_connexion_double();
                }
                else if(piece->filsG->salle.etat != 0){
                    afficher_salle_simple(piece->filsG->salle.typePiece);
                    afficher_connexion_simple();
                }
            }
        }
        else if(piece->taille == 3){
            if(piece->salle.etat != 0){
                afficher_salles_alignees_3(piece->salle.typePiece, piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);
                afficher_connexion_triple();
            }
            else if(piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_salle_simple(piece->filsG->salle.typePiece);
                afficher_connexion_simple();
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat == 0){
                afficher_salle_simple(piece->filsD->salle.typePiece);
                afficher_connexion_simple();
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat != 0){
                afficher_salles_alignees(piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);
                afficher_connexion_double();
            }
        }
        else{
            if(piece->salle.etat != 0 && piece->filsG->salle.etat != 0 && piece->filsD->salle.etat != 0){
                afficher_salles_alignees_3(piece->salle.typePiece, piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);
                afficher_connexion_triple();
            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_salles_alignees(piece->salle.typePiece, piece->filsG->salle.typePiece);
                afficher_connexion_double();
            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat == 0 && piece->filsD->salle.etat != 0){
                afficher_salles_alignees(piece->salle.typePiece, piece->filsD->salle.typePiece);
                afficher_connexion_double();
            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat == 0 && piece->filsD->salle.etat == 0){
                afficher_salle_simple(piece->salle.typePiece);
                afficher_connexion_simple();
            }
            else if(piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_salle_simple(piece->filsG->salle.typePiece);
                afficher_connexion_simple();
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat == 0){
                afficher_salle_simple(piece->filsD->salle.typePiece);
                afficher_connexion_simple();
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat != 0){
                afficher_salles_alignees(piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);
                afficher_connexion_double();
            }
            affiche_auto(niveau/3, piece->filsG->filsG);
            affiche_auto(niveau/3, piece->filsG->filsD);
            affiche_auto(niveau/3, piece->filsD->filsD);
            affiche_auto(niveau/3, piece->filsD->filsG);
        }
    }
}

// int salle_reine(Reine* reine){
    // if(reine->salle == 1){
        // return 1;
    // }
    // else{
        // return 0;
    // }
// }

// void afficher_legende(ListFourmi* liste, Reine* reine) {
    // printf("\n\033[1;33mLégende :\033[0m\n");
    // printf("Reine : Salle de la reine (%d/1)\n", salle_reine(reine));
    // printf("Nourriture : Stockage de nourriture(0/120)\n");
    // printf("Larves : Salle des larves(%d/125)\n", compter_fourmi_salle(liste, 2));
    // printf("Ressources : Stockage de ressources(0/100)\n");
    // printf("Exterieur : (%d)\n", compter_fourmi_salle(liste, 0));
// }

void afficher_fourmiliere(int niveau/*, ListFourmi* liste, Reine* reine */) {
    clear_terminal();
    afficher_titre("Fourmilière");
    afficher_fourmiliere_niveau(niveau);
    // afficher_legende(liste, reine);
    // compter_Liste_fourmi(liste);
//     printf("\n\033[1;32mAppuyez sur Entrée pour continuer...\033[0m\n");
    usleep(500000);
//     getchar();
}


int main(){
    ArbrePiece *T;
    // ListFourmi *YaR;
    // Reine *ToujourR;
    int niveau;
    niveau = 0;
    Piece A;
    Resource *metal;
    metal = malloc(sizeof(Resource *));
    metal->quantiteRessource = 0;
    metal->id = 1;
    metal->typeRessource = "bois";
    metal->quantiteMax = 10;
    Resource *bois;
    bois = malloc(sizeof(Resource *));
    bois->quantiteRessource = 0;
    bois->id = 1;
    bois->typeRessource = "bois";
    bois->quantiteMax = 10;
    Piece stockBois;
    stockBois.id = 2;
    stockBois.quantiteRessourceNecessaire = 10;
    stockBois.ressourceNecessaire = bois;
    stockBois.vie = 500;
    stockBois.etat = 1;
    stockBois.typePiece = "stockBois";
    Piece stockMetal;
    stockMetal.id = 3;
    stockMetal.quantiteRessourceNecessaire = 25;
    stockMetal.ressourceNecessaire = metal;
    stockMetal.vie = 500;
    stockMetal.etat = 1;
    stockMetal.typePiece = "stockMetal";
    A.id = 1;
    A.capaciteMax = 10;
    A.quantiteRessourceNecessaire = 10;
    A.ressourceNecessaire = metal;
    A.taille = 10;
    A.typePiece = "principale";
    A.etat = 1;
    T = init(A);
    niveau++;
    while(1){
       printf("\n\nnouveau jour !\n\n"); 
       detruitPiece(T, &niveau);
       if(metal->quantiteRessource < metal->quantiteMax){
           metal->quantiteRessource++;
       }
       if(bois->quantiteRessource < bois->quantiteMax){
           bois->quantiteRessource += 2;
       }
       if(metal->quantiteRessource >= metal->quantiteMax){
           metal->quantiteMax += 50;
           metal->quantiteRessource -= stockMetal.quantiteRessourceNecessaire;
           printf("\n\nnouveau stockMetal !\n\n"); 
           ajoutePiece(T, stockMetal);
           niveau ++;
       }
       if(bois->quantiteRessource >= bois->quantiteMax){
           bois->quantiteMax += 50;
           bois->quantiteRessource -= stockBois.quantiteRessourceNecessaire;
           printf("\n\nnouveau stockBois !\n\n"); 
           ajoutePiece(T, stockBois);
           niveau ++;
       }
       affiche_auto(niveau, T);
       sleep(1);
    }
    affiche_auto(niveau, T);
    return 0;
}