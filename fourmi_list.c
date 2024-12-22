#include "fourmi.h"

ListFourmi* Initialisation_List() {
    ListFourmi* newList = (ListFourmi*)malloc(sizeof(ListFourmi));
    if (!newList) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    newList->fourmi = NULL;
    newList->prev = NULL;
    newList->next = NULL;
    return newList;
}

ListFourmi* ajout_fourmi(ListFourmi** liste, Fourmi* fourmi) {
    if (!liste || !fourmi) return NULL;

    ListFourmi* newList = (ListFourmi*)malloc(sizeof(ListFourmi));
    if (!newList) {
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }

    newList->fourmi = fourmi;
    newList->prev = NULL;
    newList->next = *liste;

    if (*liste) {
        (*liste)->prev = newList;
    }
    *liste = newList;
    return newList;
}

void afficher_Liste_fourmi(ListFourmi* liste) {
    if (!liste) {
        printf("Liste vide\n");
        return;
    }
    ListFourmi* current = liste;
    while (current) {
        afficher_fourmi(current->fourmi);
        current = current->next;
    }
}

void compter_Liste_fourmi(ListFourmi* liste) {
    if (!liste) {
        printf("Liste vide\n");
        return;
    }
    int count = 0;
    ListFourmi* current = liste;
    while (current) {
        count++;
        current = current->next;
    }
    printf("Il y a %d fourmis dans la fourmilière\n", count);
}

int compter_fourmi_salle(ListFourmi* liste, int salle) {
    if (!liste) {
        printf("Liste vide\n");
        return 0;
    }
    int count = 0;
    ListFourmi* current = liste;
    while (current) {
        if (current->fourmi->salle == salle) {
            count++;
        }
        current = current->next;
    }
    return count;
}

ListFourmi* retirer_fourmi(ListFourmi** liste, Fourmi* fourmi) {
    if (!liste || !*liste || !fourmi) return *liste;

    ListFourmi* current = *liste;
    while (current && current->fourmi != fourmi) {
        current = current->next;
    }

    if (!current) {
        fprintf(stderr, "Erreur : fourmi non trouvée.\n");
        return *liste;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        *liste = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }

    free(current);
    return *liste;
}

void liberer_liste(ListFourmi* liste) {
    ListFourmi* current = liste;
    while (current) {
        ListFourmi* next = current->next;
        free(current->fourmi);
        free(current);
        current = next;
    }
}

Fourmi* trouver_fourmi(ListFourmi* liste, int id) {
    ListFourmi* current = liste;
    if (current == NULL) {
    return NULL;
}
    while (current) {
        if (current->fourmi == NULL) {
            return NULL;
        }
        if (current->fourmi->id_fourmi == id) {
            return current->fourmi;
        }
        current = current->next;
    }
    return NULL;
}

ListFourmi* fusionner_listes(ListFourmi* liste1, ListFourmi* liste2) {
    if (!liste1) return liste2;
    if (!liste2) return liste1;

    ListFourmi* current = liste1;
    while (current->next) {
        current = current->next;
    }

    current->next = liste2;
    if (liste2) {
        liste2->prev = current;
    }

    return liste1;
}
