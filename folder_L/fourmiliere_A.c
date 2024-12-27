#include <stdio.h>
#include <stdlib.h>
#include <environnement.h>





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
        printf("%d\n", T->salle.id);
    }
    if(T->filsD != NULL){
        afficheArbre(T->filsD);
    }
}

Resource *detruitPiece(ArbrePiece *T, Piece *R);
// permet de détruire une salle renvoie les matériaux que la destrucion donne

Maladie genereMaladie();
// permet de generer des maladie au sein de la fourmilière de manière aléatoire

// void effetMaladie(Fourmis *A, Maladie *S);
//donne a la fourmi infecté les effet de la maladie qui l'infecte peut être faire une fonction par maladie?

// void soigneMaladie();
//permet de soigner les maladie

// void stock(Fourmis *A, Piece *T);
// permet a une fourmi de stocker les materiaux qu'elle a récupere si la salle le permet



Fourmiliere init_fourmiliere(Environnement* E){
    Fourmiliere F;
    F.fourmi = NULL;
    F.reine = NULL;
    F.salle = NULL;
    F.x = 12;
    F.y = 12;
    F.suivant = NULL;

    E->chunks[F.x][F.y].type = 1;
}

int main(){
    ArbrePiece *T;
    Piece R;
    Piece Q;
    Piece S;
    Piece U;
    Piece V;
    Piece W;
    Piece A;
    Piece B;
    Piece C;
    Piece D;
    Piece E;
    Piece F;
    Piece G;
    Piece H;
    Piece I;
    // R = malloc(sizeof(Piece *));
    Resource metal;
    metal.quantiteRessource = 10;
    A.id = 1;
    A.capaciteMax = 10;
    A.quantiteRessourceNecessaire = 10;
    A.ressourceNecessaire = metal;
    A.taille = 10;
    A.typePiece = "piece";
    R.id = 2;
    Q.id = 3;
    S.id = 4;
    U.id = 5;
    V.id = 6;
    W.id = 7;
    B.id = 8;
    C.id = 9;
    D.id = 10;
    E.id = 11;
    F.id = 12;
    G.id = 13;
    H.id = 14;
    I.id = 15;
    T = init(A);
    if(T == NULL){
        printf("hein");
    }
    // printf("%d\n", A->id);
    // Resource bois;
    // Resource metal;
    // bois.quantiteRessource = 5;
    // metal.quantiteRessource = 10;
    // bois.id = 1;
    // metal.id = 2;
    // R.ressourceNecessaire = metal;
    // R.quantiteRessourceNecessaire = 5;
    // R.id = 2;
    // printf("%d\n", A->id);
    ajoutePiece(T, R);
    ajoutePiece(T, Q);
    ajoutePiece(T, S);
    ajoutePiece(T, U);
    ajoutePiece(T, V);
    ajoutePiece(T, W);
    ajoutePiece(T, B);
    ajoutePiece(T, C);
    ajoutePiece(T, D);
    ajoutePiece(T, E);
    ajoutePiece(T, F);
    ajoutePiece(T, G);
    ajoutePiece(T, H);
    ajoutePiece(T, I);
    afficheArbre(T);
    // if(T->filsG == NULL){
        // printf("heiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinMaisPouquoiJeVaisMefoutreEnLair");
    // }
    // free(bois);
    return 0;
}