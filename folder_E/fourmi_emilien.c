#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_CHAR 50
#define MAX_NIVEAUX 6

typedef struct {
    char espece[MAX_CHAR];
    int id_reine;
    char role[MAX_CHAR];
    int spermatec;
    int age;
    float cgt;
    int faim;
    int eau;
    int sante;
    char maladie[MAX_CHAR];
} Reine;

typedef struct {
    char espece[MAX_CHAR];
    int id_fourmi;
    bool sexe;
    char role[MAX_CHAR];
    int age;
    int faim;
    int eau;
    bool sante;
    char maladie[MAX_CHAR];
    float cgt;
    int coord_x;
    int coord_y;
} Fourmi;

typedef struct ListFourmis{
    Fourmi *fourmi; //je suppose une structure ant on pourra changer le nom en fonction de ce qu'emilien fait
    struct ListFourmis *suivant;
    struct ListFourmis *precedent; //liste doublement chainée car on peut avoir besoin de revenir a la fourmis précedente
}ListFourmis;

Fourmi* creationFourmi(int id, char* espece_fourmi, char* role_fourmi) {
    Fourmi* nouvelle_fourmi = (Fourmi*)malloc(sizeof(Fourmi));
    if (nouvelle_fourmi == NULL) {
        perror("Erreur d'allocation mémoire pour la reine");
        return NULL;
    }

    strcpy(nouvelle_fourmi->espece, espece_fourmi);
    nouvelle_fourmi->id_fourmi = id;
    strcpy(nouvelle_fourmi->role, role_fourmi);
    nouvelle_fourmi->age = 1;
    nouvelle_fourmi->sexe = true;
    nouvelle_fourmi->cgt = 0.00f;
    nouvelle_fourmi->faim = 0;
    nouvelle_fourmi->eau = 0;
    nouvelle_fourmi->sante = 1;
    strcpy(nouvelle_fourmi->maladie, "Rien");
    nouvelle_fourmi->coord_x = 25;
    nouvelle_fourmi->coord_y = 25;
    return nouvelle_fourmi;
}

void afficher_fourmi(Fourmi* fourmi) {
    if (fourmi == NULL) return;
    printf("\n--- Fourmi %d ---\n", fourmi->id_fourmi);
    printf("Espèce : %s\n", fourmi->espece);
    printf("Âge : %d\n", fourmi->age);
    printf("Faim : %d\n", fourmi->faim);
    printf("Eau : %d\n", fourmi->eau);
    printf("Santé : %s\n", fourmi->sante ? "En bonne santé" : "Morte");
    printf("Maladie : %s\n", fourmi->maladie);
    printf("Coordonnées : (%d, %d)\n", fourmi->coord_x, fourmi->coord_y);
}

typedef struct ListReines{
    Reine *reine;
    struct ListReines *suivant;
    struct ListReines *precedent;
}ListReines;

Reine* creationReine(int id, char* espece) {
    Reine* nouvelle_reine = (Reine*)malloc(sizeof(Reine));
    if (nouvelle_reine == NULL) {
        perror("Erreur d'allocation mémoire pour la reine");
        return NULL;
    }

    strcpy(nouvelle_reine->espece, espece);
    nouvelle_reine->id_reine = id;
    strcpy(nouvelle_reine->role, "Reine");
    nouvelle_reine->spermatec = 1;
    nouvelle_reine->age = 1;
    nouvelle_reine->cgt = 0.00f;
    nouvelle_reine->faim = 0;
    nouvelle_reine->eau = 0;
    nouvelle_reine->sante = 1;
    strcpy(nouvelle_reine->maladie, "Rien");

    return nouvelle_reine;
}

void afficher_Reine(Reine* reine){

//     printf("Reine créée avec succès :\n");
    printf("Espèce : %s\n", reine->espece);
    printf("ID : %d\n", reine->id_reine);
    printf("Rôle : %s\n", reine->role);
    printf("Spermatec : %d\n", reine->spermatec);
    printf("Âge : %d\n", reine->age);
    printf("Faim : %d\n", reine->faim);
    printf("Eau : %d\n", reine->eau);
    printf("Santé : %d\n", reine->sante);
    printf("Maladie : %s\n", reine->maladie);
}

void clear_terminal() {
    printf("\033[H\033[J");
}

void afficher_titre(const char *titre) {
    printf("\n\033[1;34m===== %s =====\033[0m\n\n", titre);
}

void afficher_salle_simple(const char *nom) {
    printf("+-----------------+\n");
    printf("|                 |\n");
    printf("|     %-10s  |\n", nom);
    printf("|                 |\n");
    printf("+-----------------+\n");
}

void afficher_salle_simple_milieu(const char *nom) {
   printf("                            +-----------------+\n");
    printf("                            |                 |\n");
    printf("                            |     %-10s  |\n", nom);
    printf("                            |                 |\n");
    printf("                            +-----------------+\n");
}

void afficher_connexion_simple() {
    printf("        |\n");
}

void afficher_connexion_simple_milieu() {
    printf("                                  |\n");
}

void afficher_connexion_double() {
    printf("        |                            |\n");
}

void afficher_salles_alignees(const char *nom1, const char *nom2) {
    printf("+-----------------+         +-----------------+\n");
    printf("|                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |\n", nom1, nom2);
    printf("|                 |         |                 |\n");
    printf("+-----------------+         +-----------------+\n");
}

void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3) {
    printf("+-----------------+         +-----------------+         +-----------------+\n");
    printf("|                 |         |                 |         |                 |\n");
    printf("|     %-10s  |----+----|     %-10s  |----+----|     %-10s  |\n", nom1, nom2, nom3);
    printf("|                 |         |                 |         |                 |\n");
    printf("+-----------------+         +-----------------+         +-----------------+\n");
}

void afficher_fourmiliere_niveau(int niveau) {
    switch (niveau) {
        case 1:
            afficher_salles_alignees("R", "N");
            break;
        case 2:
            afficher_salles_alignees("R", "N");
            afficher_connexion_simple();
            afficher_salle_simple("L");
            break;
        case 3:
            afficher_salles_alignees("R", "N");
            afficher_connexion_double();
            afficher_salles_alignees("L", "R");
            break;
        case 4:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees("L", "R");
            break;
        case 5:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees_3("L", "R", "R");
            break;
        case 6:
            afficher_salle_simple("R");
            afficher_connexion_simple();
            afficher_salles_alignees_3("L", "R", "R");
            afficher_connexion_simple_milieu();
            afficher_salle_simple_milieu("L");
            break;
        default:
            printf("Niveau %d non pris en charge.\n", niveau);
            break;
    }
}

void afficher_legende() {
    printf("\n\033[1;33mLégende :\033[0m\n");
    printf("Reine : Salle de la reine\n");
    printf("Nourriture : Stockage de nourriture\n");
    printf("Larves : Salle des larves\n");
    printf("Ressources : Stockage de ressources\n");
}

void afficher_fourmiliere(int niveau) {
    clear_terminal();
    afficher_titre("Fourmilière");
    afficher_fourmiliere_niveau(niveau);
    afficher_legende();
    printf("\n\033[1;32mAppuyez sur Entrée pour continuer...\033[0m\n");
    getchar();
}

void mise_a_jour_fourmi(Fourmi* fourmi) {
    if (fourmi == NULL) return;

    fourmi->age++;
    fourmi->faim += 5;
    fourmi->eau -= 1;

    if (fourmi->faim > 100 || fourmi->eau <= 0) {
        fourmi->sante = 0;
        strcpy(fourmi->maladie, "Mort");
    } else if (fourmi->faim > 70) {
        strcpy(fourmi->maladie, "Sous-alimentation");
    }
}

void nourrir_fourmi(Fourmi* fourmi) {
    if (fourmi == NULL) return;
    fourmi->faim -= 30;
    if (fourmi->faim < 0) fourmi->faim = 0;
    strcpy(fourmi->maladie, "Rien");
}

void deplacer_fourmi(Fourmi* fourmi, int x, int y) {
    if (fourmi == NULL) return;
    fourmi->coord_x = x;
    fourmi->coord_y = y;
    printf("Fourmi %d déplacée à (%d, %d).\n", fourmi->id_fourmi, x, y);
}

ListFourmis* ajouter_fourmi(ListFourmis* liste, Fourmi* fourmi) {
    ListFourmis* nouvel_element = (ListFourmis*)malloc(sizeof(ListFourmis));
    if (nouvel_element == NULL) {
        perror("Erreur d'allocation pour la liste des fourmis");
        return liste;
    }
    nouvel_element->fourmi = fourmi;
    nouvel_element->suivant = liste;
    nouvel_element->precedent = NULL;
    if (liste != NULL) {
        liste->precedent = nouvel_element;
    }
    return nouvel_element;
}

void cycle_de_vie(ListFourmis* liste) {
    ListFourmis* courant = liste;
    while (courant != NULL) {
        mise_a_jour_fourmi(courant->fourmi);
        afficher_fourmi(courant->fourmi);
        courant = courant->suivant;
    }
}

ListFourmis* supprimer_fourmi(ListFourmis* liste, Fourmi* fourmi) {
    ListFourmis* courant = liste;
    while (courant != NULL) {
        if (courant->fourmi == fourmi) {
            if (courant->precedent) {
                courant->precedent->suivant = courant->suivant;
            }
            if (courant->suivant) {
                courant->suivant->precedent = courant->precedent;
            }
            if (courant == liste) {
                liste = courant->suivant;
            }
            free(courant);
            break;
        }
        courant = courant->suivant;
    }
    return liste;
}

int main() {
    Reine* reine = creationReine(1, "Formica");
    if (reine != NULL) {
        afficher_Reine(reine);
    }

    ListFourmis* liste_fourmis = NULL;
    Fourmi* fourmi1 = creationFourmi(1, "Formica", "Ouvrière");
    Fourmi* fourmi2 = creationFourmi(2, "Formica", "Soldat");

    liste_fourmis = ajouter_fourmi(liste_fourmis, fourmi1);
    liste_fourmis = ajouter_fourmi(liste_fourmis, fourmi2);

    for (int jour = 1; jour <= 5; jour++) {
        printf("\n--- Jour %d ---\n", jour);
        cycle_de_vie(liste_fourmis);

        nourrir_fourmi(fourmi1);
        nourrir_fourmi(fourmi2);
    }

    free(reine);
    while (liste_fourmis != NULL) {
        Fourmi* a_supprimer = liste_fourmis->fourmi;
        liste_fourmis = supprimer_fourmi(liste_fourmis, a_supprimer);
        free(a_supprimer);
    }

    return 0;
}
