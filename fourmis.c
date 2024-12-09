#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Reine{
	char espece[50];
	int id_reine;
	char role[50];
	int spermatec;
	int age;
	float cgt;
	int faim;
	int eau;
	int sante;
	char maladie[30];
} Reine;

typedef struct Fourmis{
	char espece[50];
	int id_fourmis;
	bool sexe;
	char role[50];
// 	ce qu elle porte
	int age;
	int faim;
	int eau;
	bool sante;
	char maladie[50];
// 	information, location bouffe
	float cgt;
	int coordonnée_x;
    int coordonnée_y;
}Fourmis;

typedef struct Meteo {
    float temperature_moyenne;
    float variation_temperature;
    float temperature;     // Température actuelle
    int precipitation;            // Niveau de précipitation
} Meteo;

// Structure pour les prédateurs
typedef struct Predateurs {
    int id_predateur;
    char nom_predateur[50];
    int coordonnée_x;
    int coordonnée_y;
    int santé;
    int vitesse;
    int force;  // le degat qu'il fait
}Predateurs;

// Structure pour l'environnement
typedef struct Environnement {
    char biome[50];               // Biome (ex: espace, forêt, désert, etc.)
    //Liste_chainee chunks[100][100];

}Environnement;

typedef struct Chunk {
    int quantite_nourriture;
    int quantite_materiaux;
    int quantite_eau;
    char type[50]; //rivière, flaque d'eau, sable, fourmilière ...
}Chunk;

// Structure pour le temps
typedef struct Temps {
    int saison;
    int mois;
    int jour;
} Temps;


Environnement genererEnvironnement(){}
    //permet de générer l'environnement en fonction des préférences de l'utilisateur (avec une part d'aléatoire) génération procédurale


void incr_temp(Temps* t){}
//fait avancer le temps



//  Temps init_temps(){
// // 	 return;
// }
    //initialise le temps

void maj_meteo(Meteo m, Environnement e, Temps t){}
    //met à jour la meteo en fonction des informations contenus dans Meteo, en fonction du biome dans Environnement, et du temps Temps(mois,saison...)

void maj_environnement(Meteo m, Environnement e, Temps t){}
    //met a jour l'envuronnement en fonction de la météo, du temps (par exemple s'il pleut, les chunks vont se remplir d'eau)


void maj_predateur(Predateurs p, Environnement e, Temps t /*Liste_fourmilière fl */ ){}
    //met a jour les infos du predateur (position, dort ou pas, traverse la rivière ou pas etc...), et gère les combats avec les fourmis s'ils se rencontrent

void clear_termial() {

	for(int i = 0; i < 50; i++){
		printf("\n");
	}
}

void afficherFourmiliereNiveau1() {
    // Salles et tunnels en ASCII
    printf("    +-----------------+         +-----------------+\n");
    printf("    |                 |         |                 |\n");
	printf("    |         A       |----+----|         B       |\n");
	printf("    |                 |         |                 |\n");
    printf("    +-----------------+         +-----------------+\n");

}

void afficherFourmiliereNiveau2() {

    printf("    +-----------------+         +-----------------+\n");
    printf("    |                 |         |                 |\n");
	printf("    |         A       |----+----|         B       |\n");
	printf("    |                 |         |                 |\n");
    printf("    +-----------------+         +-----------------+\n");
    printf("        |                               |\n");
    printf("    +-----+                             |\n");
    printf("    |  C  |-----------------------------+\n");
    printf("    +-----+\n");

}

void afficherFourmiliereNiveau3() {

    printf("    +-----------------+         +-----------------+         +-----------------+ \n");
    printf("    |                 |         |                 |         |                 |\n");
	printf("    |         A       |----+----|         B       |----+----|         D       |\n");
	printf("    |                 |         |                 |         |                 |\n");
    printf("    +-----------------+         +-----------------+         +-----------------+\n");
    printf("        |                               |\n");
    printf("    +-----+                             |\n");
    printf("    |  C  |-----------------------------+\n");
    printf("    +-----+\n");

}

void afficherFourmiliereNiveau4() {

    printf("    +-----------------+         +-----------------+         +-----------------+ \n");
    printf("    |                 |         |                 |         |                 |\n");
	printf("    |         A       |----+----|         B       |----+----|         D       |\n");
	printf("    |                 |         |                 |         |                 |\n");
    printf("    +-----------------+         +-----------------+         +-----------------+\n");
    printf("        |                               |                         |\n");
    printf("    +-----+                             |                         |\n");
    printf("    |  C  |-----------------------------+                         |\n");
    printf("    +-----+                                                       |\n");
	printf("        |                                                         |        +-----+\n");
	printf("        |---------------------------------------------------------+--------|  E  |\n");
	printf("                                                                           +-----+\n");
}

void afficherRessources(){
	int nbFourmis = 12;
	int  nbFourmisMax = 40;
	printf("\n\nLégende :\n");
    printf("A : Salle de la reine (%d/%d)\n", nbFourmis, nbFourmisMax);
    printf("B : Stockage de nourriture(plantes : 6/10)\n");
    printf("C : Salle des larves\n");
	printf("D : Stockage de ressource\n");
}

void afficherFourmiliere(int niveau) {

    printf("\n====================================================================================================== Fourmilière ======================================================================================================\n\n");

    // Salles et tunnels en ASCII
	if(niveau == 1){
		afficherFourmiliereNiveau1();
	}
	else if(niveau == 2){
		afficherFourmiliereNiveau2();
	}
	else if(niveau == 3){
		afficherFourmiliereNiveau3();
	}
	else if(niveau == 4){
		afficherFourmiliereNiveau4();
	}
	afficherRessources();

	printf("\n====================================================================================================== Fin Fourmilière ======================================================================================================\n\n\n\n\n");
}

void afficher(){
	for(int i = 1; i < 5; i++)
		afficherFourmiliere(i);
}

int main(){
// 	printf("Go virer Amaury\n");
// 	printf("Hello la team\n");
// 	printf("Faut faire du racisme discretement\n");

	int nourriture = 26;
	int nbFourmis = 42;

	afficher();
// 	 sleep(3);

	return 0;
}
