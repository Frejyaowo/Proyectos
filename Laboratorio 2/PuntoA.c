#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para generar un movimiento aleatorio (-1, 0 o 1)
int generarMovimiento() {
    return rand() % 3 - 1;
}

int main() {
    int c; // Diámetro del círculo
    int x = 0, y = 0; // Coordenadas iniciales de la partícula
    int movimientos = 0;

    // Entrada de datos
    printf("Ingrese el diametro del circulo (1 <= c <= 100): ");
    scanf("%d", &c);
    printf("Ingrese las coordenadas iniciales (x y): ");
    scanf("%d %d", &x, &y);

    // Semilla para generar números aleatorios
    srand(time(NULL));

    // Simulación de 13 movimientos
    while (movimientos < 13) {
        int dx = generarMovimiento();
        int dy = generarMovimiento();

        // Actualizar coordenadas
        x += dx;
        y += dy;

        // Verificar si la partícula salió del círculo
        if (x * x + y * y > c * c / 4) {
            break;
        }

        // Mostrar el movimiento actual
        printf("Movimiento %d: (%d, %d)\n", movimientos + 1, dx, dy);

        movimientos++;
    }

    // Salida
    printf("La particula realizo %d movimientos antes de salir del circulo.\n", movimientos);

    return 0;
}