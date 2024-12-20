#include "fourmiliere.h"
#include <stdio.h>
#include <unistd.h>

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
        case 1: afficher_salles_alignees("R", "N"); break;
        case 2: afficher_salles_alignees("R", "N"); afficher_connexion_simple(); afficher_salle_simple("L"); break;
        case 3: afficher_salles_alignees("R", "N"); afficher_connexion_double(); afficher_salles_alignees("L", "R"); break;
        case 4: afficher_salle_simple("R"); afficher_connexion_simple(); afficher_salles_alignees("L", "R"); break;
        case 5: afficher_salle_simple("R"); afficher_connexion_simple(); afficher_salles_alignees_3("L", "R", "R"); break;
        case 6: afficher_salle_simple("R"); afficher_connexion_simple(); afficher_salles_alignees_3("L", "R", "R"); afficher_connexion_simple_milieu(); afficher_salle_simple_milieu("L"); break;
        default: printf("Niveau %d non pris en charge.\n", niveau); break;
    }
}

int salle_reine(Reine* reine) {
    return reine->salle == 1;
}

void afficher_legende(ListFourmi* liste, Reine* reine) {
    printf("\n\033[1;33mLégende :\033[0m\n");
    printf("Reine : Salle de la reine (%d/1)\n", salle_reine(reine));
    printf("Nourriture : Stockage de nourriture(0/120)\n");
    printf("Larves : Salle des larves(%d/125)\n", compter_fourmi_salle(liste, 2));
    printf("Ressources : Stockage de ressources(0/100)\n");
    printf("Exterieur : (%d)\n", compter_fourmi_salle(liste, 0));
}

void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine) {
    clear_terminal();
    afficher_titre("Fourmilière");
    afficher_fourmiliere_niveau(niveau);
    afficher_legende(liste, reine);
    compter_Liste_fourmi(liste);
    usleep(500000);
}
