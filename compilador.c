#include <stdio.h>
#include <string.h>   // Para strcpy, strlen, strcmp
#include <stdlib.h> 
#include <sys/stat.h> 
int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("uso:compilar archivo de c\n");
        return 1;
    }

char comando[100];
char *archivo = argv[1];
printf("compilando: %s\n", archivo);

if (argc > 1){
    char base[100];
strcpy(base, archivo);
// Quitar el ".c" del final
base[strlen(base) - 2] = '\0';


sprintf(comando, "gcc %s -o %s", archivo, base);

}
int resultado = system(comando);
if (resultado == 0 ) {
    printf("compilacion exitosa\n");

} else {
    printf("error al compilar \n");
}

    
    return 0;
}