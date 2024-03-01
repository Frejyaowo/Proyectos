#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaración de la función leer_imagen
void leer_imagen(const char* mario);

// Declaración de la función escala de grises
void escala_grises(const char* mario);

// Declaración de la función convolución
void convolucion(const char* mario);


int main() {
    char mario[] = "Yoshibmp.bmp"; // Nombre de la imagen

    // Variables necesarias para manejar la apertura y lectura de un archivo BMP
    FILE* entrada = fopen(mario, "rb");
    unsigned char header[54];
    unsigned char pixel[3];
    unsigned char gray;

    if (entrada == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1; // Salir del programa con un código de error
    }

    // Lectura de la imagen
    leer_imagen(mario);

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
            escala_grises(mario);
            break;
        case 2: 
            printf("\nHa elegido convolución.\n");
            convolucion(mario);
            break;
        case 3: 
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción no válida. Por favor, seleccione una opción válida (1-4).\n");
            break;
    };

    fclose(entrada); // Cerrar el archivo de entrada
    return 0;
}

// Implementación de la función leer_imagen
void leer_imagen(const char* mario) {
    FILE* entrada = fopen(mario, "rb");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de imagen.\n");
        return;
    }
    printf("Imagen leída correctamente.\n");
    fclose(entrada);
}

// Implementación de la función escala de grises
void escala_grises(const char* mario) {
	
    FILE* entrada = fopen(mario, "rb");
    FILE* salida = fopen("yoshi_gris.bmp", "wb");
    if (entrada == NULL || salida == NULL) {
        printf("Error al abrir los archivos de imagen.\n");
        return;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, entrada);
    fwrite(header, sizeof(unsigned char), 54, salida);

    int ancho = (int)&header[18];
    int alto = (int)&header[22];
    int padding = (4 - (ancho * 3) % 4);

    unsigned char pixel[3];
    unsigned char gray;

    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            fread(pixel, sizeof(unsigned char), 3, entrada);
            gray = (unsigned char)((299 * pixel[2] + 587 * pixel[1] + 114 * pixel[0])/1000);
            memset(pixel, gray, sizeof(pixel));
            fwrite(pixel, sizeof(unsigned char), 3, salida);
        }
        unsigned char padding_byte = 0;
        fwrite(&padding_byte, sizeof(unsigned char), padding, salida);
    }

    printf("Imagen convertida a escala de grises y guardada como 'imagen_gris.bmp'.\n");

    fclose(entrada);
    fclose(salida);
}

void convolucion(const char* mario){
	
}