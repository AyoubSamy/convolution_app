/*Tarik Khoumri CCN
Sidi Mohamed Nabgha Abd Latif GLSID
Abdellah khaiy GLSID
Ayoub Samy BDCC */
double** Generate_Matrice(double **, int, int);
double** intialize_Matrice(double **, int, int);
void affiche_Matrice(double **, int, int);
double** generate_gausse_Kernel(double**, float, int);
double** Normalize_kernel(double**, int);
double** apply_gaussian_filter(double**, int, int, double**, int, double**);