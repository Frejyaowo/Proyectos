#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, i;
    long long int *fib;

    printf("Ingrese un numero para realizar la serie: ");
    scanf("%d", &n);

    fib = (long long int*)malloc(n * sizeof(long long int));

    fib[0] = 0;
    fib[1] = 1;

    for (i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    printf("La serie fibonacci es: ");

    for (i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    
    printf("\n");

    free(fib); // Liberar memoria asignada con malloc

    return 0;
}

