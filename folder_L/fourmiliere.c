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

void *detruitPiece(ArbrePiece *T){
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

int main(){
    ArbrePiece *T;
    char test;
    Piece A;
    Resource *metal;
    metal = malloc(sizeof(Resource *));
    metal->quantiteRessource = 0;
    metal->id = 1;
    metal->typeRessource = "bois";
    metal->quantiteMax = 50000;
    Resource *bois;
    bois = malloc(sizeof(Resource *));
    bois->quantiteRessource = 0;
    bois->id = 1;
    bois->typeRessource = "bois";
    bois->quantiteMax = 50000;
    Piece stockBois;
    stockBois.id = 2;
    stockBois.quantiteRessourceNecessaire = 10;
    stockBois.ressourceNecessaire = bois;
    stockBois.vie = 5000;
    stockBois.etat = 1;
    Piece stockMetal;
    stockMetal.id = 3;
    stockMetal.quantiteRessourceNecessaire = 25;
    stockMetal.ressourceNecessaire = metal;
    stockMetal.vie = 5000;
    stockMetal.etat = 1;
    A.id = 1;
    A.capaciteMax = 10;
    A.quantiteRessourceNecessaire = 10;
    A.ressourceNecessaire = metal;
    A.taille = 10;
    A.typePiece = "principale";
    A.etat = 1;
    T = init(A);
    while(1){
        detruitPiece(T);
        if(metal->quantiteRessource < metal->quantiteMax){
            metal->quantiteRessource++;
        }
        if(bois->quantiteRessource < bois->quantiteMax){
            bois->quantiteRessource += 2;
        }
        if(metal->quantiteRessource <= metal->quantiteMax){
            metal->quantiteMax += 50000;
            metal->quantiteRessource -= stockMetal.quantiteRessourceNecessaire;
            ajoutePiece(T, stockMetal);
        }
        if(bois->quantiteRessource <= bois->quantiteMax){
            bois->quantiteMax += 50000;
            bois->quantiteRessource -= stockBois.quantiteRessourceNecessaire;
            ajoutePiece(T, stockBois);
        }
        afficheArbre(T);
        printf("\n");
        sleep(5);
    }
    return 0;
}