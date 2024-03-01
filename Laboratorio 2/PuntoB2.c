#include <stdio.h>

int contarDivisibles(int A, int B, int K) {
    // Si A es divisible por K, entonces A es el primer número en el rango que es divisible por K
    // De lo contrario, el primer número en el rango que es divisible por K es el próximo múltiplo de K mayor que A
    int primerMultiplo = (A % K == 0) ? A : A + (K - A % K);

    // Si el primer múltiplo de K que es mayor que B está fuera del rango [A..B], no hay números en el rango que sean divisibles por K
    if (primerMultiplo > B) {
        return 0;
    }

    // Calcular el último múltiplo de K que está dentro del rango [A..B]
    int ultimoMultiplo = B - B % K;

    // Calcular el número de múltiplos de K en el rango [A..B]
    int cantidadMultiplos = (ultimoMultiplo - primerMultiplo) / K + 1;

    return cantidadMultiplos;
}

int main() {
    int A, B, K;

    // Entrada de datos
    printf("Ingrese el valor de A: ");
    scanf("%d", &A);
    printf("Ingrese el valor de B: ");
    scanf("%d", &B);
    printf("Ingrese el valor de K: ");
    scanf("%d", &K);

    // Llamada a la función contarDivisibles
    int cantidadDivisibles = contarDivisibles(A, B, K);

    // Salida
    printf("El numero de enteros dentro del rango [%d..%d] que son divisibles por %d es: %d\n", A, B, K, cantidadDivisibles);

    return 0;
}