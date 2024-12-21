#include "fourmi.h"

void ajuster_role_par_saison(Fourmi* fourmi, Temps* saison) {

        if(saison->mois == 0){
            if (fourmi->role == COLLECTRICE_MIELLAT) {
                fourmi->role = NOURRICE;
            }
        }
        if(saison->mois == 1){
            if (fourmi->role == NOURRICE) {
                fourmi->role = EXPLORATRICE;
            }
        }
        if(saison->mois == 2){
            if (fourmi->role == NOURRICE) {
                fourmi->role = COLLECTRICE_MIELLAT;
            }
        }
        if(saison->mois == 3){
            if (fourmi->role == COLLECTRICE_MIELLAT) {
                fourmi->role = SOLDAT;
            }
        }
}
