#include <stdio.h>
#include <stdlib.h>

typedef struct ListFourmi ListFourmi;
typedef struct ListReine ListReine;
typedef struct ArbrePiece ArbrePiece;
typedef struct ListRessource ListRessource;

struct ListFourmi{
    Fourmis *fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
    ListFourmi *suivant;
    ListFourmi *precedent; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente 
};

struct ListReine{
    Reine *reine;
    ListReine *suivant;
    ListReine *precedent; //même raison que pour ListFourmi
};

struct ArbrePiece{
    Piece *salle;
    ArbrePiece *filsG;
    ArbrePiece *filsD;
};

typedef struct{
    char *typeRessource;
    int id;
    int *quantiteRessource;
}Resource;

struct ListRessource{
    Resource *resource;
    ListRessource *suivant;
    ListRessource *precedent
};

typedef struct{
    ListFourmi *fourmi; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de fourmis
    ListReine *reine; //liste chainée car on aura besoin d'augmenter et de baisser les nombre de reine (il est possible qu'il y ait plusieur reine dans la fourmilière)
    ArbrePiece *piece; //plus simple a parcourir pour savoir quelle salle mêne a ou
}Fourmilière;

typedef struct{
    int taille;
    int id; //j'hésite avec un char * mais si il n'y a pas beaucoup de salle un int permet des comparaison plus simple a vous de voir
    char *typePiece;
    ListRessource *ressource;
    int capaciteMax;
}Piece;


typedef struct{
    char *typeMaladie;
    int id;
    
}Maladie;

void ajoutePiece(ArbrePiece *T, Piece *R, ListRessource *L);
// permet d'ajouter une salle si on a les ressources nécéssaire

Resource *detruitPiece(ArbrePiece *T, Piece *R);
// permet de détruire une salle renvoie les matériaux que la destrucion donne

Maladie genereMaladie();
// permet de generer des maladie au sein de la fourmilière de manière aléatoire

void effetMaladie(Fourmis *A, Maladie *S);
//donne a la fourmi infecté les effet de la maladie qui l'infecte peut être faire une fonction par maladie?

void soigneMaladie();
//permet de soigner les maladie

void stock(Fourmis *A, Piece *T);
// permet a une fourmi de stocker les materiaux qu'elle a récupere si la salle le permet
