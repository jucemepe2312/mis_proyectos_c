#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    
    printf("=== SHARK (copia mala de Dolphin) ===\n");
    printf("1. Ver archivos\n");
    printf("2. Hacer una carpeta\n");
    printf("3. Ver una carpeta\n");
    printf("Elige una opción: ");
    
    int opcion;
    scanf("%d", &opcion);
    
    if (opcion == 1) {
        DIR *dir = opendir("/home/santi");
        if (dir == NULL) {
            printf("Error: no se pudo abrir la carpeta.\n");
            return 1;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s\n", entry->d_name);
            }
        }
        closedir(dir);

    } else if (opcion == 2) {
        char nombre[256];
        printf("Nombre de la carpeta: ");
        scanf("%s", nombre);
        
        if (mkdir(nombre, 0777) == 0) {
            printf("Carpeta '%s' creada con éxito.\n", nombre);
        } else {
            printf("Error: no se pudo crear la carpeta.\n");
        }

    } else if (opcion == 3) {
        char ruta[256];
        printf("Escribe la ruta de la carpeta: ");
        scanf("%s", ruta);
        
        DIR *dir = opendir(ruta);
        if (dir == NULL) {
            printf("Error: no se pudo abrir la carpeta '%s'.\n", ruta);
            return 1;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s\n", entry->d_name);
            }
        }
        closedir(dir);


    } else {
        printf("Opción no válida.\n");
    }
    
    return 0;
}