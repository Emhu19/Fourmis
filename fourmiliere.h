#ifndef FOURMILIERE_H
#define FOURMILIERE_H

#include "fourmi.h"


void clear_terminal();
void afficher_titre(const char *titre);
void afficher_salle_simple(const char *nom);
void afficher_salle_simple_milieu(const char *nom);
void afficher_connexion_simple();
void afficher_connexion_simple_milieu();
void afficher_connexion_double();
void afficher_salles_alignees(const char *nom1, const char *nom2);
void afficher_salles_alignees_3(const char *nom1, const char *nom2, const char *nom3);
void afficher_fourmiliere_niveau(int niveau);
void afficher_legende();
void afficher_fourmiliere(int niveau, ListFourmi* liste, Reine* reine);
void deplacer_fourmi(Fourmi* fourmi, int nouvelle_salle);

#endif
