#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fourmi.h"

typedef struct ListMaladie ListMaladie;

typedef struct{
    char *typeMaladie;
    int id;
}Maladie;

struct ListMaladie{
    Maladie maladie;
    ListMaladie *suivant;
};

Maladie initMaladie(int id, char *typeMaladie){
    Maladie result;
    result.id = id;
    result.typeMaladie = typeMaladie;
    return result;
}

void genererMaladie(ListMaladie *Maladies){
    int malade;
    malade = rand()%100;
    printf("malade %d", malade);
}
// permet de generer des maladie au sein de la fourmilière de manière aléatoire

// void effetMaladie(Fourmis *A, Maladie *S);
//donne a la fourmi infecté les effet de la maladie qui l'infecte peut être faire une fonction par maladie?

// void soigneMaladie();
//permet de soigner les maladie

int main(){
    srand( time( NULL ) );
    // ListFourmi *Fourmis;
    ListMaladie *Maladies;
    genererMaladie(Maladies);
    return 0;
}