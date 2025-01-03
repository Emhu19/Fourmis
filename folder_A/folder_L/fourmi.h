#ifndef FOURMI_H
#define FOURMI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reine.h"
#include "environnement.h"
#include "fourmi.h"

typedef struct ListMaladie ListMaladie;

typedef struct{
    char *typeMaladie;
    int id;
    int faim;
    int soif;
}Maladie;

struct ListMaladie{
    Maladie maladie;
    ListMaladie *suivant;
};


#define BASE_COOR_X 12
#define BASE_COOR_Y 12
#define MAX_CHAR 50

typedef enum {
    NOURRICE,
    EXPLORATRICE,
    SOLDAT,
    COLLECTRICE_MIELLAT
} Role;

typedef struct {
    Role role;
    int espece;
    int id_fourmi;
    int salle;
    bool sexe;
    int age;
    int faim;
    int eau;
    int besoin_faim;
    int besoin_eau;
    bool sante;
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
/****************************************************************************/

/****************************************************************************/
void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map);
void update_day_liste_fourmi(ListFourmi* liste, Environnement* map);
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

#endif

// Liste des types de fourmilles
/* 1 Fourmi coupeuse de feuilles : Atta
        1 Reine fondatrice de champignon
        2 Ouvrière transporteur de feuilles
        3 Soldat protecteur des colonnes
        4 Ouvrière nettoyeuse des champignons
        5 Ouvrière mineure pour le jardinage de champignons
*/
/* 2 Fourmis des dunes : Cataglyphis
    Exploratrice de chaleur extrême
    Messagère rapide
    Chercheuse d’ombre
    Ouvrière éclaireuse
    Reine migratrice
    Fourmi stérile pour fouille des sables
*/
// 3 Fourmis des rochers : Messor
// 4 Fourmis amazoniennes : Eciton
// 5 Fourmis forestières : Formica
    // Ouvrière constructrice de nids en bois ou aiguilles
        // Exploratrice forestière
        // Soldat défensif avec acide formique
        // Transporteur de petits insectes
        //Reine des sous-bois
        // Collectrice de miellat des pucerons
// 6 Fourmis du désert : Pogonomyrmex
// 7 Fourmis cultivatrices de champignons : Acromyrmex
// 8 Fourmis nageuses : Polyrhachis
