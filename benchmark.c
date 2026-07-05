#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio = clock();
    long long contador = 0;
    
    while ((double)(clock() - inicio) / CLOCKS_PER_SEC < 5.0) {
        printf("hola");
        contador++;
        if (contador % 100000000 == 0) {
            printf("Contador: %lld\n", contador);
        }
    }
    
    double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Total: %lld\n", contador);
    printf("Tiempo: %.6f segundos\n", tiempo);
    return 0;
}