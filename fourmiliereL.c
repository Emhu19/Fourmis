// #include "fourmiliere.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fourmiliereL.h"

// typedef struct ListFourmi ListFourmi;
// typedef struct ListReine ListReine;
// typedef struct ArbrePiece ArbrePiece;
// 
// struct ListFourmi{
    // Fourmis *fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
    // ListFourmi *suivant;
    // ListFourmi *precedent; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente 
// };
// 
// struct ListReine{
    // Reine *reine;
    // ListReine *suivant;
    // ListReine *precedent; //même raison que pour ListFourmi
// };
// 
// typedef struct{
    // char *typeRessource;
    // int id;
    // int quantiteRessource;
    // int quantiteMax;
// }Ressource;
// 
// typedef struct{
    // ListFourmi *fourmi; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de fourmis
    // ListReine *reine; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de reine (il est possible qu'il y ait plusieur reine dans la fourmilière)
    // ArbrePiece *piece; //plus simple a parcourir pour savoir quelle salle mêne a ou
// }Fourmilière;
// 
// typedef struct{
    // int taille;
    // int id;
    // char *typePiece;
    // int capaciteMax;
    // Ressource *ressourceNecessaire;
    // int quantiteRessourceNecessaire;
    // Ressource *ressourceStock;
    // int vie;
    // int etat;
    // int stock;
// }Piece;
// 
// struct ArbrePiece{
    // Piece salle;
    // int taille;
    // int profondeur;
    // ArbrePiece *filsG;
    // ArbrePiece *filsD;
// };

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

void detruitPiece(ArbrePiece *T){
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
        detruitPiece(T->filsD);
        detruitPiece(T->filsG);
    }
}

ArbrePiece *ajouteStock(ArbrePiece *T, int quantiteAjout, Ressource *ressource){
    if(T == NULL){
        return NULL;
    }
    if(T->salle.ressourceStock->id == ressource->id && T->salle.stock + quantiteAjout < T->salle.capaciteMax){
        T->salle.stock += quantiteAjout;
        return T;
    }
    else if(T->filsG->salle.ressourceStock->id == ressource->id){
        T->filsG = ajouteStock(T->filsG, quantiteAjout, ressource);
        return T;
    }
    else if(T->filsD->salle.ressourceStock->id == ressource->id){
        T->filsD = ajouteStock(T->filsD, quantiteAjout, ressource);
        return T;
    }
    else if(ajouteStock(T->filsG, quantiteAjout, ressource) != NULL){
        T->filsG = ajouteStock(T->filsG, quantiteAjout, ressource);
        return T;
    }
    else if(ajouteStock(T->filsD, quantiteAjout, ressource) != NULL){
        T->filsD = ajouteStock(T->filsD, quantiteAjout, ressource);
        return T;        
    }
    else{
        return T;
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
    printf("\n\033[0;33m========================================================================= %s =========================================================================\033[0m\n\n", titre);
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

void afficher_salles_alignees_4(const char *nom1, const char *nom2, const char *nom3, const char *nom4) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3, nom4);
    printf("|                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}

void afficher_salles_alignees_5(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |     %-10s  |\n", nom1, nom2, nom3, nom4, nom5);
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}

void afficher_salles_alignees_6(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5, const char *nom6) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |     %-10s  |     %-10s  |\n", nom1, nom2, nom3, nom4, nom5, nom6);
    printf("|                 |         |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
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

void affiche_auto(ArbrePiece *piece){
    if(piece != NULL){
        if(piece->taille == 1){
            if(piece->salle.etat != 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->salle.typePiece);
            }
        }
        else if(piece->taille== 2){
            if(piece->filsD != NULL){
                if(piece->salle.etat != 0){
                    afficher_connexion_double();
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsD->salle.typePiece);

                }
                else if(piece->filsD->salle.etat != 0){
                    afficher_connexion_simple();
                    afficher_salle_simple(piece->filsD->salle.typePiece);
                }
            }
            else if(piece->filsG != NULL){
                if(piece->salle.etat != 0){
                    afficher_connexion_double();
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsG->salle.typePiece);

                }
                else if(piece->filsG->salle.etat != 0){
                    afficher_connexion_simple();
                    afficher_salle_simple(piece->filsG->salle.typePiece);

                }
            }
        }
        else if(piece->taille == 3){
            if(piece->salle.etat != 0){
                afficher_connexion_triple();
                afficher_salles_alignees_3(piece->salle.typePiece, piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);

            }
            else if(piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->filsG->salle.typePiece);

            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat == 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->filsD->salle.typePiece);

            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat != 0){
                afficher_connexion_double();
                afficher_salles_alignees(piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);

            }
        }
        else{
            if(piece->salle.etat != 0 && piece->filsG->salle.etat != 0 && piece->filsD->salle.etat != 0){
                afficher_connexion_triple();
                afficher_salles_alignees_3(piece->salle.typePiece, piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);

            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_connexion_double();
                afficher_salles_alignees(piece->salle.typePiece, piece->filsG->salle.typePiece);

            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat == 0 && piece->filsD->salle.etat != 0){
                afficher_connexion_double();
                afficher_salles_alignees(piece->salle.typePiece, piece->filsD->salle.typePiece);

            }
            else if(piece->salle.etat != 0 && piece->filsG->salle.etat == 0 && piece->filsD->salle.etat == 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->salle.typePiece);
            }
            else if(piece->filsG->salle.etat != 0 && piece->filsD->salle.etat == 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->filsG->salle.typePiece);
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat == 0){
                afficher_connexion_simple();
                afficher_salle_simple(piece->filsD->salle.typePiece);
            }
            else if(piece->filsD->salle.etat != 0 && piece->filsG->salle.etat != 0){
                afficher_connexion_double();
                afficher_salles_alignees(piece->filsG->salle.typePiece, piece->filsD->salle.typePiece);

            }
            affiche_auto(piece->filsG->filsG);
            affiche_auto(piece->filsG->filsD);
            affiche_auto(piece->filsD->filsD);
            affiche_auto(piece->filsD->filsG);
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

// void afficher_fourmiliere(int niveau/*, ListFourmi* liste, Reine* reine */) {
    // clear_terminal();
    // afficher_titre("Fourmilière");
    // afficher_fourmiliere_niveau(niveau);
    // afficher_legende(liste, reine);
    // compter_Liste_fourmi(liste);
    // printf("\n\033[1;32mAppuyez sur Entrée pour continuer...\033[0m\n");
    // usleep(500000);
    // getchar();
// }

Ressource *initRessource(int id, int quantiteMax, char *typeRessource){
    Ressource *ressource;
    ressource = malloc(sizeof(Ressource *));
    ressource->quantiteRessource = 0;
    ressource->quantiteMax = quantiteMax;
    ressource->id = id;
    ressource->typeRessource = typeRessource;
    return ressource;
}

Piece initPiece(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Ressource *ressourceStock){
    Piece piece;
    piece.id = id;
    piece.ressourceNecessaire = ressourceNecessaire;
    piece.ressourceStock = ressourceStock;
    piece.stock = 0;
    piece.vie = 500;
    piece.typePiece = typePiece;
    piece.capaciteMax = 10;
    piece.quantiteRessourceNecessaire = quantiteRNecessaire;
    piece.etat = 1;
    piece.capaciteMax = 10;
    return piece;
}

ListRessource *initListR(Ressource *ressource){
    ListRessource *temp;
    temp = malloc(sizeof(ListRessource *));
    temp->ressource = ressource;
    temp->suivant = NULL;
    return temp;
}

ListRessource *ajouteRessource(ListRessource *ressources, Ressource *ressource){
    ListRessource *temp;
    temp = malloc(sizeof(ListRessource *));
    temp->ressource = ressource;
    temp->suivant = ressources;
    return temp;
}

ListPiece *initListP(Piece piece){
    ListPiece *pieces;
    pieces = malloc(sizeof(ListPiece));
    pieces->piece = piece;
    pieces->suivant = NULL;
    return pieces;
}

ListPiece *ajoutePieceList(ListPiece *pieces, Piece piece){
    ListPiece *temp;
    temp = malloc(sizeof(ListPiece));
    temp->piece = piece;
    temp->suivant = pieces;
    return temp;
}

void afficheList(ListRessource *T){
    ListRessource *temp;
    temp = T;
    while(temp != NULL){
        printf("%d ", temp->ressource->id);
        temp = temp->suivant;
    }
}

void cycleFourmiliere(ListRessource *ressources, ArbrePiece *T, ListPiece *pieces){
    detruitPiece(T);
    ListRessource *temp;
    ListPiece *tempP;
    temp = ressources;
    tempP = pieces;
    while(temp != NULL){
        if(temp->ressource->quantiteRessource < temp->ressource->quantiteMax){
            temp->ressource->quantiteRessource++;
        }
        temp = temp->suivant;
    }
    temp = ressources;
    while(temp != NULL){
        if(temp->ressource->quantiteRessource >= temp->ressource->quantiteMax){
            while(temp->ressource->id != tempP->piece.ressourceStock->id){
                tempP = tempP->suivant;
            }
            temp->ressource->quantiteMax += 10;
            temp->ressource->quantiteRessource -= tempP->piece.quantiteRessourceNecessaire;
            ajoutePiece(T, tempP->piece);
        }
        tempP = pieces;
        temp = temp->suivant;
    }
    afficher_titre("Terre");
    affiche_auto(T);
    afficher_titre("Centre de la Terre");
}

// int main(){
    // ArbrePiece *T;
    // Piece A;
    // ListRessource *ressources;
    // ListPiece *pieces;
    // Ressource *metal;
    // Ressource *bois;
    // Piece stockBois;
    // Piece stockMetal;
    // metal = initRessource(1, 10, "metal");
    // ressources = initListR(metal);
    // bois = initRessource(2, 10, "bois");
    // ressources = ajouteRessource(ressources, bois);
    // stockBois = initPiece(2, bois, 5,  "stockBois", bois);
    // pieces = initListP(stockBois);
    // stockMetal = initPiece(3, metal, 5,  "stockMetal", metal);
    // pieces = ajoutePieceList(pieces, stockMetal);
    // A = initPiece(1, bois, 0, "Principale", bois);
    // T = init(A);
    // while(1){
    //    printf("\n\nnouveau jour !\n\n"); 
    //    detruitPiece(T);
    //    if(metal->quantiteRessource < metal->quantiteMax){
        //    metal->quantiteRessource++;
        //    ajouteStock(T, 1, metal);
    //    }
    //    if(bois->quantiteRessource < bois->quantiteMax){
        //    bois->quantiteRessource += 2;
    //    }
    //    if(metal->quantiteRessource >= metal->quantiteMax){
        //    metal->quantiteMax += 10;
        //    metal->quantiteRessource -= stockMetal.quantiteRessourceNecessaire;
        //    printf("\n\nnouveau stockMetal !\n\n"); 
        //    ajoutePiece(T, stockMetal);
        //    niveau ++;
    //    }
    //    if(bois->quantiteRessource >= bois->quantiteMax){
        //    bois->quantiteMax += 10;
        //    bois->quantiteRessource -= stockBois.quantiteRessourceNecessaire;
        //    printf("\n\nnouveau stockBois !\n\n"); 
        //    ajoutePiece(T, stockBois);
        //    niveau ++;
    //    }
    //    affiche_auto(T);
        // cycleFourmiliere(ressources, T, pieces);
        // sleep(1);
    // }
    // return 0;
// }
