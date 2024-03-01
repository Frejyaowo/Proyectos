#include <stdio.h>

void fibonacci(int n) {
    unsigned long long int a = 0, b = 1, nextTerm;

    printf("Los primeros 500 términos de la serie de Fibonacci para %d son:\n", n);

    for (int i = 1; i <= 500; ++i) {
        printf("%llu, ", a);
        nextTerm = a + b;
        a = b;
        b = nextTerm;
    }
}

int main() {
    int n;

    printf("Ingrese el número para calcular la serie de Fibonacci: ");
    scanf("%d", &n);

    fibonacci(n);

    return 0;
}
