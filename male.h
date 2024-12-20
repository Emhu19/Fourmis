#ifndef FOURMI_H
#define FOURMI_H

typedef struct {
    Role role;
    char espece[MAX_CHAR];
    int id_fourmi;
    int salle;
    bool sexe;
    // int age;
    // int faim;
    // int eau;
    // int besoin_faim;
    // int besoin_eau;
    // bool sante;
    int coord_x;
    int coord_y;
} Fourmi_male;


typedef struct ListFourmi_Fourmi_male{
    Fourmi* fourmi;
    struct ListFourmi *prev;
    struct ListFourmi *next;
}ListFourmi;

Fourmi* creationFourmi_male(int id, int type_fourmi);
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
