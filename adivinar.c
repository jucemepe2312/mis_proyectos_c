#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

bool comparar_numeros(int usuario, int secreto) {

    if (usuario < secreto) {
        printf("el numero secreto es MAYOR al que dices \n");
        return false;

        } else if (usuario > secreto ) {
            printf("el numero secreto es MENOR  al que dices \n");
            return false;
        } else if (usuario == secreto ) {
            printf("LO LOGRASTE, %d ES EL CORRECTO ", secreto);
            return true;
        }
        return false;
        
    }


int main() {
    char opcion;
    char dificultad[10];
    srand(time(NULL));
    
    while (1) {
        // Elegir dificultad y límite
        int limite = 100;
        int max_intentos = 10;
        
        printf("\n=== ADIVINA EL NÚMERO ===\n");
        printf("¿Listo para empezar? (s/n): ");
        scanf(" %c", &opcion);
        
        if (opcion != 's') {
            printf("Gracias por jugar\n");
            break;
        }
        
        printf("Elige tu dificultad (facil/media/dificil): ");
        scanf("%s", dificultad);
        
        // Configurar según dificultad
        if (strcmp(dificultad, "facil") == 0) {
            limite = 50;
            max_intentos = 15;
        } else if (strcmp(dificultad, "media") == 0) {
            limite = 100;
            max_intentos = 10;
        } else if (strcmp(dificultad, "dificil") == 0) {
            limite = 200;
            max_intentos = 7;
        } else {
            printf("Dificultad no válida. Usando media.\n");
        }
        
        int numero_secreto = rand() % limite + 1;
        int intentos = 0;
        int numero;
        
        printf("\nHe pensado un número entre 1 y %d\n", limite);
        printf("Tienes %d intentos.\n\n", max_intentos);
        
        while (intentos < max_intentos) {
            printf("Intento %d/%d: ", intentos + 1, max_intentos);
            scanf("%d", &numero);
            intentos++;
            

            if (comparar_numeros(numero, numero_secreto)) {
                printf("¡Lo lograste en %d intentos!\n", intentos);
                break;
            }
            
            // Si no acertó y es el último intento, mostrar mensaje
            if (intentos == max_intentos) {
                printf("\n¡Agotaste tus intentos! El número era %d\n", numero_secreto);
            }
        }
    }
    
    return 0;
}




