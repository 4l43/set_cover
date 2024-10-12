#include <stdio.h>
#include <stdbool.h>

int U = 7;
int S = 6;
int A[6][7] = {
    {1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1},
    {0, 0, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1},
    {0, 1, 0, 0, 0, 0, 1}
};

bool elements_couverts[7];

void initialiser_elements_couverts() {
    for (int i = 0; i < U; i++) {
        elements_couverts[i] = false;
    }
}

int compter_elements_non_couverts(int sous_ensemble[]) {
    int compte = 0;
    for (int i = 0; i < U; i++) {
        if (sous_ensemble[i] == 1 && !elements_couverts[i]) {
            compte++;
        }
    }
    return compte;
}

void marquer_comme_couvert(int sous_ensemble[]) {
    for (int i = 0; i < U; i++) {
        if (sous_ensemble[i] == 1) {
            elements_couverts[i] = true;
        }
    }
}

void affichage_sous_ensembles(int sous_ensembles[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("Sous-ensemble %c\n", 'A' + sous_ensembles[i]);
    }
}

void algorithme_glouton() {
    initialiser_elements_couverts();
    
    bool tous_couverts = false;
    while (!tous_couverts) {
        int meilleur_index = -1;
        int meilleur_compte = -1;

        for (int i = 0; i < S; i++) {
            int compte = compter_elements_non_couverts(A[i]);
            if (compte > meilleur_compte) {
                meilleur_compte = compte;
                meilleur_index = i;
            }
        }

        if (meilleur_compte == 0) {
            break;
        }

        marquer_comme_couvert(A[meilleur_index]);
        printf("Selection du sous-ensemble %c\n", 'A' + meilleur_index);

        tous_couverts = true;
        for (int i = 0; i < U; i++) {
            if (!elements_couverts[i]) {
                tous_couverts = false;
                break;
            }
        }
    }

    if (tous_couverts) {
        printf("Tous les elements sont couverts.\n");
    } else {
        printf("Impossible de couvrir tous les elements avec les sous-ensembles donnes.\n");
    }
}

bool est_combinaison_couverte(int sous_ensembles[], int taille) {
    bool couverts[U];
    for (int i = 0; i < U; i++) {
        couverts[i] = false;
    }

    for (int i = 0; i < taille; i++) {
        int index_sous_ensemble = sous_ensembles[i];
        for (int j = 0; j < U; j++) {
            if (A[index_sous_ensemble][j] == 1) {
                couverts[j] = true;
            }
        }
    }

    for (int i = 0; i < U; i++) {
        if (!couverts[i]) {
            return false;
        }
    }
    return true;
}

void combinaisons_exactes(int sous_ensembles[], int debut, int taille, int r) {
    if (taille == r) {
        if (est_combinaison_couverte(sous_ensembles, r)) {
            printf("Combinaison optimale avec %d sous-ensembles :\n", r);
            affichage_sous_ensembles(sous_ensembles, r);
        }
        return;
    }

    for (int i = debut; i < S; i++) {
        sous_ensembles[taille] = i;
        combinaisons_exactes(sous_ensembles, i + 1, taille + 1, r);
    }
}

void algorithme_exact() {
    for (int r = 1; r <= S; r++) {
        int sous_ensembles[r];
        combinaisons_exactes(sous_ensembles, 0, 0, r);
    }
}

int main() {
    printf("Algorithme Glouton:\n");
    algorithme_glouton();
    printf("\nAlgorithme Exact:\n");
    algorithme_exact();
    return 0;
}
