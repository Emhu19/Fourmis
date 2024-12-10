#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHAR_SALLE_NOM 50
#define MAX_CHAR_ROLE 50
#define MAX_CHAR_MALADIE 50

typedef struct {
    char espece[MAX_CHAR_SALLE_NOM];
    int id_reine;
    char role[MAX_CHAR_ROLE];
    int spermatec;
    int age;
    float cgt;
    int faim;
    int eau;
    int sante;
    char maladie[MAX_CHAR_MALADIE];
} Reine;

typedef struct {
    char espece[MAX_CHAR_SALLE_NOM];
    int id_fourmi;
    bool sexe;
    char role[MAX_CHAR_ROLE];
    int age;
    int faim;
    int eau;
    bool sante;
    char maladie[MAX_CHAR_MALADIE];
    float cgt;
    int coord_x;
    int coord_y;
} Fourmi;

typedef struct {
    float temperature_moyenne;
    float variation_temperature;
    float temperature;
    int precipitation;
} Meteo;

typedef struct {
    int id_predateur;
    char nom[MAX_CHAR_SALLE_NOM];
    int coord_x;
    int coord_y;
    int sante;
    int vitesse;
    int force;
} Predateur;

typedef struct {
    char biome[MAX_CHAR_SALLE_NOM];
} Environnement;

typedef struct {
    int saison;
    int mois;
    int jour;
} Temps;

typedef struct {
    char type[MAX_CHAR_SALLE_NOM];
    int nourriture;
    int materiaux;
    int eau;
} Chunk;

void clear_terminal() {
    printf("\033[H\033[J");
}

void afficher_titre(const char *titre) {
    printf("\n===== %s =====\n", titre);
}

void afficher_salle(const char *nom, const char *connexions) {
    printf("    +-----------------+\n");
    printf("    |                 |\n");
    printf("    |     %3s         |\n", nom);
    printf("    |                 |\n");
    printf("    +-----------------+\n");
    if (connexions) {
        printf("        |%s\n", connexions);
    }
}

void afficher_fourmiliere_niveau(int niveau) {
    switch (niveau) {
        case 1:
            afficher_salle("A", NULL);
            afficher_salle("B", NULL);
            break;
        case 2:
            afficher_salle("A", "|");
            afficher_salle("C", NULL);
            afficher_salle("B", NULL);
            break;
        case 3:
            afficher_salle("A", "|");
            afficher_salle("C", "|");
            afficher_salle("B", NULL);
            afficher_salle("D", NULL);
            break;
        default:
            printf("Niveau non pris en charge.\n");
            break;
    }
}

void afficher_legende() {
    printf("\nLégende :\n");
    printf("A : Salle de la reine\n");
    printf("B : Stockage de nourriture\n");
    printf("C : Salle des larves\n");
    printf("D : Stockage de ressources\n");
}

void afficher_fourmiliere(int niveau) {
    clear_terminal();
    afficher_titre("Fourmilière");
    afficher_fourmiliere_niveau(niveau);
    afficher_legende();
}

int main() {
    for (int niveau = 1; niveau <= 3; niveau++) {
        afficher_fourmiliere(niveau);
        sleep(2);
    }
    return 0;
}
