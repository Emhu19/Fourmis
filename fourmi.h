#ifndef FOURMI_H
#define FOURMI_H

#include <stdbool.h>

#define MAX_CHAR 50

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

Fourmi* creationFourmi(int id, const char* espece_fourmi, const char* role_fourmi);
void afficher_fourmi(const Fourmi* fourmi);
void mise_a_jour_fourmi(Fourmi* fourmi);
void nourrir_fourmi(Fourmi* fourmi);
void deplacer_fourmi(Fourmi* fourmi, int x, int y);

#endif
