#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>   // mkdir
#include <dirent.h> 

// ===========================
//  ESTRUCTURAS
// ===========================
typedef struct {
    int id;
    char titulo[100];
    int completada;
} Tarea;

Tarea *tareas = NULL;
int num_tareas = 0;


void agregar_tarea(const char *titulo) {
    mkdir("tareas", 0777);

    // Validar que el título no sea NULL
    if (titulo == NULL || titulo[0] == '\0') {
        printf("❌ Título inválido\n");
        return;
    }

    char nombre_archivo[256];
    sprintf(nombre_archivo, "tareas/%d_%s.txt", num_tareas + 1, titulo);

    FILE *f = fopen(nombre_archivo, "w");
    if (f == NULL) {
        printf("❌ Error al crear el archivo: %s\n", nombre_archivo);
        return;
    }

    fprintf(f, "ID: %d\n", num_tareas + 1);
    fprintf(f, "Tarea: %s\n", titulo);
    fprintf(f, "Estado: Pendiente\n");

    time_t t = time(NULL);
    fprintf(f, "Fecha: %s", ctime(&t));

    fclose(f);
    num_tareas++;
    printf("✅ Tarea creada: %s\n", nombre_archivo);
}



void listar_tareas() {
    DIR *dir = opendir("Tareas");
    if (dir == NULL) {
        printf("📂 No hay tareas o la carpeta no existe\n");
        return;   // ✅ Sin valor
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("📄 %s\n", entry->d_name);
        }
    }
    closedir(dir);
}
void completar_tarea(int id) {
    // 1. Abrir la carpeta
    DIR *dir = opendir("Tareas");
    if (dir == NULL) {
        printf("📂 No hay tareas o la carpeta no existe\n");
        return;
    }

    // 2. Buscar el archivo por ID
    char archivo_encontrado[256] = "";
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char patron[10];
        sprintf(patron, "%d_", id);
        if (strncmp(entry->d_name, patron, strlen(patron)) == 0) {
            strcpy(archivo_encontrado, entry->d_name);
            break;
        }
    }
    closedir(dir);

    // 3. Verificar si se encontró
    if (strlen(archivo_encontrado) == 0) {
        printf("❌ Tarea con ID %d no encontrada\n", id);
        return;
    }

    // 4. Construir la ruta completa
    char ruta_completa[512];
    sprintf(ruta_completa, "tareas/%s", archivo_encontrado);

    // 5. Leer el archivo y guardar en buffer
    FILE *f_lectura = fopen(ruta_completa, "r");
    if (f_lectura == NULL) {
        printf("❌ Error al leer la tarea\n");
        return;
    }

    char buffer[4096] = "";
    char linea[256];
    while (fgets(linea, sizeof(linea), f_lectura) != NULL) {
        // Buscar y reemplazar "Pendiente" por "Completada"
        if (strstr(linea, "Estado: Pendiente") != NULL) {
            strcpy(linea, "Estado: Completada\n");
        }
        strcat(buffer, linea);
    }
    fclose(f_lectura);

    // 6. Guardar el archivo modificado
    FILE *f_escritura = fopen(ruta_completa, "w");
    if (f_escritura == NULL) {
        printf("❌ Error al guardar la tarea\n");
        return;
    }
    fprintf(f_escritura, "%s", buffer);
    fclose(f_escritura);

    // 7. Mostrar mensaje de éxito
    printf("✅ Tarea %d completada\n", id);
}
void ver_tareas() {
    DIR *dir = opendir("Tareas");
    if (dir == NULL) {
        printf("📂 No hay tareas o la carpeta no existe\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char ruta_completa[512];
            sprintf(ruta_completa, "tareas/%s", entry->d_name);

            FILE *f = fopen(ruta_completa, "r");
            if (f == NULL) {
                printf("Error al leer: %s\n", entry->d_name);
                continue;
            }

            char linea[256];
            printf("\n=== %s ===\n", entry->d_name);
            while (fgets(linea, sizeof(linea), f) != NULL) {
                printf("%s", linea);
            }
            fclose(f);
        }
        // <--- ELIMINA ESTE return;
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: tareas [comando] [argumento]\n");
        printf("Comandos: agregar, listar, ver_todas, completar\n");
        return 1;
    }

    if (strcmp(argv[1], "agregar") == 0) {
        if (argc > 2) {
            agregar_tarea(argv[2]);
        } else {
            printf("❌ Falta el título de la tarea\n");
        }
    }
    else if (strcmp(argv[1], "listar") == 0) {
        listar_tareas();
    }
    else if (strcmp(argv[1], "ver_todas") == 0) {
        ver_tareas();
    }
    else if (strcmp(argv[1], "completar") == 0) {
        if (argc > 2) {
            int id = atoi(argv[2]);
            completar_tarea(id);
        } else {
            printf("❌ Falta el ID de la tarea\n");
        }
    }
    else {
        printf("❌ Comando desconocido: %s\n", argv[1]);
        printf("Comandos: agregar, listar, ver_todas, completar\n");
    }

    return 0;
}


