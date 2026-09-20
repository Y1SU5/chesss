#include "raylib.h"

int main(void) {
    // Inicializar una ventana de 640x640 píxeles
    InitWindow(640, 640, "Mi Tablero con Raylib");
    SetTargetFPS(60);

    Color claro = (Color){ 240, 217, 181, 255 };
    Color oscuro = (Color){ 181, 136, 99, 255 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar la cuadrícula 8x8
        for (int f = 0; f < 8; f++) {
            for (int c = 0; c < 8; c++) {
                //dibuja la casilla
                Color colorCasilla = ((f + c) % 2 == 0) ? claro : oscuro;
                DrawRectangle(c * 80, f * 80, 80, 80, colorCasilla);

                
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}