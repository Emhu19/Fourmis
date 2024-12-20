#ifndef FOURMI_H
#define FOURMI_H

#include <stdbool.h>
#include "reine.h"
#include "environnement.h"

#define MAX_CHAR 50

typedef enum {
    NOURRICE,
    EXPLORATRICE,
    SOLDAT,
    COLLECTRICE_MIELLAT
} Role;

typedef struct {
    Role role;
    char espece[MAX_CHAR];
    int id_fourmi;
    int salle;
    bool sexe;
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
Fourmi* creationFourmi(int id, int type_fourmi, bool sexe);
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
void update_day_fourmi(ListFourmi* liste ,Fourmi* fourmi, Environnement* map);
void update_day_liste_fourmi(ListFourmi* liste, Environnement* map);
int compter_fourmi_salle(ListFourmi* liste, int salle);
void ajuster_role_par_saison(Fourmi* fourmi);


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
