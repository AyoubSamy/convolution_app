
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

// fonction pour generer une matrice :
double** Generate_Matrice(double **Matrice, int n, int p) {
    Matrice = (double **)malloc(n * sizeof(double*)); // creation d'un espace memoire pointe par matrice de taille n qui doit representer notre colonnes
    if (Matrice == NULL) {
        printf("Erreur d'allocation mémoire pour les lignes.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        Matrice[i] = (double*)malloc(p * sizeof(double)); // allocation de lignes
        if (Matrice[i] == NULL) {
            printf("Erreur d'allocation mémoire pour la colonne %d.\n", i);
            exit(1);
        }
    }
    return Matrice;
}

// fonction pour intialiser la matrice :
double** intialize_Matrice(double **Matrice, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Matrice[i][j] = rand() % 256;
        }
    }
    return Matrice;
}

// affichage d'une matrice :
void affiche_Matrice(double **Matrice, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("T[%d][%d] = %.2lf \n", i, j, Matrice[i][j]);
        }
    }
}

// calcule des coefficient de la matrice de filter de gauss :
double** generate_gausse_Kernel(double** filter, float sigma, int k) {
    int N = 2 * k + 1;
    int x, y = 0;
    // generer la matrice vide :
    filter = Generate_Matrice(filter, N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // calculer les decalages x et y
            x = i - k; // (k,k) est le centre de kernel
            y = j - k;
            filter[i][j] = (1.0 / (2.0 * M_PI * (sigma * sigma))) * exp(-((x * x + y * y) / (2 * sigma * sigma))); // expression de la fonction gaussienne
        }
    }
    return filter;
}

// fonction de normalisation :
double** Normalize_kernel(double** filter, int taille) {
    double sum = 0.0;
    int i, j;
    // calcule de la somme des elements de filtre
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            sum += filter[i][j];
        }
    }
    // diviser par la somme chaque element
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            filter[i][j] /= sum;
        }
    }
    return filter;
}

// fonction qui applique le filtre de gausse :
double** apply_gaussian_filter(double** Matrice, int lignes, int colonnes, double** kernel, int k, double** Matrice_resultat) {
    int N = 2 * k + 1; // Taille du noyau

    // Parcourir chaque pixel de l'image
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            double pix_conv = 0.0;

            // Convolution : appliquer le noyau autour du pixel (i, j)
            for (int ki = -k; ki <= k; ki++) {
                for (int kj = -k; kj <= k; kj++) {
                    // Pour accéder aux indices des pixels voisins selon la taille du noyau
                    int x = i + ki; // Décalage dans l'axe horizontal
                    int y = j + kj; // Décalage dans l'axe vertical

                    // Vérifier les bords (ignorer les pixels hors image)
                    if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
                        pix_conv += Matrice[x][y] * kernel[ki + k][kj + k];
                    }
                }
            }
            Matrice_resultat[i][j] = pix_conv; // Mettre le résultat dans l'image filtrée
        }
    }
    return Matrice_resultat;
}