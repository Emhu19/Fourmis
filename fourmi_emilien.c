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

int main() {
//     for (int niveau = 1; niveau <= MAX_NIVEAUX; niveau++) {
//         afficher_fourmiliere(niveau);
//     }
    afficher_fourmiliere(1);

    Reine* reine = creationReine(1, "Libre");
    if (reine != NULL) {
        printf("Reine créée avec succès :\n");
        printf("Espèce : %s\n", reine->espece);
        printf("ID : %d\n", reine->id_reine);
        printf("Rôle : %s\n", reine->role);
        printf("Spermatec : %d\n", reine->spermatec);
        printf("Âge : %d\n", reine->age);
        printf("Faim : %d\n", reine->faim);
        printf("Eau : %d\n", reine->eau);
        printf("Santé : %d\n", reine->sante);
        printf("Maladie : %s\n", reine->maladie);

        free(reine);
    } else {
        printf("Erreur lors de la création de la reine.\n");
    }
    return 0;
}

