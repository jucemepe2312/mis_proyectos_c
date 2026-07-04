// ============================================================
//  BIBLIOTECAS
// ============================================================
#include "raylib.h"

// ============================================================
//  ENUMS (Estados del juego)
// ============================================================
typedef enum {
    MENU,       // Pantalla de inicio / selección de dificultad
    JUGANDO,    // Juego en curso
    GAME_OVER   // Pantalla de "perdiste"
} EstadoJuego;

// ============================================================
//  CONSTANTES
// ============================================================
#define TAMANO_CELDA 20      // Tamaño de cada cuadrito (20x20 píxeles)
#define ANCHO 800            // Ancho de la ventana
#define ALTO 600             // Alto de la ventana
#define COLUMNAS (ANCHO / TAMANO_CELDA)   // 40 columnas
#define FILAS (ALTO / TAMANO_CELDA)       // 30 filas
#define MAX_SEGMENTOS 100    // Límite de la serpiente (por si se vuelve muy larga)

// ============================================================
//  ESTRUCTURAS
// ============================================================
typedef struct {
    int x;   // Posición en la cuadrícula (columna)
    int y;   // Posición en la cuadrícula (fila)
} Segmento; 
void reiniciar_juego(Segmento serpiente[], int *longitud, int *dir_x, int *dir_y,
                     int *comida_x, int *comida_y, float *intervalo) {
    *longitud = 3;
    
    serpiente[0].x = COLUMNAS / 2;
    serpiente[0].y = FILAS / 2;
    serpiente[1].x = COLUMNAS / 2 - 1;
    serpiente[1].y = FILAS / 2;
    serpiente[2].x = COLUMNAS / 2 - 2;
    serpiente[2].y = FILAS / 2;
    
    *dir_x = 1;
    *dir_y = 0;
    
    *comida_x = GetRandomValue(0, COLUMNAS - 1);
    *comida_y = GetRandomValue(0, FILAS - 1);
    
    *intervalo = 0.15f;
} // Cada segmento del cuerpo de la serpiente

// ============================================================
//  FUNCIÓN PRINCIPAL
// ============================================================
int main() {
    // 1. Inicializar ventana
    

    InitWindow(ANCHO, ALTO, "Anaconda XD");
    SetTargetFPS(60);  // Limitamos a 60 FPS para no consumir recursos de más

    // 2. Variables del juego
    EstadoJuego estado = MENU; 
    int seleccion = 0; // Arrancamos en el menú

    // --- Serpiente ---
    Segmento serpiente[MAX_SEGMENTOS];
    int longitud = 3;  // Empieza con 3 segmentos

    // Posición inicial (centro de la pantalla)
    serpiente[0].x = COLUMNAS / 2;
    serpiente[0].y = FILAS / 2;
    serpiente[1].x = COLUMNAS / 2 - 1;
    serpiente[1].y = FILAS / 2;
    serpiente[2].x = COLUMNAS / 2 - 2;
    serpiente[2].y = FILAS / 2;

    // Dirección inicial: hacia la derecha
    int dir_x = 1;
    int dir_y = 0;

    // --- Comida ---
    int comida_x = GetRandomValue(0, COLUMNAS - 1);
    int comida_y = GetRandomValue(0, FILAS - 1);

    // --- Control de movimiento ---
    float tiempo_ultimo_movimiento = 0;
    float intervalo = 0.15f;  // Segundos entre cada paso (velocidad del juego)

    // 3. Bucle principal del juego
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();  // Tiempo entre frames (para movimiento fluido)

        // 4. MÁQUINA DE ESTADOS
        switch (estado) {
            case MENU:
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawText("ANACONDA XD", 300, 100, 40, RAYWHITE);
    DrawText("Jugar", 350, 250, 30, (seleccion == 0) ? YELLOW : RAYWHITE);
    DrawText("Salir", 350, 300, 30, (seleccion == 1) ? YELLOW : RAYWHITE);
    EndDrawing();

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
        seleccion = (seleccion == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_ENTER)) {
        if (seleccion == 0) {
            reiniciar_juego(serpiente, &longitud, &dir_x, &dir_y,
                            &comida_x, &comida_y, &intervalo);
            estado = JUGANDO;
        } else if (seleccion == 1) {
            CloseWindow();
            return 0;
        }
    }
    break;

case GAME_OVER:
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawText("GAME OVER", 300, 200, 50, RED);
    DrawText(TextFormat("Puntaje final: %d", longitud - 3), 300, 280, 30, RAYWHITE);
    DrawText("Presiona ENTER para reiniciar", 250, 350, 20, LIGHTGRAY);
    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) {
        reiniciar_juego(serpiente, &longitud, &dir_x, &dir_y,
                        &comida_x, &comida_y, &intervalo);
        estado = JUGANDO;
    }
    break;


            case JUGANDO:
                // =============================================
                //  LÓGICA DEL JUEGO
                // =============================================

                // 4.1 Leer entrada del teclado (cambiar dirección)
                // Evita que la serpiente pueda girar sobre sí misma
                if (IsKeyPressed(KEY_UP) && dir_y != 1) {
                    dir_x = 0;
                    dir_y = -1;
                }
                if (IsKeyPressed(KEY_DOWN) && dir_y != -1) {
                    dir_x = 0;
                    dir_y = 1;
                }
                if (IsKeyPressed(KEY_LEFT) && dir_x != 1) {
                    dir_x = -1;
                    dir_y = 0;
                }
                if (IsKeyPressed(KEY_RIGHT) && dir_x != -1) {
                    dir_x = 1;
                    dir_y = 0;
                }

                // 4.2 Mover la serpiente (solo en intervalos de tiempo)
                tiempo_ultimo_movimiento += dt;
                if (tiempo_ultimo_movimiento >= intervalo) {
                    tiempo_ultimo_movimiento = 0;

                    // Guardar la última posición (para cuando crezca)
                    int ultima_x = serpiente[longitud - 1].x;
                    int ultima_y = serpiente[longitud - 1].y;

                    // Desplazar el cuerpo: cada segmento toma la posición del anterior
                    for (int i = longitud - 1; i > 0; i--) {
                        serpiente[i].x = serpiente[i - 1].x;
                        serpiente[i].y = serpiente[i - 1].y;
                    }

                    // Mover la cabeza en la dirección actual
                    serpiente[0].x += dir_x;
                    serpiente[0].y += dir_y;

                    // --- COLISIONES ---

                    // 4.3 Comida: si la cabeza toca la comida, crece y genera nueva comida
                    if (serpiente[0].x == comida_x && serpiente[0].y == comida_y) {
                        longitud++;
                        serpiente[longitud - 1].x = ultima_x;
                        serpiente[longitud - 1].y = ultima_y;
                        comida_x = GetRandomValue(0, COLUMNAS - 1);
                        comida_y = GetRandomValue(0, FILAS - 1);
                    }

                    // 4.4 Pared: si la cabeza sale de la pantalla → Game Over
                    if (serpiente[0].x < 0 || serpiente[0].x >= COLUMNAS ||
                        serpiente[0].y < 0 || serpiente[0].y >= FILAS) {
                        estado = GAME_OVER;
                    }

                    // 4.5 Cuerpo: si la cabeza choca con algún segmento → Game Over
                    for (int i = 1; i < longitud; i++) {
                        if (serpiente[0].x == serpiente[i].x &&
                            serpiente[0].y == serpiente[i].y) {
                            estado = GAME_OVER;
                        }
                    }
                }

                // =============================================
                //  DIBUJADO
                // =============================================
                BeginDrawing();
                ClearBackground(DARKGRAY);

                // Dibujar la serpiente (cabeza de color verde, cuerpo verde claro)
                for (int i = 0; i < longitud; i++) {
                    Color color = (i == 0) ? GREEN : LIME;
                    DrawRectangle(
                        serpiente[i].x * TAMANO_CELDA,
                        serpiente[i].y * TAMANO_CELDA,
                        TAMANO_CELDA - 1,  // Dejamos un pixel de separación
                        TAMANO_CELDA - 1,
                        color
                    );
                }

                // Dibujar la comida (roja)
                DrawRectangle(
                    comida_x * TAMANO_CELDA,
                    comida_y * TAMANO_CELDA,
                    TAMANO_CELDA - 1,
                    TAMANO_CELDA - 1,
                    RED
                );

                // Mostrar puntaje (longitud - 3 = cantidad de comida comida)
                DrawText(TextFormat("Puntaje: %d", longitud - 3), 10, 10, 20, RAYWHITE);

                EndDrawing();
                break;


        }
    }

    // 5. Cerrar ventana limpiamente
    CloseWindow();
    return 0;
}