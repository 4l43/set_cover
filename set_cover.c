#include <stdio.h>
#include <stdbool.h>

int U = 7;  // Taille de l'ensemble U
int S = 6;  // Nombre de sous-ensembles
char c[] = "1001001 1001000 0001101 0010110 0110011 0100001";
int tab[6][7];  // Tableau pour les sous-ensembles

bool solution_found = false;  // Variable pour indiquer si une solution a été trouvée

// Fonction pour vérifier si une combinaison de sous-ensembles couvre tout U
bool is_combination_covered(int subsets[], int size) {
    bool covered[U];
    for (int i = 0; i < U; i++) {
        covered[i] = false;  // Initialiser tout comme non couvert
    }

    // Marquer les éléments couverts par les sous-ensembles de la combinaison
    for (int i = 0; i < size; i++) {
        int subset_index = subsets[i];
        for (int j = 0; j < U; j++) {
            if (tab[subset_index][j] == 1) {
                covered[j] = true;
            }
        }
    }

    // Vérifier si tous les éléments de U sont couverts
    for (int i = 0; i < U; i++) {
        if (!covered[i]) {
            return false;
        }
    }
    return true;
}

// Fonction pour générer toutes les combinaisons de taille 'r' de sous-ensembles
void find_optimal_cover_recursive(int subsets[], int start, int size, int r) {
    if (solution_found) return;  // Si une solution a été trouvée, on arrête

    if (size == r) {
        // Si la combinaison a la bonne taille, vérifier si elle couvre tout U
        if (is_combination_covered(subsets, r)) {
            printf("Combinaison optimale trouvée avec %d sous-ensembles :\n", r);
            for (int i = 0; i < r; i++) {
                printf("Sous-ensemble %c\n", 'A' + subsets[i]);  // Convertir en lettre
            }
            solution_found = true;  // On indique qu'une solution a été trouvée
        }
        return;
    }

    // Générer toutes les combinaisons possibles
    for (int i = start; i < S; i++) {
        subsets[size] = i;
        find_optimal_cover_recursive(subsets, i + 1, size + 1, r);
    }
}

int main() {
    // Initialisation du tableau tab à partir de la chaîne c
    int row = 0, col = 0;
    for (int i = 0; i < 42; i++) {
        if (c[i] == ' ') {
            row++;
            col = 0;
        } else {
            tab[row][col] = c[i] - '0';
            col++;
        }
    }

    // Test de toutes les combinaisons de 2 à S sous-ensembles
    for (int r = 2; r <= S; r++) {
        if (solution_found) break;  // Arrêter la boucle si une solution a été trouvée
        int subsets[r];
        find_optimal_cover_recursive(subsets, 0, 0, r);
    }

    return 0;
}
