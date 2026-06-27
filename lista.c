#include <stdio.h>

int main(){

    char tareas[5][100];
    char num_tareas = 0;
    int opcion;

    while (1){

    printf("bienvenido a esta humilde lista de tareas \n");
    printf("por favor ingresa que deseas hacer \n");
    printf("1:agregar una tarea \n");
    printf("2:mirar las tareas \n" );
    printf("3:completar una tarea \n");
    printf("4:salir \n");

    scanf("%d", &opcion);


    if (opcion == 1){
        printf("has decidido hacer una nueva tarea \n");
        printf("introduce el nombre de la tarea en una sola palabra \n");
        scanf("%s", tareas[num_tareas]);
        num_tareas++;

} else if (opcion == 2) {
    printf("Tus tareas:\n");
    for (int i = 0; i < num_tareas; i++) {
        printf("%s\n", tareas[i]);  // <--- Esto muestra el nombre de la tarea
    }
} else if (opcion == 3) {
    printf ("introduce el nombre de la tarea que deseas completar o eliminar \n");
    scanf ("%s", tareas[num_tareas]);
    num_tareas--;
    printf("tarea eliminada exitosamente \n");
} else if (opcion == 4){
    break;
}

    }

    return 0;
}