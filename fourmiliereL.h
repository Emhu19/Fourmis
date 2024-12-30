#ifndef FOURMILIEREL_H
#define FOURMILIEREL_H

#include "fourmi.h"

typedef struct ArbrePiece ArbrePiece;
typedef struct ListRessource ListRessource;
typedef struct ListPiece ListPiece;

typedef struct{
    char *typeRessource;
    int id;
    int quantiteRessource;
    int quantiteMax;
}Ressource;

typedef struct{
    int croissance;
    bool parasite;
}Champignon;

typedef struct{
    int miellat_produit;
    int sante;
}Puceron;

typedef struct{
    int taille;
    int id;
    char *typePiece;
    int capaciteMax;
    Ressource *ressourceNecessaire;
    int quantiteRessourceNecessaire;
    Ressource *ressourceStock;
    int vie;
    int etat;
    int stock;
    Champignon champigon;
    Puceron puceron;
    int nbChampignon;
    int nbPuceron;
}Piece;

struct ArbrePiece{
    Piece salle;
    int taille;
    int profondeur;
    ArbrePiece *filsG;
    ArbrePiece *filsD;
};

struct ListRessource{
    Ressource *ressource;
    ListRessource *suivant;
};

struct ListPiece{
    Piece piece;
    ListPiece *suivant;
};

ArbrePiece *init(Piece e);
int puiss2(int n);
ArbrePiece *ajoutePiece(ArbrePiece *T, Piece R);
void detruitPiece(ArbrePiece *T);

void clear_terminal();
void afficher_titre(const char *titre);

void afficher_salle_simple_milieu(const char *nom);
void afficher_connexion_simple();
void afficher_connexion_simple_milieu();
void afficher_connexion_double();

void afficher_salle_simple(const char *nom);
void afficher_salle_simple_2(const char *nom);
void afficher_salle_simple_3(const char *nom);
void afficher_salle_simple_4(const char *nom);
void afficher_salle_simple_5(const char *nom);
void afficher_salle_simple_6(const char *nom);
void afficher_salles_alignees(const char *nom1, const char *nom2);
void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3);
void afficher_salles_alignees_4(const char *nom1, const char *nom2, const char *nom3, const char *nom4);
void afficher_salles_alignees_5(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5);
void afficher_salles_alignees_6(const char *nom1, const char *nom2, const char *nom3, const char *nom4, const char *nom5, const char *nom6);

void afficher_fourmiliere_niveau(int niveau);
void afficher_legende();
void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine);
void affiche_auto(ArbrePiece *piece);
Ressource *initRessource(int id, int quantiteMax, char *typeRessource);
Piece initPieceStock(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Ressource *ressourceStock);
Piece initPieceChampignon(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Champignon champignon);
Piece initPiecePuceron(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Puceron puceron);
ListRessource *initListR(Ressource *ressource);
ListRessource *ajouteRessource(ListRessource *ressources, Ressource *ressource);
ListPiece *initListP(Piece piece);
ListPiece *ajoutePieceList(ListPiece *pieces, Piece piece);
void cycleFourmiliere(ListRessource *ressources, ArbrePiece *T, ListPiece *pieces, ListFourmi *fourmis);
void mort_de_la_fourmiliere(int raison);
void afficheStock(ArbrePiece *T);
void soignerMaladie(ListFourmi *fourmis);
void effetMaladie(ListFourmi *fourmis);
ListFourmi *genererMaladie(ListFourmi *fourmis, ListMaladie *maladies);
ListMaladie *ajouterMaladie(ListMaladie *maladies, Maladie maladie);
ListMaladie *initListMaladie(Maladie maladie);
Maladie initMaladie(int id, char *typeMaladie);


#endif
