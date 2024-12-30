#ifndef FOURMI_H
#define FOURMI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reine.h"
#include "environnement.h"
#include "fourmi.h"


#define BASE_COOR_X 12
#define BASE_COOR_Y 12
#define MAX_CHAR 50

typedef enum {
    NOURRICE,
    EXPLORATRICE,
    OUVRIERE,
    COLLECTRICE_MIELLAT,
    SOLDAT,
    POT_DE_MIEL,
    AGRICOLE,
    ELEVEUR
} RolePrincipal;

typedef struct ListMaladie ListMaladie;

typedef struct{
    char *typeMaladie;
    int id;
}Maladie;

struct ListMaladie{
    Maladie maladie;
    ListMaladie *suivant;
};

typedef struct {
   bool estCultivatrice; //Atta et Acromyrmex
   bool estNageuse; //Polyrhachis
   bool estEleveur; //Formica
   bool estAustralienne; //Camponotus
} RoleSecondaire;

typedef struct {
    int eau;
    int nourriture;
    int feuilles;
    int bois;
    int seve;
} Inventaire;

typedef struct {
    RolePrincipal role;
    RoleSecondaire role_secondaire;
    Inventaire* inventaire;
    int espece;
    int id_fourmi;
    int salle;
    bool sexe;
    int age;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    int sante;
    Maladie maladie;
    bool estMalade;
    float cgt;
    int coord_x;
    int coord_y;
} Fourmi;


typedef struct ListFourmi{
    Fourmi* fourmi;
    struct ListFourmi *prev;
    struct ListFourmi *next; //liste doublement chainée car on pourrait avoir besoin de revenir a la fourmis précedente
}ListFourmi;

/****************************************************************************/
Fourmi* creationFourmi(int id, int type_fourmi, bool sexe);
void afficher_fourmi(const Fourmi* fourmi);
/****************************************************************************/

/****************************************************************************/
ListFourmi* Initialisation_List();
void afficher_Liste_fourmi(ListFourmi* liste);
ListFourmi* ajout_fourmi(ListFourmi** liste, Fourmi* fourmi);
ListFourmi* retirer_fourmi(ListFourmi** liste, Fourmi* fourmi);
void compter_Liste_fourmi(ListFourmi* liste);
void liberer_liste(ListFourmi* liste);
Fourmi* trouver_fourmi(ListFourmi* liste, int id);
ListFourmi* fusionner_listes(ListFourmi* liste1, ListFourmi* liste2);
/****************************************************************************/

/****************************************************************************/
void mise_a_jour_fourmi(Fourmi* fourmi);
void nourrir_fourmi(Fourmi* fourmi);
/****************************************************************************/

/****************************************************************************/
void deplacement_fourmi(Fourmi* fourmi, Environnement* map);
void deplacement_ronde(Fourmi* fourmi, Environnement* map);
/****************************************************************************/

/****************************************************************************/
void update_day_fourmi_inventaire(Fourmi* fourmi, Environnement* map);
void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map, Temps* saison);
void update_day_liste_fourmi(ListFourmi* liste, Environnement* maps, Temps* saison);
/****************************************************************************/

/****************************************************************************/
int compter_fourmi_salle(ListFourmi* liste, int salle);
/****************************************************************************/

/****************************************************************************/
void ajuster_role_par_saison(Fourmi* fourmi, Temps* saison);
/****************************************************************************/

/****************************************************************************/
void gerer_creation_fourmis_males(ListFourmi** fourmis, Reine* reine);
void supprimer_fourmis_males(ListFourmi* fourmis);
/****************************************************************************/
void ajuster_role(Fourmi* fourmi, ListFourmi* liste, Temps* saison);

#endif

// Liste des types de fourmilles
/* 1 Fourmi coupeuse de feuilles : Atta
*/
/* 2 Fourmis des dunes : Cataglyphis
*/
// 3 Fourmis des rochers : Messor
// 4 Fourmis australienne : Camponotus
// 5 Fourmis forestières : Formica
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis
