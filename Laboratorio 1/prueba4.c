#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de la función leer_imagen
void leer_imagen(const char* lunabmp);

// Declaración de la función guardar_imagen
unsigned char** guardar_imagen(const char* lunabmp);

// Declaración de la función escala de grises
void escala_grises(unsigned char** matriz_pixels, int ancho, int alto);

// Declaración de la función convolucion
void convolucion(unsigned char** matriz_pixels, int ancho, int alto);

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
    unsigned char** matriz_pixels = guardar_imagen(lunabmp);

    // Obtener dimensiones de la imagen
    int ancho = (int)header[18];
    int alto = (int)header[22];

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
            convolucion(matriz_pixels, ancho, alto);
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
unsigned char** guardar_imagen(const char* lunabmp) {
    FILE* entrada = fopen(lunabmp, "rb");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de imagen.\n");
        return NULL;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, entrada);

    int ancho = (int)header[18];
    int alto = (int)header[22];
    int padding = (4 - (ancho * 3) % 4) % 4;

    unsigned char pixel[3];
    unsigned char gray;

    // Crear matriz de píxeles usando malloc
    unsigned char** matriz_pixels = (unsigned char**)malloc(alto * sizeof(unsigned char*));
    for (int i = 0; i < alto; ++i) {
        matriz_pixels[i] = (unsigned char*)malloc(ancho * sizeof(unsigned char));
    }

    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
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
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            matriz_pixels[i][j] = (unsigned char)((299 * matriz_pixels[i][j] + 587 * matriz_pixels[i][j] + 114 * matriz_pixels[i][j])/1000);
        }
    }
}

// Implementación de la función convolucion
void convolucion(unsigned char** matriz_pixels, int ancho, int alto) {
    // Implementación de la convolución
}
