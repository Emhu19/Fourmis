#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fourmiliereL.h"
#include "fourmi.h"

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
                T->salle.ressourceStock->quantiteMax -= 10;
                T->salle.ressourceStock->quantiteRessource -= T->salle.stock;
                T->salle.stock = 0;
            }
        }
        detruitPiece(T->filsD);
        detruitPiece(T->filsG);
    }
}

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

void affiche_auto(ArbrePiece *piece){
    if(piece != NULL){
        if(piece->taille == 1){
            if(piece->salle.etat != 0){
                afficher_salle_simple(piece->salle.typePiece);
                afficher_connexion_simple();
            }
        }
        else if(piece->taille== 2){
            if(piece->filsD != NULL){
                 if(piece->salle.etat != 0 && piece->filsD->salle.etat != 0){
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsD->salle.typePiece);
                    afficher_connexion_double();
                }
                else if(piece->filsD->salle.etat == 0 && piece->salle.etat != 0){
                    afficher_salle_simple(piece->salle.typePiece);
                    afficher_connexion_simple();
                }
                else if(piece->filsD->salle.etat != 0 && piece->salle.etat == 0){
                    afficher_salle_simple(piece->filsD->salle.typePiece);
                    afficher_connexion_simple();
                }
            }
            else if(piece->filsG != NULL){
                if(piece->salle.etat != 0 && piece->filsG->salle.etat != 0){
                    afficher_salles_alignees(piece->salle.typePiece, piece->filsG->salle.typePiece);
                    afficher_connexion_double();
                }
                else if(piece->filsG->salle.etat == 0 && piece->salle.etat != 0){
                    afficher_salle_simple(piece->salle.typePiece);
                    afficher_connexion_simple();
                }
                else if(piece->filsG->salle.etat != 0 && piece->salle.etat == 0){
                    afficher_salle_simple(piece->filsG->salle.typePiece);
                    afficher_connexion_simple();
                }
            }
        }
        else if(piece->taille == 3){
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

void afficheStock(ArbrePiece *T){
    if(T != NULL){
        if(T->salle.etat != 0){
            printf("%s contient %d %s\n", T->salle.typePiece, T->salle.stock, T->salle.ressourceStock->typeRessource);
        }
        afficheStock(T->filsG);
        afficheStock(T->filsD);
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

int evaluerBesoinNourriture(ListFourmi *Fourmis, Ressource *Nourriture){
    if(Nourriture->id != 4){
        printf("ce n'est pas de la nourriture !");
        return 0;
    }
    int result;
    result = 0;
    ListFourmi *temp;
    temp = Fourmis;
    while(temp->next != NULL){
        result += temp->fourmi->besoin_faim;
        temp = temp->next;
    }
    if(result > Nourriture->quantiteRessource){
        result -= Nourriture->quantiteRessource;
        return result;
    }
    else{
        return 0;
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
            printf("%s : %d\n",temp->ressource->typeRessource, temp->ressource->quantiteRessource);
        }
        temp = temp->suivant;
    }
    afficheStock(T);
    temp = ressources;
    while(temp != NULL){
        if(temp->ressource->quantiteRessource >= temp->ressource->quantiteMax){
            while(temp->ressource->id != tempP->piece.ressourceStock->id){
                tempP = tempP->suivant;
            }
            printf("%s\n", temp->ressource->typeRessource);
            *quantiteRetire = tempP->piece.quantiteRessourceNecessaire;
            printf("%d\n", *quantiteRetire);
            temp->ressource->quantiteMax += 10;
            T = retireStock(T, quantiteRetire, temp->ressource);
            temp->ressource->quantiteRessource -= tempP->piece.quantiteRessourceNecessaire;
            ajoutePiece(T, tempP->piece);
        }
        tempP = pieces;
        temp = temp->suivant;
    }
    free(quantiteAjout);
    affiche_auto(T);
}

// int main(){
    // ArbrePiece *T;
    // Piece A;
    // ListRessource *ressources;
    // ListPiece *pieces;
    // Ressource *roche;
    // Fourmi *f1;
    // Fourmi *f2;
    // Fourmi *f3;
    // f1 = creationFourmi(1, 1, 0);
    // f2 = creationFourmi(2, 1, 0);
    // f3 = creationFourmi(3, 1, 0);
    // ListFourmi *fourmis;
    // fourmis = Initialisation_List();
    // fourmis = ajout_fourmi(&fourmis, f1);
    // fourmis = ajout_fourmi(&fourmis, f2);
    // fourmis = ajout_fourmi(&fourmis, f3);
    // roche = initRessource(1, 10, "roche");
    // ressources = initListR(roche);
    // Ressource *bois;
    // bois = initRessource(2, 10, "bois");
    // ressources = ajouteRessource(ressources, bois);
    // Ressource *null;
    // null = initRessource(0, 0, "null");
    // Ressource *feuille;
    // feuille = initRessource(3, 10, "feuille");
    // ressources = ajouteRessource(ressources, feuille);
    // Ressource *nourriture;
    // nourriture = initRessource(4, 10, "nourriture");
    // ressources = ajouteRessource(ressources, nourriture);
    // Piece stockBois;
    // stockBois = initPiece(2, bois, 5,  "stockBois", bois);
    // pieces = initListP(stockBois);
    // Piece stockRoche;
    // stockRoche = initPiece(3, roche, 5,  "stockRoche", roche);
    // pieces = ajoutePieceList(pieces, stockRoche);
    // Piece stockFeuille;
    // stockFeuille = initPiece(4, feuille, 5, "sFeuille", feuille);
    // pieces = ajoutePieceList(pieces, stockFeuille);
    // Piece stockNourriture;
    // stockNourriture = initPiece(5, nourriture, 5, "sNourriture", nourriture);
    // pieces = ajoutePieceList(pieces, stockNourriture);
    // A = initPiece(1, bois, 0, "Principale", null);
    // T = init(A);
    // T = ajoutePiece(T, stockBois);
    // T = ajoutePiece(T, stockRoche);
    // T = ajoutePiece(T, stockFeuille);
    // T = ajoutePiece(T, stockNourriture);
    // int besoin;
    // while(1){
        // printf("\n\nnouveau jour !\n\n"); 
        // cycleFourmiliere(ressources, T, pieces);
        // besoin = evaluerBesoinNourriture(fourmis, nourriture);
        // printf("il y a besoin de %d nourriture\n", besoin);
        // sleep(1);
    // }
    // return 0;
// }