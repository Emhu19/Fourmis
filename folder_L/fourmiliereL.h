#ifndef FOURMILIEREL_H
#define FOURMILIEREL_H

#include "fourmi.h"

typedef struct ArbrePiece ArbrePiece;
typedef struct ListRessource ListRessource;
typedef struct ListPiece ListPiece;
typedef struct ListMaladie ListMaladie;

typedef struct{
    char *typeMaladie;
    int id;
}Maladie;

struct ListMaladie{
    Maladie maladie;
    ListMaladie *suivant;
};

typedef struct{
    char *typeRessource;
    int id;
    int quantiteRessource;
    int quantiteMax;
}Ressource;

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
    ListFourmi *fourmis;
    int quantiteFourmiMax;
    int quantiteFourmi;
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
void afficher_salle_simple(const char *nom);
void afficher_salle_simple_milieu(const char *nom);
void afficher_connexion_simple();
void afficher_connexion_simple_milieu();
void afficher_connexion_double();
void afficher_salles_alignees(const char *nom1, const char *nom2);
void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3);
void afficher_fourmiliere_niveau(int niveau);
void afficher_legende();
void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine);
void affiche_auto(ArbrePiece *piece);
Ressource *initRessource(int id, int quantiteMax, char *typeRessource);
Piece initPiece(int id, Ressource *ressourceNecessaire, int quantiteRNecessaire, char *typePiece, Ressource *ressourceStock, int quantiteFourmiMax);
ListRessource *initListR(Ressource *ressource);
ListRessource *ajouteRessource(ListRessource *ressources, Ressource *ressource);
ListPiece *initListP(Piece piece);
ListPiece *ajoutePieceList(ListPiece *pieces, Piece piece);
void afficheStock(ArbrePiece *T);
ArbrePiece *ajouteStock(ArbrePiece *T, int *quantiteAjout, Ressource *ressource);
ArbrePiece *retireStock(ArbrePiece *T, int *quantiteRetire, Ressource *ressource);
void cycleFourmiliere(ListRessource *ressources, ArbrePiece *T, ListPiece *pieces);
int evaluerBesoinNourriture(ListFourmi *Fourmis, Ressource *Nourriture);
void libereArbre(ArbrePiece *T);
ArbrePiece *ajouteFourmi(ArbrePiece *T, Fourmi **fourmi);
Maladie initMaladie(int id, char *typeMaladie);
void genererMaladie(ListFourmi *fourmis, ListMaladie *maladies);
ListMaladie *initListMaladie(Maladie maladie);
ListMaladie *ajouterMaladie(ListMaladie *maladies, Maladie maladie);


#endif
