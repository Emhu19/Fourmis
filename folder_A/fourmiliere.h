#ifndef FOURMILIERE_H
#define FOURMILIERE_H

#include "fourmi.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct ListFourmi ListFourmi;
typedef struct ListReine ListReine;
typedef struct ArbrePiece ArbrePiece;
typedef struct ListRessource ListRessource;

// struct ListFourmi{
//     // Fourmis *fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
//     ListFourmi *suivant;
//     ListFourmi *precedent; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente 
// };

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
}Ressource;

// struct ListRessource{
    // Resource *resource;
    // ListRessource *suivant;
    // ListRessource *precedent;
// };

typedef struct{
    ListFourmi *fourmi; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de fourmis
    ListReine *reine; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de reine (il est possible qu'il y ait plusieur reine dans la fourmilière)
    ArbrePiece *piece; //plus simple a parcourir pour savoir quelle salle mêne a ou
    int espece;
    int x;
    int y;
}Fourmiliere;

typedef struct{
    int taille;
    int id;
    char *typePiece;
    int capaciteMax;
    Ressource *ressourceNecessaire;
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


typedef struct{
    char *typeMaladie;
    int id;
}Maladie;


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


ArbrePiece *init(Piece e);


int puiss2(int n);

ArbrePiece *ajoutePiece(ArbrePiece *T, Piece R);

void afficheArbre(ArbrePiece *T);
void detruitPiece(ArbrePiece *T);

Maladie genereMaladie();


void clear_terminal() ;

void afficher_titre(const char *titre);

void afficher_salle_simple(const char *nom);

void afficher_salle_simple_milieu(const char *nom);

void afficher_connexion_simple();

void afficher_connexion_simple_milieu();

void afficher_connexion_double();
void afficher_salles_alignees(const char *nom1, const char *nom2);

void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3);

void afficher_fourmiliere_niveau(int niveau);

int salle_reine(Reine* reine);

void afficher_legende(ListFourmi* liste, Reine* reine);

void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine);



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



int puiss2(int n);




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


#endif
