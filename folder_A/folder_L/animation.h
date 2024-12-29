#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 42
#define ANIMATION_STEPS 55

void afficherArray(const char *array[], int size);
void afficher_fourmi_animation(int position);
void afficherMenu_Fourmiliere();
void afficherMenu_Carte();
void afficher_logo();
int affichage_animation_debut();
void logo_1();
int logo_2();
int logo_3();
#endif
