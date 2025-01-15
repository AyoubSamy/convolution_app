#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    double** Matrice = NULL;
    double** filtre = NULL;
    double** matrice_resultats = NULL;
    int taille_ligne, taille_colonne, taille_filter, k;
    float sigma;

    // verifier est ce que les donnees entrer par l'utilisateur sont valide :
    do {
        printf("entrer le nombre de ligne qui doit etre superieur A 3 = ");
        scanf("%d", &taille_ligne);

        printf("entrer le nombre de colonne qui doit etre superieur A 3 = ");
        scanf("%d", &taille_colonne);

        printf("entrer la valeur de k pour calculer la taille du masque 2*k+1 (un nombre entier >1 ) = ");
        scanf("%d", &k);

        printf("entrer l'ecart type = ");
        scanf("%f", &sigma);
    } while ((taille_ligne <= 3) || (taille_colonne <= 3));

    // recalculer la taille de filter
    taille_filter = 2 * k + 1;

    // GENERER LA MATRICE :
    Matrice = Generate_Matrice(Matrice, taille_ligne, taille_colonne);

    // INTIALISER LA MATRICE PAR DES VALEURS ALEATOIRES ENTRE 0 ET 255
    Matrice = intialize_Matrice(Matrice, taille_ligne, taille_colonne);

    printf("--------------------------notre Matrice sur laquelle on va appliquer le filtre ----------------------------------:\n ");
    // AFFICHER LA MATRICE :
    affiche_Matrice(Matrice, taille_ligne, taille_colonne);

    // generer le filtre de gauss :
    filtre = generate_gausse_Kernel(filtre, sigma, k);

    printf("--------------------------le filtre gaussien sans normalisation ----------------------------------:\n ");
    affiche_Matrice(filtre, taille_filter, taille_filter);

    printf("--------------------------le filtre gaussien apres normalisation----------------------------------:\n ");
    filtre = Normalize_kernel(filtre, taille_filter);
    affiche_Matrice(filtre, taille_filter, taille_filter);

    printf("--------------------------matrice resultats ----------------------------------:\n ");
    matrice_resultats = Generate_Matrice(matrice_resultats, taille_ligne, taille_colonne);
    matrice_resultats = apply_gaussian_filter(Matrice, taille_ligne, taille_colonne, filtre, k, matrice_resultats);
    affiche_Matrice(matrice_resultats, taille_ligne, taille_colonne);

    return 0;
}