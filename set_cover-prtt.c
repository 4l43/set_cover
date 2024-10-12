#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int U, S;  // Déclaration des tailles de U et S
int **A;
bool *union_couverts;

void tab_union() {
    for (int i = 0; i < U; i++) {
        union_couverts[i] = false;
    }
}

void afficher(int sous_ensembles[], int taille) {
    printf("La sous-collection : {");
    for (int i = 0; i < taille; i++) {
        printf("%c", 'A' + sous_ensembles[i]);
        if (i < taille - 1) {
            printf(",");
        }
    }
    printf("} est la couverture optimale\n");
}

void couver(int sous_ensemble[]) {
    for (int i = 0; i < U; i++) {
        if (sous_ensemble[i] == 1) {
            union_couverts[i] = true;
        }
    }
}

// Algorithme glouton
void algorithme_glouton() {
    tab_union();
    
    bool fin = false;
    int sous_ensembles_selectionnes[6]; // Taille maximum pour les sous-ensembles
    int taille_selection = 0;

    while (!fin) {
        int meilleur_index = -1;
        int meilleur_cmt = -1;

        for (int i = 0; i < S; i++) {
            int cmt = 0;
            for (int j = 0; j < U; j++) {
                if (A[i][j] == 1 && union_couverts[j] == false) {
                    cmt++;
                }
            }
            if (cmt > meilleur_cmt) {
                meilleur_cmt = cmt;
                meilleur_index = i;
            }
        }

        if (meilleur_cmt == 0) {
            fin = true;
        } else {
            couver(A[meilleur_index]);
            sous_ensembles_selectionnes[taille_selection] = meilleur_index;
            taille_selection++;
        }
    }

    if (taille_selection > 0) {
        afficher(sous_ensembles_selectionnes, taille_selection);
    } else {
        printf("Impossible de couvrir tous les éléments avec les sous-ensembles donnés.\n");
    }
}

// Fonction pour vérifier si tous les éléments sont couverts
bool fin(int sous_ensembles[], int taille) {
    tab_union();
    
    for (int i = 0; i < taille; i++) {
        couver(A[sous_ensembles[i]]);
    }

    for (int i = 0; i < U; i++) {
        if (union_couverts[i] == false) {
            return false;
        }
    }
    return true;
}

// Algorithme exact récursif
void algo_exact_recursif(int sous_ensembles[], int debut, int taille, int l) {
    if (taille == l) {
        if (fin(sous_ensembles, l)) {
            afficher(sous_ensembles, l);
        }
        return;
    }

    for (int i = debut; i < S; i++) {
        sous_ensembles[taille] = i;
        algo_exact_recursif(sous_ensembles, i + 1, taille + 1, l);
    }
}

// Algorithme exact
void algo_exact() {
    for (int l = 1; l <= S; l++) {
        int sous_ensembles[l];
        algo_exact_recursif(sous_ensembles, 0, 0, l);
    }
}

int main() {
    printf("Entrez la taille de l'ensemble U (nombre d'éléments) : ");
    scanf("%d", &U);
    printf("Entrez le nombre de sous-ensembles S : ");
    scanf("%d", &S);

    A = (int **)malloc(S * sizeof(int *));
    for (int i = 0; i < S; i++) {
        A[i] = (int *)malloc(U * sizeof(int));
    }

    printf("Entrez les sous-ensembles (0 ou 1) :\n");
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < U; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    union_couverts = (bool *)malloc(U * sizeof(bool));

    printf("Algorithme Exact :\n");
    algo_exact();

    printf("\nAlgorithme Glouton :\n");
    algorithme_glouton();

    for (int i = 0; i < S; i++) {
        free(A[i]);
    }
    free(A);
    free(union_couverts);

    return 0;
}
