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
    for (int niveau = 1; niveau <= MAX_NIVEAUX; niveau++) {
        afficher_fourmiliere(niveau);
    }

    return 0;
}
