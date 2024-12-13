#ifndef FOURMI_H
#define FOURMI_H

#include <stdbool.h>
#include "reine.h"

#define MAX_CHAR 50

typedef struct {
    char espece[MAX_CHAR];
    int id_fourmi;
    int salle;
    bool sexe;
    char role[MAX_CHAR];
    int age;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    bool sante;
    char maladie[MAX_CHAR];
    float cgt;
    int coord_x;
    int coord_y;
} Fourmi;


typedef struct ListFourmi{
    Fourmi* fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
    struct ListFourmi *prev;
    struct ListFourmi *next; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente
}ListFourmi;
Fourmi* creationFourmi(int id, const char* role_fourmi, int type_fourmi);
void afficher_fourmi(const Fourmi* fourmi);
ListFourmi* Initialisation_List();
void afficher_Liste_fourmi(ListFourmi* liste);
ListFourmi* ajout_fourmi(ListFourmi** liste, Fourmi* fourmi);
ListFourmi* retirer_fourmi(ListFourmi** liste, Fourmi* fourmi);
void compter_Liste_fourmi(ListFourmi* liste);
void liberer_liste(ListFourmi* liste);
Fourmi* trouver_fourmi(ListFourmi* liste, int id);
ListFourmi* fusionner_listes(ListFourmi* liste1, ListFourmi* liste2);
void mise_a_jour_fourmi(Fourmi* fourmi);
void nourrir_fourmi(Fourmi* fourmi);
void deplacer_fourmi(Fourmi* fourmi, int x, int y);
void update_day_fourmi(Fourmi* fourmi);
void update_day_liste_fourmi(ListFourmi* liste);
int compter_fourmi_salle(ListFourmi* liste, int salle);

#endif
