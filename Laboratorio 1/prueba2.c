#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de la función leer_imagen
void leer_imagen(const char* lunabmp);

// Declaración de la función guardar_imagen
unsigned char** guardar_imagen(const char* lunabmp, int* ancho, int* alto);

// Declaración de la función escala de grises
void escala_grises(unsigned char** matriz_pixels, int ancho, int alto);

// Declaración de la función convolucion
void convolucion(unsigned char** matriz_pixels, int ancho, int alto, int** matriz_conv);

int main() {
    char lunabmp[] = "lunabmp.bmp"; // Nombre de la imagen

    // Variables necesarias para manejar la apertura y lectura de un archivo BMP
    FILE* entrada = fopen(lunabmp, "rb");
    unsigned char header[54];
    unsigned char pixel[3];
    unsigned char gray;

    if (entrada == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1; // Salir del programa con un código de error
    }

    // Lectura de la imagen
    leer_imagen(lunabmp);

    // Obtener matriz de píxeles
    int ancho, alto;
    unsigned char** matriz_pixels = guardar_imagen(lunabmp, &ancho, &alto);

    // Menú de opciones
    int opcion;
    printf("\nMENU DE OPCIONES:\n");
    printf("1. Cambiar a escala de grises\n");
    printf("2. Convolución\n");
    printf("3. Salir\n");
    printf("\nIntroduzca su opción (1-3): ");
    scanf("%d", &opcion);

    switch (opcion) {
        
        case 1: 
            printf("\nHa elegido cambiar a escala de grises.\n");
            escala_grises(matriz_pixels, ancho, alto);
            break;
        case 2: 
            printf("\nHa elegido convolución.\n");
            // Solicitar al usuario que introduzca los valores de la matriz de convolución
            int** matriz_conv = (int*)malloc(3 * sizeof(int));
            for (int i = 0; i < 3; ++i) {
                matriz_conv[i] = (int*)malloc(3 * sizeof(int));
            }
            printf("Introduzca los valores de la matriz de convolución:\n");
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    scanf("%d", &matriz_conv[i][j]);
                }
            }
            convolucion(matriz_pixels, ancho, alto, matriz_conv);
            // Liberar memoria usada por la matriz de convolución
            for (int i = 0; i < 3; ++i) {
                free(matriz_conv[i]);
            }
            free(matriz_conv);
            break;
        case 3: 
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción no válida. Por favor, seleccione una opción válida (1-4).\n");
            break;
    };

    fclose(entrada); // Cerrar el archivo de entrada

    // Liberar memoria usada por la matriz de píxeles
    for (int i = 0; i < alto; ++i) {
        free(matriz_pixels[i]);
    }
    free(matriz_pixels);

    return 0;
}

// Implementación de la función leer_imagen
void leer_imagen(const char* lunabmp) {
    FILE* entrada = fopen(lunabmp, "rb");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de imagen.\n");
        return;
    }
    printf("Imagen leída correctamente.\n");
    fclose(entrada);
}

// Implementación de la función guardar_imagen
unsigned char** guardar_imagen(const char* lunabmp, int* ancho, int* alto) {
    FILE* entrada = fopen(lunabmp, "rb");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de imagen.\n");
        return NULL;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, entrada);

    *ancho = (int)header[18];
    *alto = (int)header[22];
    int padding = (4 - (*ancho * 3) % 4) % 4;

    unsigned char pixel[3];
    unsigned char gray;

    // Crear matriz de píxeles usando malloc
    unsigned char** matriz_pixels = (unsigned char*)malloc(*alto * sizeof(unsigned char));
    for (int i = 0; i < *alto; ++i) {
        matriz_pixels[i] = (unsigned char*)malloc(*ancho * sizeof(unsigned char));
    }

    for (int i = 0; i < *alto; ++i) {
        for (int j = 0; j < *ancho; ++j) {
            fread(pixel, sizeof(unsigned char), 3, entrada);
            matriz_pixels[i][j] = pixel[0];
        }
        fseek(entrada, padding, SEEK_CUR);
    }

    fclose(entrada);

    return matriz_pixels;
}

// Implementación de la función escala de grises
void escala_grises(unsigned char** matriz_pixels, int ancho, int alto) {
    // Convertir matriz de píxeles a escala de grises
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            matriz_pixels[i][j] = (unsigned char)((299 * matriz_pixels[i][j] + 587 * matriz_pixels[i][j] + 114 * matriz_pixels[i][j])/1000);
        }
    }

    // Guardar matriz de píxeles en escala de grises en un archivo
    guardar_imagen("imagen_gris.bmp", matriz_pixels, ancho, alto);
}

// Implementación de la función convolucion
void convolucion(unsigned char** matriz_pixels, int ancho, int alto, int** matriz_conv) {
    // Crear matriz de píxeles para la imagen convolucionada
    unsigned char** matriz_convolucionada = (unsigned char*)malloc(alto * sizeof(unsigned char));
    for (int i = 0; i < alto; ++i) {
        matriz_convolucionada[i] = (unsigned char*)malloc(ancho * sizeof(unsigned char));
    }

    // Aplicar convolución a cada píxel de la imagen
    for (int i = 1; i < alto - 1; ++i) {
        for (int j = 1; j < ancho - 1; ++j) {
            int suma = 0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    suma += matriz_pixels[i + k][j + l] * matriz_conv[k + 1][l + 1];
                }
            }
            matriz_convolucionada[i][j] = (unsigned char)suma;
        }
    }

    // Guardar matriz de píxeles convolucionada en un archivo
    guardar_imagen("imagen_conv.bmp", matriz_convolucionada, ancho, alto);

    // Liberar memoria usada por la matriz de píxeles convolucionada
    for (int i = 0; i < alto; ++i) {
        free(matriz_convolucionada[i]);
    }
    free(matriz_convolucionada);
}