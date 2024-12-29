#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

void genererMaladie(ListFourmi *fourmis, ListMaladie *maladies){
    int malade;
    ListFourmi *tempF;
    tempF = fourmis;
    ListMaladie *tempM;
    tempM = maladies;
    while(tempF != NULL){
        malade = rand()%10;
        while(tempM != NULL){
            if(tempM->maladie.id == malade){
                strcpy(tempF->fourmi->maladie, maladies->maladie.typeMaladie);
            }
            tempM = tempM->suivant;
        }
        tempF = tempF->next;
    }
}
// permet de generer des maladie au sein de la fourmilière de manière aléatoire

// void effetMaladie(Fourmis *A, Maladie *S);
//donne a la fourmi infecté les effet de la maladie qui l'infecte peut être faire une fonction par maladie?

// void soigneMaladie();
//permet de soigner les maladie

int main(){
    srand( time( NULL ) );
    Fourmi *f1;
    Fourmi *f2;
    Fourmi *f3;
    f1 = creationFourmi(1, 1, 0);
    f2 = creationFourmi(2, 1, 0);
    f3 = creationFourmi(3, 1, 0);
    ListFourmi *fourmis;
    fourmis = Initialisation_List();
    fourmis = ajout_fourmi(&fourmis, f1);
    fourmis = ajout_fourmi(&fourmis, f2);
    fourmis = ajout_fourmi(&fourmis, f3);
    ListMaladie *maladies;
    
    genererMaladie(fourmis, maladies);
    afficher_Liste_fourmi(fourmis);
    return 0;
}