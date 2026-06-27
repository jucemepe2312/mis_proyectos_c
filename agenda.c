#include <stdio.h>
#include <string.h>

int main() {
    char nombres[5][30];
    char telefonos[5][15];
    int num_contactos = 0;
    int opcion;

    while (1) {
        printf("\n--- Agenda ---\n");
        printf("1. Agregar\n");
        printf("2. Mostrar\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            printf("Nombre: ");
            scanf("%s", nombres[num_contactos]);
            printf("Telefono: ");
            scanf("%s", telefonos[num_contactos]);
            num_contactos++;
        } else if (opcion == 2) {
            printf("Numero de contactos: %d\n", num_contactos);
            for (int i = 0; i < num_contactos; i++) {
                printf("%d. %s - %s\n", i + 1, nombres[i], telefonos[i]);
            }
        } else if (opcion == 3) {
            break;
        } else {
            printf("Opcion no valida.\n");
        }
    }

    return 0;
}