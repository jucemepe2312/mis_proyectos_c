#include <stdio.h>

// 1. Funciones (fuera de main)
double suma(double a, double b) {
    return a + b;
}

double resta(double a, double b) {
    return a - b;
}

double multiplicacion(double a, double b) {
    return a * b;
}

double division(double a, double b) {
    return a / b;
}

// 2. main (después de las funciones)
int main() {
    printf("Bienvenido a la calculadora basica\n");
    
    while (1) {  // Bucle para repetir
        printf("1. Suma\n");
        printf("2. Resta\n");
        printf("3. Multiplicacion\n");
        printf("4. Division\n");
        printf("Elige una opcion: ");

        int opcion;
        scanf("%d", &opcion);

        if (opcion < 1 || opcion > 4) {
            printf("Opcion no valida. Intenta de nuevo.\n");
            continue;  // Vuelve al inicio del bucle
        }

        if (opcion == 1) {
            printf("Ingrese el primer numero: ");
            double a;
            scanf("%lf", &a);
            printf("Ingrese el segundo numero: ");
            double b;
            scanf("%lf", &b);
            double resultado = suma(a, b);
            printf("El resultado de la suma es: %.2lf\n", resultado);
        } else if (opcion == 2) {
            printf("Ingrese el primer numero: ");
            double a;
            scanf("%lf", &a);
            printf("Ingrese el segundo numero: ");
            double b;
            scanf("%lf", &b);
            double resultado = resta(a, b);
            printf("El resultado de la resta es: %.2lf\n", resultado);
            // Aquí va la resta (igual que suma, pero llamando a resta())
        } else if (opcion == 3) {
            printf("Ingrese el primer numero: ");
            double a;
            scanf("%lf", &a);
            printf("Ingrese el segundo numero: ");
            double b;
            scanf("%lf", &b);
            double resultado = multiplicacion(a, b);
            printf("El resultado de la multiplicacion es: %.2lf\n", resultado);
        } else if (opcion == 4) {
            printf("Ingrese el primer numero: ");
            double a;
            scanf("%lf", &a);
            printf("Ingrese el segundo numero: ");
            double b;
            scanf("%lf", &b);
            if (b == 0) {
                printf("Error: Division por cero no permitida.\n");
            } else {
                double resultado = division(a, b);
                printf("El resultado de la division es: %.2lf\n", resultado);
            }
        }
    }

    return 0;
}