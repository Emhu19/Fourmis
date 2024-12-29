// #include "fourmiliere.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fourmiliereL.h"


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
            T->salle.vie -= 25;
            printf("%s : %d vie\n", T->salle.typePiece, T->salle.vie);
            if(T->salle.vie <= 0){
                printf("la salle %s est détruite c'est dommage\n", T->salle.typePiece);
                T->salle.etat = 0;
                if(T->salle.ressourceStock != NULL){
                    T->salle.ressourceStock->quantiteMax -= 10;
                    T->salle.ressourceStock->quantiteRessource -= T->salle.stock;
                }
                T->salle.stock = 0;
            }
        }
        detruitPiece(T->filsD);
        detruitPiece(T->filsG);
    }
}

ArbrePiece *ajouteStock(ArbrePiece *T, int *quantiteAjout, Ressource *ressource){
    if(T == NULL){
        return NULL;
    }
    if(T->salle.ressourceStock == ressource && T->salle.etat != 0 && T->salle.stock < T->salle.capaciteMax){
        T->salle.stock += *quantiteAjout;
        *quantiteAjout -= *quantiteAjout;
        return T;
    }
    if(T->filsG != NULL){
        T->filsG = ajouteStock(T->filsG, quantiteAjout, ressource);
    }
    if(T->filsD != NULL){
        T->filsD = ajouteStock(T->filsD, quantiteAjout, ressource);
    }
    return T;
}

ArbrePiece *retireStock(ArbrePiece *T, int *quantiteRetire, Ressource *ressource){
    if(T == NULL){
        return NULL;
    }
    if(T->salle.ressourceStock == ressource && T->salle.etat != 0){
        T->salle.stock -= *quantiteRetire;
        *quantiteRetire -= *quantiteRetire;
        return T;
    }
    if(T->filsG != NULL){
        T->filsG = retireStock(T->filsG, quantiteRetire, ressource);
    }
    if(T->filsD != NULL){
        T->filsD = retireStock(T->filsD, quantiteRetire, ressource);
    }
    return T;
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

void afficher_salle_simple_2(const char *nom) {
    printf("                            +-----------------+\n");
    printf("                            |                 |\n");
    printf("                            |     %-10s  |\n", nom);
    printf("                            |                 |\n");
    printf("                            +-----------------+\n");
}

void afficher_salle_simple_3(const char *nom) {
    printf("                                                        +-----------------+\n");
    printf("                                                        |                 |\n");
    printf("                                                        |     %-10s  |\n", nom);
    printf("                                                        |                 |\n");
    printf("                                                        +-----------------+\n");
}

void afficher_salle_simple_4(const char *nom) {
    printf("                                                                                    +-----------------+\n");
    printf("                                                                                    |                 |\n");
    printf("                                                                                    |     %-10s  |\n", nom);
    printf("                                                                                    |                 |\n");
    printf("                                                                                    +-----------------+\n");
}
void afficher_salle_simple_5(const char *nom) {
    printf("                                                                                                                +-----------------+\n");
    printf("                                                                                                                |                 |\n");
    printf("                                                                                                                |     %-10s  |\n", nom);
    printf("                                                                                                                |                 |\n");
    printf("                                                                                                                +-----------------+\n");
}
void afficher_salle_simple_6(const char *nom) {
    printf("                                                                                                                                            +-----------------+\n");
    printf("                                                                                                                                            |                 |\n");
    printf("                                                                                                                                            |     %-10s  |\n", nom);
    printf("                                                                                                                                            |                 |\n");
    printf("                                                                                                                                            +-----------------+\n");
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
/**********************************************************************************************************************************************************************************/



/**********************************************************************************************************************************************************************************/
void afficher_salles_alignees(const char *nom1, const char *nom2) {
    printf("+-----------------+         +-----------------+\n");
    printf("|                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |\n", nom1, nom2);
    printf("|                 |         |                 |\n");
    printf("+-----------------+         +-----------------+\n");
}
/**********************************************************************************************************************************************************************************/


/**********************************************************************************************************************************************************************************/
void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3) {
    printf("+-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3);
    printf("|                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+\n");
}
/**********************************************************************************************************************************************************************************/


/**********************************************************************************************************************************************************************************/
void afficher_salles_alignees_4(const char *nom1, const char *nom2, const char *nom3, const char *nom4) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3, nom4);
    printf("|                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}

/**********************************************************************************************************************************************************************************/
void gestionElevage(ArbrePiece *T) {
    if (T == NULL) return;
    if(T->salle.etat == 0) return;

    if (strcmp(T->salle.typePiece, "Champignons") == 0) {
        Champignon *champignon = &T->salle.champignon;

        if (!champignon->parasite && (rand() % 100 < 5)) {
            champignon->parasite = true;
        }

        if (champignon->parasite) {
            champignon->nbChampignon -= 5;
            if (champignon->nbChampignon < 0) champignon->nbChampignon = 0;
        } else {
            champignon->nbChampignon += champignon->croissance;
            if (champignon->nbChampignon > T->salle.capaciteMax) {
                champignon->nbChampignon = T->salle.capaciteMax;
            }
        }
    }

    if (strcmp(T->salle.typePiece, "Pucerons") == 0) {
        Puceron *puceron = &T->salle.puceron;

        if (puceron->sante > 0) {
            puceron->miellat_produit += puceron->nbPuceron;
            puceron->nbPuceron++;
            if (puceron->nbPuceron > T->salle.capaciteMax) {
                puceron->nbPuceron = T->salle.capaciteMax;
            }
        } else {
            puceron->nbPuceron -= 1;
            if (puceron->nbPuceron < 0) puceron->nbPuceron = 0;
        }
    }

    gestionElevage(T->filsG);
    gestionElevage(T->filsD);
}


/**********************************************************************************************************************************************************************************/
void afficher_salles_alignees_5(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |     %-10s  |\n", nom1, nom2, nom3, nom4, nom5);
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}
void afficher_salles_alignees_5_1(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |     %-10s  |----+----|     %-10s  |----+----|      %-10s  |\n", nom1, nom2, nom3, nom4, nom5);
    printf("|                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}
void afficher_salles_alignees_5_5(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5) {
    printf("                            +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("                            |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("                            |     %-10s  |----+----|     %-10s  |     %-10s  |----+----|     %-10s  |----+----|      %-10s  |\n", nom1, nom2, nom3, nom4, nom5);
    printf("                            |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("                            +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}
/**********************************************************************************************************************************************************************************/


/**********************************************************************************************************************************************************************************/
void afficher_salles_alignees_6(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5, const char *nom6) {
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |     %-10s  |----+----|     %-10s  ||     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3, nom4, nom5, nom6);
    printf("|                 |         |                 |         |                 |         |                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+         +-----------------+\n");
}
/**********************************************************************************************************************************************************************************/

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

Ressource *initRessource(int id, int quantiteMax, char *typeRessource){
    Ressource *ressource;
    ressource = malloc(sizeof(Ressource *));
    ressource->quantiteRessource = 0;
    ressource->quantiteMax = quantiteMax;
    ressource->id = id;
    ressource->typeRessource = typeRessource;
    return ressource;
}

Piece initPieceStock(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Ressource *ressourceStock){
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

Piece initPieceChampignon(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Champignon champignon){
    Piece piece;
    piece.id = id;
    piece.ressourceNecessaire = ressourceNecessaire;
    piece.ressourceStock = NULL;
    piece.stock = 0;
    piece.capaciteMax = 10;
    piece.vie = 500;
    piece.typePiece = typePiece;
    piece.quantiteRessourceNecessaire = quantiteRNecessaire;
    piece.etat = 1;
<<<<<<< HEAD
    piece.champignon = champignon;
    piece.puceron = puceron;
    piece.champignon.nbChampignon = 0;
    piece.puceron.nbPuceron = 0;
=======
    piece.champigon = champignon;
    piece.nbChampignon = 0;
    return piece;
}

Piece initPiecePuceron(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Puceron puceron){
    Piece piece;
    piece.id = id;
    piece.ressourceNecessaire = ressourceNecessaire;
    piece.ressourceStock = NULL;
    piece.stock = 0;
    piece.capaciteMax = 10;
    piece.vie = 500;
    piece.typePiece = typePiece;
    piece.quantiteRessourceNecessaire = quantiteRNecessaire;
    piece.etat = 1;
    piece.puceron = puceron;
    piece.nbPuceron = 0;
>>>>>>> 6f0b2c002f45db590496e3addb3c21e730ff2467
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

void afficheStock(ArbrePiece *T){
    if(T != NULL){
        if(T->salle.etat != 0){
            printf("%s contient %d %s\n", T->salle.typePiece, T->salle.stock, T->salle.ressourceStock->typeRessource);
        }
        afficheStock(T->filsG);
        afficheStock(T->filsD);
    }
}

void cycleFourmiliere(ListRessource *ressources, ArbrePiece *T, ListPiece *pieces){
    detruitPiece(T);
    ListRessource *temp;
    ListPiece *tempP;
    int *quantiteAjout;
    quantiteAjout = malloc(sizeof(int));
    *quantiteAjout = 1;
    int *quantiteRetire;
    quantiteRetire = malloc(sizeof(int));
    *quantiteRetire = 1;
    temp = ressources;
    tempP = pieces;
    while(temp != NULL){
        if(temp->ressource->quantiteRessource < temp->ressource->quantiteMax){
            temp->ressource->quantiteRessource++;
            *quantiteAjout = 1;
            T = ajouteStock(T, quantiteAjout, temp->ressource);
        }
        temp = temp->suivant;
    }
    temp = ressources;
    while(temp != NULL){
        if(temp->ressource->quantiteRessource >= temp->ressource->quantiteMax){
            while(tempP->piece.ressourceStock == NULL){
                tempP = tempP->suivant;
            }
            while(temp->ressource->id != tempP->piece.ressourceStock->id){
                tempP = tempP->suivant;
                while(tempP->piece.ressourceStock == NULL){
                    tempP = tempP->suivant;
                }
            }
            *quantiteRetire = tempP->piece.quantiteRessourceNecessaire;
            temp->ressource->quantiteMax += 10;
            T = retireStock(T, quantiteRetire, temp->ressource);
            temp->ressource->quantiteRessource -= tempP->piece.quantiteRessourceNecessaire;
            ajoutePiece(T, tempP->piece);
        }
        tempP = pieces;
        temp = temp->suivant;
    }
    afficher_titre("Terre");
    affiche_auto(T);
    afficher_titre("Centre de la Terre");
    free(quantiteAjout);
    free(quantiteRetire);
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

void mort_de_la_fourmiliere(int raison){
    if(raison == 1){ //mort de la reine
        printf("La reine est mort, aucune autres reines dans la colonie pour faire survivre la fourmilières\n");
        printf("La fourmiliere s'éteint lentement durant 2 ans et se termine quand la dernière fourmi meurt...\n");
    }
    else if(raison == 2){ //risque climatique
        printf("La pluie à inonder la fourmilière\n");
    }
    else if(raison == 3){ //effondrement de la fourmiliere
        printf("La fourmiliere était trop endommagé, aucune des salles n'a tenue, tout c'est éffondrer\n");
    }
    printf("Fin de la simulation, merci d'avoir simuler\n\n");
}
