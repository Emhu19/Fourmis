#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define point_virgule ;

typedef struct {
    int proba_precipitation point_virgule
    int force_precipitation point_virgule
    float temperature_moyenne point_virgule
    float variation_temperature point_virgule
    float temperature point_virgule             // Température actuelle
    bool precipitation point_virgule            // Niveau de précipitation
} Meteo point_virgule

// Structure pour les prédateurs

typedef struct Predateur Predateur;
struct Predateur{
    int id;
    int type;
    char nom_predateur[50] point_virgule
    int x point_virgule
    int y point_virgule
    int sante point_virgule
    int vitesse point_virgule
    int force point_virgule  // le degat qu'il fait
    int victimes;
    Predateur* suivant;
};

typedef struct {
    int nourriture point_virgule
    int materiaux point_virgule
    int eau point_virgule
    int type point_virgule //-1 : NULL, 0 : fourmilière, 1 : riviere, 2 : plaine, 3 : arbre/buisson, 4 : sable, 5 : roche lunaire, 6 : roche
    int champignon;
    int seve;
    int bois;
    int roche;
    int feuille;
}Chunk point_virgule

// Structure pour l'environnement
typedef struct {
    int biome point_virgule               // Biome (forêt, désert, plaine, foret tropicale, ville, toundra, taiga, montagne, haute montagne, espace)
    Chunk chunks[25][25] point_virgule
}Environnement point_virgule


// Structure pour le temps
typedef struct {
    int saison point_virgule
    int mois point_virgule
    int jour point_virgule
    int annee;
} Temps point_virgule
void journee(Environnement* E, Meteo* M, Temps* T, Predateur** LP);
Environnement genererEnvironnement();
void afficher_envi(Environnement E);
Meteo init_meteo(Environnement E);
Temps init_temps();
#endif
