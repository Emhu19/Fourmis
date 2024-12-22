#ifndef FOURMILIERE_H
#define FOURMILIERE_H

#include "fourmi.h"

typedef struct ArbrePiece ArbrePiece;

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
}Piece;

struct ArbrePiece{
    Piece salle;
    int taille;
    int profondeur;
    ArbrePiece *filsG;
    ArbrePiece *filsD;
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

#endif
