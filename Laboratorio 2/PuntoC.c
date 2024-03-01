#include <stdio.h>

// Función para mostrar un dígito en formato LCD
void mostrarDigito(int digito, char *display, const int *lcd_segment, const char *segment_c, const char *segment_x, const char *segment_y) {
    for (int segnum = 0; segnum < 12; segnum++) {
        if (lcd_segment[digito * 12 + segnum] == 1) {
            int x = segment_x[segnum];
            int y = segment_y[segnum];
            display[y * 36 + x] = segment_c[segnum];
        }
    }
}

int main() {
    const int lcd_segment[] =
    {
        1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, // 0
        0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, // 1
        1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, // 2
        1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, // 3
        0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, // 4
        1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, // 5
        1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, // 6
        1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, // 7
        1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, // 8
        1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, // 9
    };

    const char segment_c[] = "--|||--|||--";
    const char segment_x[] = { 1, 3, 0, 2, 4, 1, 3, 0, 2, 4, 1, 3 };
    const char segment_y[] = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4 };

    char display[180]; // Array para almacenar los tres números (5 filas x 12 columnas * 3)

    int digito1, digito2, digito3;

    while (1) {
        printf("Ingrese el primer dígito (0-9): ");
        scanf("%d", &digito1);

        printf("Ingrese el segundo dígito (0-9): ");
        scanf("%d", &digito2);

        printf("Ingrese el tercer dígito (0-9): ");
        scanf("%d", &digito3);

        if ((digito1 < 0 || digito1 > 9) || (digito2 < 0 || digito2 > 9) || (digito3 < 0 || digito3 > 9)) {
            printf("Al menos uno de los dígitos está fuera de rango. Por favor, ingrese dígitos válidos (0-999).\n");
            continue; // Volver al inicio del bucle
        }

        // Limpiar la matriz display
        for (int i = 0; i < 180; i++)
            display[i] = ' ';

        // Mostrar el primer dígito en la matriz display
        mostrarDigito(digito1, display, lcd_segment, segment_c, segment_x, segment_y);

        // Mostrar el segundo dígito en la matriz display
        mostrarDigito(digito2, display + 12, lcd_segment, segment_c, segment_x, segment_y);

        // Mostrar el tercer dígito en la matriz display
        mostrarDigito(digito3, display + 24, lcd_segment, segment_c, segment_x, segment_y);

        // Imprimir los dígitos uno al lado del otro
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 36; j++)
                putchar(display[i * 36 + j]);
            putchar('\n');
        }
    }

    return 0;
}
