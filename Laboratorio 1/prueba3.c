#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaración de la función leer_imagen
void leer_imagen(const char* imagenp);

// Declaración de la función escala de grises
void escala_grises(const char* imagenp);

// Declaración de la función convolución
void convolucion(const char* imagenp);


int main() {
    char imagenp[] = "imagenp.bmp"; // Nombre de la imagen

    // Variables necesarias para manejar la apertura y lectura de un archivo BMP
    FILE* entrada = fopen(imagenp, "rb");
    unsigned char header[54];
    unsigned char pixel[3];
    unsigned char gray;

    if (entrada == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1; // Salir del programa con un código de error
    }

    // Lectura de la imagen
    leer_imagen(imagenp);

    // Menú de opciones
    int opcion;
    printf("\nMENU DE OPCIONES:\n");
    printf("1. Cambiar a escala de grises\n");
    printf("2. Convolución\n");
    printf("3. Salir\n");
    printf("\nIntroduzca su opción (1-4): ");
    scanf("%d", &opcion);

    switch (opcion) {
        
        case 1: 
            printf("\nHa elegido cambiar a escala de grises.\n");
            escala_grises(imagenp);
            break;
        case 2: 
            printf("\nHa elegido convolución.\n");
            convolucion(imagenp);
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
void leer_imagen(const char* imagenp) {
    FILE* entrada = fopen(imagenp, "rb");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de imagen.\n");
        return;
    }
    printf("Imagen leída correctamente.\n");
    fclose(entrada);
}


// Implementación de la función escala de grises
void escala_grises(const char* imagenp) {
	
	/*Se abren dos archivos, uno para la lectura de la imagen original (entrada) 
	y otro para la escritura de la imagen en escala de grises (salida). 
	El archivo de salida se crea con el nombre "imagen_gris.bmp". */
    FILE* entrada = fopen(imagenp, "rb");
    FILE* salida = fopen("imagen_gris.bmp", "wb");
    
    /*Se verifica si la apertura de ambos archivos fue exitosa. Si alguno de los 
	dos archivos no se pudo abrir, se imprime un mensaje de error y se sale de 
	la función.*/
    if (entrada == NULL || salida == NULL) {
        printf("Error al abrir los archivos de imagen.\n");
        return;
    }

	/* Se lee la cabecera del archivo de imagen original (entrada) y se escribe 
	en el archivo de salida (salida). La cabecera de un archivo BMP generalmente 
	tiene un tamaño de 54 bytes.*/
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, entrada);
    fwrite(header, sizeof(unsigned char), 54, salida);


	/* Se extraen las dimensiones de la imagen (ancho y alto) de la cabecera del 
	archivo. 
	Además, se calcula la cantidad de bytes de relleno (padding) que se 
	requiere al final de cada fila para que la fila tenga un tamaño múltiplo de 
	4 bytes.*/
    int ancho = (int)&header[18];
    int alto = (int)&header[22];
    int padding = (4 - (ancho * 3) % 4); //Lo encontramos mediante formulas 


	/* Se declaran variables para almacenar los valores de los píxeles de la 
	imagen original (pixel) y su versión en escala de grises (gray). 
	La imagen 
	se supone que tiene píxeles de 24 bits (3 bytes por píxel) :) */
    unsigned char pixel[3];
    unsigned char gray;
    

	/* Se itera sobre cada fila y columna de la imagen original. 
	Se lee el valor de cada píxel (componentes R, G, B) y se calcula su valor 
	en escala de grises utilizando la fórmula. 
	Luego, se escribe el nuevo valor de píxel en el archivo de salida. 
	Después de escribir cada fila de píxeles, se agrega el 
	padding necesario al final de la fila, 4 bytes por pixel para el color RGB tambien para la luminocidad. */
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


	// se cierran ambos archivos para liberar los recursos utilizados.
    fclose(entrada);
    fclose(salida);
}

void convolucion(const char* imagenp){
	
}
