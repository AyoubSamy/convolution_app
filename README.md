# Gaussian Filter Application

This project generates a matrix of pixel values, applies a Gaussian filter to smooth it, and normalizes the results. It's a basic implementation of Gaussian blurring, commonly used in image processing.

## Features

- Generate a matrix of random pixel values (0 to 255).
- Create a Gaussian kernel based on user-defined parameters.
- Normalize the kernel to ensure accurate filtering.
- Apply the Gaussian filter to the matrix using convolution.

## How It Works

1. The user specifies:
   - Matrix size (rows and columns).
   - Kernel size using `k` (filter size = `2k + 1`).
   - Standard deviation (`sigma`) for the Gaussian filter.

2. The application:
   - Generates a random pixel matrix.
   - Creates and normalizes the Gaussian kernel.
   - Applies the filter to the matrix, producing a smoothed output.

## Gaussian Filter Function

The Gaussian filter is applied using the following function:

```c
// Function to apply Gaussian filter to a matrix
double** apply_gaussian_filter(double** Matrice, int lignes, int colonnes, double** kernel, int k, double** Matrice_resultat) {
    int N = 2 * k + 1; // Taille du noyau

    // Parcourir chaque pixel de l'image
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            double pix_conv = 0.0;

            // Convolution: appliquer le noyau autour du pixel (i, j)
            for (int ki = 0; ki < N; ki++) {
                for (int kj = 0; kj < N; kj++) {
                    int x = i + (ki - k); // Horizontal shift
                    int y = j + (kj - k); // Vertical shift

                    // Vérifier les bords (ignorer les pixels hors image)
                    if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
                        pix_conv += Matrice[x][y] * kernel[ki][kj];
                    }
                }
            }

            Matrice_resultat[i][j] = pix_conv; // Résultat dans l'image filtrée
        }
    }
    return Matrice_resultat;
}
```

## Visualization of Convolution

The image below illustrates the convolution process, where the kernel is slid over the matrix and a weighted sum of overlapping values is computed for each position:

![Convolution Process](https://upload.wikimedia.org/wikipedia/commons/8/8f/2D_Convolution_Animation.gif)

## Usage

1. Compile the program using a C compiler (e.g., GCC):
   ```bash
   gcc -o gaussian_filter gaussian_filter.c -lm
   ```

2. Run the program:
   ```bash
   ./gaussian_filter
   ```

3. Follow the prompts to input matrix size, kernel size, and sigma.

## Example

Input:
- Matrix size: 5x5
- Kernel size: 3 (kernel = 3x3)
- Sigma: 1.0

Output:
- Original matrix
- Gaussian kernel (before and after normalization)
- Filtered matrix

## Requirements

- A C compiler (e.g., GCC).
- Standard math library (`-lm` flag).

## License

This project is free to use and modify.

