#include <stdio.h>


// 1. DECLARACIÓN DE FUNCIONES (fuera de main)


void depositar(float *saldo, float cantidad) {
    *saldo = *saldo + cantidad;
}

void retirar(float *saldo, float cantidad) {
    *saldo = *saldo - cantidad;
}

void transferir(float *origen, float *destino, float cantidad) {
    if (cantidad > *origen) {
        printf("Saldo insuficiente.\n");
    } else {
        *origen = *origen - cantidad;
        *destino = *destino + cantidad;
    }
}

void mostrar_cuenta(int id, char nombres[][30], char telefonos[][15], float saldos[]) {
    printf("\n--- CUENTA %d ---\n", id);
    printf("Nombre: %s\n", nombres[id]);
    printf("Telefono: %s\n", telefonos[id]);
    printf("Saldo: %.2f\n", saldos[id]);
    printf("------------------\n");
}

void mostrar_todas(int num_contactos, char nombres[][30], char telefonos[][15], float saldos[]) {
    if (num_contactos == 0) {
        printf("\nNo hay cuentas registradas.\n");
        return;
    }
    printf("\n--- LISTA DE CUENTAS ---\n");
    for (int i = 0; i < num_contactos; i++) {
        printf("%d. %s - %s - Saldo: %.2f\n", i, nombres[i], telefonos[i], saldos[i]);
    }
    printf("-------------------------\n");
}  // <--- AQUÍ FALTABA ESTA LLAVE

void agregar_cuenta(int *num_contactos, char nombres[][30], char telefonos[][15], float saldos[]) {
    if (*num_contactos < 5) {
        printf("Nombre de la nueva cuenta: ");
        scanf("%s", nombres[*num_contactos]);
        printf("Telefono de la nueva cuenta: ");
        scanf("%s", telefonos[*num_contactos]);
        saldos[*num_contactos] = 0.0;
        (*num_contactos)++;
        printf("\n¡Cuenta agregada con exito!\n");
    } else {
        printf("\nLimite de cuentas alcanzado (maximo 5).\n");
    }
}


// 2. PROGRAMA PRINCIPAL


int main() {
    char nombres[5][30];
    char telefonos[5][15];
    float saldos[5];
    int num_contactos = 0;
    int opcion;

    while (1) {
        printf("\n===== MEXICAN EXPRESS =====\n");
        printf("1. Ver saldo de una cuenta\n");
        printf("2. Hacer un deposito\n");
        printf("3. Hacer un retiro\n");
        printf("4. Transferir entre cuentas\n");
        printf("5. Agregar nueva cuenta\n");
        printf("6. Mostrar todas las cuentas\n");
        printf("7. Salir\n");
        printf("============================\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            int id;
            printf("Escribe el numero de cuenta (0-%d): ", num_contactos - 1);
            scanf("%d", &id);
            if (id >= 0 && id < num_contactos) {
                mostrar_cuenta(id, nombres, telefonos, saldos);
            } else {
                printf("Cuenta no encontrada.\n");
            }
        }
        else if (opcion == 2) {
            int id;
            float cantidad;
            printf("Escribe el numero de la cuenta: ");
            scanf("%d", &id);
            if (id >= 0 && id < num_contactos) {
                printf("Escribe la cantidad a depositar: ");
                scanf("%f", &cantidad);
                if (cantidad > 0) {
                    depositar(&saldos[id], cantidad);
                    printf("Deposito realizado con exito. Nuevo saldo: %.2f\n", saldos[id]);
                } else {
                    printf("Cantidad invalida.\n");
                }
            } else {
                printf("Cuenta no encontrada.\n");
            }
        }
        else if (opcion == 3) {
            int id;
            float cantidad;
            printf("Escribe el numero de la cuenta: ");
            scanf("%d", &id);
            if (id >= 0 && id < num_contactos) {
                printf("Escribe la cantidad a retirar: ");
                scanf("%f", &cantidad);
                if (cantidad <= saldos[id]) {
                    retirar(&saldos[id], cantidad);
                    printf("Retiro realizado con exito. Nuevo saldo: %.2f\n", saldos[id]);
                } else {
                    printf("Saldo insuficiente.\n");
                }
            } else {
                printf("Cuenta no encontrada.\n");
            }
        }
        else if (opcion == 4) {
            int id1, id2;
            float cantidad;
            printf("Escribe desde que cuenta quieres transferir: ");
            scanf("%d", &id1);
            printf("Y a que cuenta quieres transferir: ");
            scanf("%d", &id2);
            if (id1 >= 0 && id1 < num_contactos && id2 >= 0 && id2 < num_contactos) {
                printf("Introduce la cantidad a transferir: ");
                scanf("%f", &cantidad);
                if (cantidad > 0) {
                    transferir(&saldos[id1], &saldos[id2], cantidad);
                    printf("Transferencia exitosa.\n");
                    printf("Saldo de origen: %.2f\n", saldos[id1]);
                    printf("Saldo de destino: %.2f\n", saldos[id2]);
                } else {
                    printf("Cantidad invalida.\n");
                }
            } else {
                printf("Cuenta no encontrada.\n");
            }
        }
        else if (opcion == 5) {
            agregar_cuenta(&num_contactos, nombres, telefonos, saldos);
        }
        else if (opcion == 6) {
            mostrar_todas(num_contactos, nombres, telefonos, saldos);
        }
        else if (opcion == 7) {
            printf("¡Gracias por usar Mexican Express!\n");
            break;
        }
        else {
            printf("Opcion no valida.\n");
        }
    }

    return 0;
}