#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10000 

void sum(char *a, char *b, char *result) {
    int carry = 0;
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int k = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? a[i] - '0' : 0;
        int digitB = (j >= 0) ? b[j] - '0' : 0;
        int total = digitA + digitB + carry;
        result[k++] = total % 10 + '0';
        carry = total / 10;
        i--;
        j--;
    }

    result[k] = '\0';

    // Reverse the result string
    int len = strlen(result);
    for (int m = 0; m < len / 2; m++) {
        char temp = result[m];
        result[m] = result[len - m - 1];
        result[len - m - 1] = temp;
    }
}

void fib(int n) {
    if (n <= 0) {
        printf("Ingrese un número positivo mayor que cero.\n");
        return;
    }

    char f[MAX_DIGITS] = "0";
    char f_next[MAX_DIGITS] = "1";
    char temp[MAX_DIGITS];

    printf("La serie fibonacci es: %s ", f);

    for (int i = 1; i < n; ++i) {
        printf("%s ", f_next);
        sum(f, f_next, temp);
        strcpy(f, f_next);
        strcpy(f_next, temp);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Ingrese el número que desea generar: ");
    scanf("%d", &n);

    fib(n);

    return 0;
}
