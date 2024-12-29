#include "fourmi.h"
#include "time.h"

void gerer_creation_fourmis_males(ListFourmi** fourmis, Reine* reine) {
    if (reine->royale) {
        for (int j = 0; j < 10; j++) {
            Fourmi* fourmi_male = creationFourmi(2000, reine->type, false);
            *fourmis = ajout_fourmi(fourmis, fourmi_male);
        }
    } else if (rand() % 100 == 19) {
        reine->royale = true;
    }
}

void supprimer_fourmis_males(ListFourmi* fourmis) {
    Fourmi* fourmi_male_supp = trouver_fourmi(fourmis, 2000);
    if (fourmi_male_supp) {
        retirer_fourmi(&fourmis, fourmi_male_supp);
    }
}
