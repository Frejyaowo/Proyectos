#include <stdio.h>

<<<<<<< HEAD
<<<<<<< HEAD
int main() {
    const int MAX_TERMS = 500;
    unsigned long long fib[MAX_TERMS]; // Arreglo estático para almacenar la serie de Fibonacci
    unsigned long long n; // Número de términos a calcular

    printf("Ingrese un numero para realizar la serie: ");
    scanf("%llu", &n);

    if (n > MAX_TERMS) {
        printf("El numero ingresado excede el limite de 500.\n");
        return 1;
    }

    // Calcular la serie de Fibonacci
    fib[0] = 0;
    fib[1] = 1;
    for (unsigned long long i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Imprimir la serie de Fibonacci
    printf("La serie fibonacci es: ");
    for (unsigned long long i = 0; i < n; i++) {
        printf("%llu ", fib[i]);
    }
    printf("\n");

=======
// Función para mostrar un dígito en formato LCD
void mostrarDigito(int digito) {
    const char *lcd[] = {
        " -- ", "|  |", "    ", "|  |", " -- ", // 0
        "    ", "   |", "    ", "   |", "    ", // 1
        " -- ", "   |", " -- ", "|   ", " -- ", // 2
        " -- ", "   |", " -- ", "   |", " -- ", // 3
        "    ", "|  |", " -- ", "   |", "    ", // 4
        " -- ", "|   ", " -- ", "   |", " -- ", // 5
        " -- ", "|   ", " -- ", "|  |", " -- ", // 6
        " -- ", "   |", "    ", "   |", "    ", // 7
        " -- ", "|  |", " -- ", "|  |", " -- ", // 8
        " -- ", "|  |", " -- ", "   |", " -- "  // 9
    };
    for (int i = 0; i < 5; i++)
        printf("%s\n", lcd[digito * 5 + i]);
}

=======
>>>>>>> 38ed9eb (change 4)
int main() {
    const int MAX_TERMS = 500;
    unsigned long long fib[MAX_TERMS]; // Arreglo estático para almacenar la serie de Fibonacci
    unsigned long long n; // Número de términos a calcular

    printf("Ingrese un numero para realizar la serie: ");
    scanf("%llu", &n);

    if (n > MAX_TERMS) {
        printf("El numero ingresado excede el limite de 500.\n");
        return 1;
    }
<<<<<<< HEAD
>>>>>>> ef6eb05 (Change 3)
=======

    // Calcular la serie de Fibonacci
    fib[0] = 0;
    fib[1] = 1;
    for (unsigned long long i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Imprimir la serie de Fibonacci
    printf("La serie fibonacci es: ");
    for (unsigned long long i = 0; i < n; i++) {
        printf("%llu ", fib[i]);
    }
    printf("\n");

>>>>>>> 38ed9eb (change 4)
    return 0;
}
