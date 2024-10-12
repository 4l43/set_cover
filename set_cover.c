#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int U = 7;
int S = 6;
int **A;
bool *union;

void tab_union() {
    for (int i = 0; i < U; i++) {
        union[i] = false;
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
            union[i] = true;
        }
    }
}

//2.2 : 
void algorithme_glouton() {
    tab_union();
    
    bool fin = false;
    int sous_ensembles_selectionnes[6];
    int taille_selection = 0;

    while (fin == false) {
        int meilleur_index = -1;
        int meilleur_cmt = -1;

        for (int i = 0; i < S; i++) {
            int cmt = 0;
            for (int j = 0; j < U; j++) {
                if (A[i][j] == 1 && union[j] == false) {
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
        printf("Impossible de couvrir tous les elements avec les sous-ensembles donnes.\n");
    }
}


//revoire : 
bool fin(int sous_ensembles[], int taille) {
    tab_union();
    
    for (int i = 0; i < taille; i++) {
        couver(A[sous_ensembles[i]]);
    }

    for (int i = 0; i < U; i++) {
        if (union[i] == false) {
            return false;
        }
    }
    return true;
}


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

void algo_exact() {
    for (int l = 1; l <= S; l++) {
        int sous_ensembles[l];
        algo_exact_recursif(sous_ensembles, 0, 0, l);
    }
}

int main() {
    A = (int **)malloc(S * sizeof(int *));
    for (int i = 0; i < S; i++) {
        A[i] = (int *)malloc(U * sizeof(int));
    }

    int temp[6][7] = {
        {1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 1}
    };
                //||
                //V
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < U; j++) {
            A[i][j] = temp[i][j];
        }
    }

    union = (bool *)malloc(U * sizeof(bool));

    printf("Algorithme Exact :\n");
    algo_exact();

    printf("\nAlgorithme Glouton :\n");
    algorithme_glouton();

    for (int i = 0; i < S; i++) {
        free(A[i]);
    }
    free(A);
    free(union);

    return 0;
}
