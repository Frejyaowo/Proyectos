#include <stdio.h>

int solucion(int *X, int *Y, int *D);

int main() {
    int X = 0;
    int Y = 0;
    int D = 0;
    
    printf("\n Bienvenido: \n ");
	printf("\n Si desea saber la cantidad minima de saltos que debe realizar la rana pequeña para alcanzar su objetivo: \n ");
    printf("\n Digite la posicion X:  \n ");
    scanf("%d", &X);
    printf("\n Digite la posicion Y:  \n ");
    scanf("%d", &Y);    

    do{
        printf("\n Digite la distancia fija D:  \n");
        scanf("%d", &D);
    }while(D <= 0);


    printf("\n Digite la a distancia fija D:  \n");
    scanf("%d", &D);
    
    printf("\n Numero minimo de saltos: %d\n", solucion(&X, &Y, &D));
    return 0;
}


int solucion(int *X, int *Y, int *D) {
    return (*Y - *X + *D - 1) / *D;
}
