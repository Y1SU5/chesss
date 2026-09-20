#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//incluir el tablero grafico
#include "raylib.h"

#define TAM_CASILLA 80
#define TAM_FICHA 48
#define MARGEN ((TAM_CASILLA - TAM_FICHA) / 2.0f)

//principal(Danielle)
#define DJM 0x44616E69656C6C65ULL

//struct general para todas las fichas
typedef struct{
    char sbl;
    int color;
    int fil;
    int col;
    int move;
}pieza;

//struct para el tablero grafico
typedef struct {
    Texture2D w_a, w_c, w_t, w_k, w_q, w_p;
    Texture2D b_a, b_c, b_t, b_k, b_q, b_p;
}TexturasAjedrez;


//prototipos

//tablero grafico
//dibujar el tablero(tablero)
    void dibujar_ficha(Texture2D tex,int f, int c);
//dibujar tablero grafico
    void dibujar_tablero_grafico(void);
//dibujar todas las fichas
    void dibujar_todas_las_fichas(pieza tab[8][8], TexturasAjedrez tex);
    
//tablero terminal
//inicar tablero
    void iniciar_tablero(pieza tab[8][8]);
//tablero
    void prt_tbs(pieza tab[8][8]);
//validar  
    int vltr(char pos[]);
//manda cual es la funcion que se usara
    int es_movimiento_valido(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//dibujar casilla
    void dibujar_posibles_movimientos(pieza tab[8][8], int org_f, int org_c);
//cambio de posicion   
    void chg_pos(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar el moviento de los peones
    int vltr_peon(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar movimiento de las torres
    int vltr_torre(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar el movimiento de los caballos
    int vltr_cbll(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar movimiento de los alfiles
    int vltr_alfl(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar movimiento de los reyes
    int vltr_rey(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar movimiento de las reinas
    int vltr_reina(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);

int main(void){
    //inicializar la ventana
    InitWindow(8 * TAM_CASILLA, 8 * TAM_CASILLA, "Tablero de Ajedrez");
    SetTargetFPS(60);
    // Cargar texturas desde tus carpetas
    TexturasAjedrez tex;
    tex.w_a = LoadTexture("fichas/f_wth/w_a.png");
    tex.w_c = LoadTexture("fichas/f_wth/w_c.png");
    tex.w_k = LoadTexture("fichas/f_wth/w_k.png");
    tex.w_p = LoadTexture("fichas/f_wth/w_p.png");
    tex.w_q = LoadTexture("fichas/f_wth/w_q.png");
    tex.w_t = LoadTexture("fichas/f_wth/w_t.png");

    tex.b_a = LoadTexture("fichas/f_blk/b_a.png");
    tex.b_c = LoadTexture("fichas/f_blk/b_c.png");
    tex.b_k = LoadTexture("fichas/f_blk/b_k.png");
    tex.b_p = LoadTexture("fichas/f_blk/b_p.png");
    tex.b_q = LoadTexture("fichas/f_blk/b_q.png");
    tex.b_t = LoadTexture("fichas/f_blk/b_t.png");
    

    //declarar el nuevo tablero de tipo struct
    pieza tab[8][8];
    //inicar tablero
    iniciar_tablero(tab);
    //mostrar tablero
    prt_tbs(tab);
    
    //crear variables para recordar la seleccion(antes del while
    bool pieza_seleccionada = false;
    int org_f = -1, org_c = -1;

    //crear el bucle
    //cambiamos el true dentro del while

    while(!WindowShouldClose()){

        //detectar el click del mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouse = GetMousePosition();
            int f = (int)(mouse.y / TAM_CASILLA);
            int c = (int)(mouse.x / TAM_CASILLA);
            
            if (!pieza_seleccionada){
                //primer click(si la casilla no esta vacia)
                if (tab[f][c].sbl != '_'){
                    org_f = f;
                    org_c = c;
                    pieza_seleccionada = true;
                }
            }
            else {
                //segundo click, el origen es f y c
                int chg_f = f;
                int chg_c = c;

                //si es valido se mueve; si no, simplemente no hace nada
                if(es_movimiento_valido(tab, org_f, org_c, chg_f, chg_c)){
                    chg_pos(tab, org_f, org_c, chg_f, chg_c);
                }

                //reiniciar para la siguiente seleccion
                pieza_seleccionada = false;

            }
        }  
        BeginDrawing();
            ClearBackground(RAYWHITE);
            dibujar_tablero_grafico();
            if(pieza_seleccionada){
                //resalta casilla de la pieza que se toca
                DrawRectangle(org_c * TAM_CASILLA, org_f * TAM_CASILLA, TAM_CASILLA, TAM_CASILLA, (Color){255, 255, 0, 100});
                //dibuja los posibles movimientos 
                dibujar_posibles_movimientos(tab, org_f, org_c);

            }
            dibujar_todas_las_fichas(tab, tex);
        EndDrawing();

    }//cierra el while

    //liberar recursos al cerrar la ventana
    UnloadTexture(tex.w_a); UnloadTexture(tex.w_c); UnloadTexture(tex.w_k);
    UnloadTexture(tex.w_p); UnloadTexture(tex.w_q); UnloadTexture(tex.w_t);
    UnloadTexture(tex.b_a); UnloadTexture(tex.b_c); UnloadTexture(tex.b_k);
    UnloadTexture(tex.b_p); UnloadTexture(tex.b_q); UnloadTexture(tex.b_t);
    
    CloseWindow();

    return 0;
}


//FUNCIONES IMPORTANTES


//iniciar tablero
void iniciar_tablero(pieza tab[8][8]){
    //luego de crear el tablero de 8x8 creamos hacemos la distribucion
    //hacemos esto para dejar la funcion principal(main) limpia y se pueda entender
    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            tab[j][i].sbl = '_';
            tab[j][i].color = -1;
            tab[j][i].fil = j;
            tab[j][i].col = i;
            tab[j][i].move = 0;
        }
    }

    //piezas negras(1)
        //torre
        tab[0][0] = (pieza){'T', 1, 0, 0, 0};
        //caballo
        tab[0][1] = (pieza){'C', 1, 0, 1, 0};
        ///alfil
        tab[0][2] = (pieza){'A', 1, 0, 2, 0};
        //reina
        tab[0][3] = (pieza){'Q', 1, 0, 3, 0};
        //rey
        tab[0][4] = (pieza){'K', 1, 0, 4, 0};
        //alfil
        tab[0][5] = (pieza){'A', 1, 0, 5, 0};
        //caballo
        tab[0][6] = (pieza){'C', 1, 0, 6, 0};
        //torre
        tab[0][7] = (pieza){'T', 1, 0, 7, 0};

    //piezas blancas(0)
        //torre
        tab[7][0] = (pieza){'t', 0, 7, 0, 0};
        //caballo
        tab[7][1] = (pieza){'c', 0, 7, 1, 0};
        ///alfil
        tab[7][2] = (pieza){'a', 0, 7, 2, 0};
        //reina
        tab[7][3] = (pieza){'q', 0, 7, 3, 0};
        //rey
        tab[7][4] = (pieza){'k', 0, 7, 4, 0};
        //alfil
        tab[7][5] = (pieza){'a', 0, 7, 5, 0};
        //caballo
        tab[7][6] = (pieza){'c', 0, 7, 6, 0};
        //torre
        tab[7][7] = (pieza){'t', 0, 7, 7, 0};
    //poner peones negros(1)
    for(int i = 0; i < 8; i++){
        tab[1][i] = (pieza){'P', 1, 1, i, 0};
    }
    //ponrt peones blancos(0)
    for (int i = 0; i < 8; i++){
        tab[6][i] = (pieza){'p', 0, 6, i, 0};
    }

}



//dibujar el tablero(tablero)
void dibujar_ficha(Texture2D tex,int f, int c){
    Rectangle fuente = {0.0f, 0.0f, (float)tex.width, (float)tex.height};
    //posicion de la ficha + el margen para dejarla perfectamente centrada
    Rectangle destino = {
        (float)(c * TAM_CASILLA) + MARGEN, 
        (float)(f * TAM_CASILLA) + MARGEN, 
        (float)TAM_FICHA,
        (float)TAM_FICHA
    };

    DrawTexturePro(tex, fuente, destino, (Vector2){ 0, 0 }, 0.0f, WHITE);
}

//dibujar tablero grafico
void dibujar_tablero_grafico(void){
    Color claro = (Color){ 240, 217, 181, 255 };
    Color oscuro = (Color){ 181, 136, 99, 255 };

    for (int f = 0; f < 8; f++){
        for (int c = 0; c < 8; c++){
            Color colCasilla = ((f + c) % 2 == 0) ? oscuro : claro;
            DrawRectangle(c * TAM_CASILLA, f * TAM_CASILLA, TAM_CASILLA, TAM_CASILLA, colCasilla);

            Color colTexto = ((f + c) % 2 == 0) ? claro : oscuro;
            //numeros a la izquierda (arriba en la casilla)
            if (c == 0){
                char num[2] = { (char)('8' - f), '\0' };
                DrawText(num, c * TAM_CASILLA + 4,f * TAM_CASILLA + 4, 16, colTexto);
            }
            //letras abajo(esquina inferior derecha de la esquina)
            if (f == 7){
                char letra[2] = { (char)('a' + c), '\0' };
                DrawText(letra, c * TAM_CASILLA + (TAM_CASILLA - 14), f * TAM_CASILLA + (TAM_CASILLA - 20), 16, colTexto);
            }
        }
    }
}

//dibujar todas las fichas
void dibujar_todas_las_fichas(pieza tab[8][8], TexturasAjedrez tex){
    for (int f = 0; f < 8; f++){
        for (int c = 0; c < 8; c++){
            char s = tab[f][c].sbl;
            int col = tab[f][c].color;

            if (col == 0){
                if (s == 'p' || s == 'P') dibujar_ficha(tex.w_p, f, c);
                else if (s == 't' || s == 'T') dibujar_ficha(tex.w_t, f, c);
                else if (s == 'c' || s == 'C') dibujar_ficha(tex.w_c, f, c);
                else if (s == 'a' || s == 'A') dibujar_ficha(tex.w_a, f, c);
                else if (s == 'q' || s == 'Q') dibujar_ficha(tex.w_q, f, c);
                else if (s == 'k' || s == 'K') dibujar_ficha(tex.w_k, f, c);
            }
            else if (col == 1){
                if (s == 'P' || s == 'p') dibujar_ficha(tex.b_p, f, c);
                else if (s == 'T' || s == 't') dibujar_ficha(tex.b_t, f, c);
                else if (s == 'C' || s == 'c') dibujar_ficha(tex.b_c, f, c);
                else if (s == 'A' || s == 'a') dibujar_ficha(tex.b_a, f, c);
                else if (s == 'Q' || s == 'q') dibujar_ficha(tex.b_q, f, c);
                else if (s == 'K' || s == 'k') dibujar_ficha(tex.b_k, f, c);
            }
        }
    }
}

//tablero
void prt_tbs(pieza tab[8][8]){
    printf("\n   a b c d e f g h\n"); 
    printf("   _ _ _ _ _ _ _ _\n");

    for(int j = 0; j < 8; j++){
        printf("%d| ", 8 - j);
        for(int i = 0; i < 8; i++){
            printf("%c ", tab[j][i].sbl);
        }
        printf("\n");
    }
    printf("\n");
}

//validar
int vltr(char pos[]){
    if (pos[0] < 'a' || pos[0] > 'h'){
        return 1;
    }
    if (pos[1] < '1' || pos[1] > '8'){
        return 1;
    }
    return 0;
}

//cambiar de posicion
void chg_pos(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c) {
    tab[chg_f][chg_c] = tab[org_f][org_c];
    tab[chg_f][chg_c].fil = chg_f;
    tab[chg_f][chg_c].col = chg_c;
    tab[chg_f][chg_c].move++;

    tab[org_f][org_c].sbl = '_';
    tab[org_f][org_c].color = -1;
    tab[org_f][org_c].move = 0;
}


//movimiento valido
int es_movimiento_valido(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c) {
    char s = tab[org_f][org_c].sbl;

    if (s == 'p' || s == 'P') return vltr_peon(tab, org_f, org_c, chg_f, chg_c) == 0;
    if (s == 't' || s == 'T') return vltr_torre(tab, org_f, org_c, chg_f, chg_c) == 0;
    if (s == 'c' || s == 'C') return vltr_cbll(tab, org_f, org_c, chg_f, chg_c) == 0;
    if (s == 'a' || s == 'A') return vltr_alfl(tab, org_f, org_c, chg_f, chg_c) == 0;
    if (s == 'q' || s == 'Q') return vltr_reina(tab, org_f, org_c, chg_f, chg_c) == 0;
    if (s == 'k' || s == 'K') return vltr_rey(tab, org_f, org_c, chg_f, chg_c) == 0;

    return 0;
}


//validar movimiento de los peones
int vltr_peon(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    int dif_f = chg_f - org_f;
    int dif_c = chg_c - org_c;
    //peones blancos
    if (tab[org_f][org_c].color == 0){
        //movimiento recto
        if (dif_c == 0){
            //un paso al frente
            if (dif_f == -1 && tab[chg_f][chg_c].sbl == '_'){
                return 0;
            }
            //dos pasos al frente
            if (dif_f == -2 && tab[org_f][org_c].move == 0 && tab[chg_f][chg_c].sbl=='_' && tab[org_f-1][org_c].sbl=='_'){
                return 0;
            }
        }
        //comer en diagonal
        /*logicamente esto : (dif_c == 1 || dif_f == -1) && dif_f == -1, se reduce a esto:
        dif_f == -1  */
        if (dif_f == -1 && (dif_c == 1 || dif_c == -1)){
            if (tab[chg_f][chg_c].sbl != '_' && tab[chg_f][chg_c].color != 0){
                return 0;
            }
        }
    }

    //peones negros
    if (tab[org_f][org_c].color == 1){
        //movimiento recto
        if (dif_c == 0){
            //un paso al frente
            if (dif_f == 1 && tab[chg_f][chg_c].sbl == '_'){
                return 0;
            }
            //dos pasos al frente
            if (dif_f == 2 && tab[org_f][org_c].move == 0 && tab[chg_f][chg_c].sbl == '_' && tab[org_f+1][org_c].sbl == '_'){
                return 0;
            }
        }
        //comer en diagonal
        /*logicamente: (dif_f == 1 || dif_c == 1) && dif_f ==-1 se reduce a :
        dif_f == 1  */
        if (dif_f == 1 && (dif_c == 1 || dif_c == -1)){
            if (tab[chg_f][chg_c].sbl != '_' && tab[chg_f][chg_c].color != 1){
                return 0;
            }
        }
    }
    return 1;
}


//validar movimiento de las torres
int vltr_torre(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    int dif_f = chg_f - org_f; 
    int dif_c = chg_c - org_c;
    //torre solo se mueve en horizontal o vertical(nunca en ambas)
    if (dif_f != 0 && dif_c != 0){
        return 1;
    }
    //movimiento vertical
    if (dif_c == 0){
        //sube
        if (dif_f < 0){
            for(int i = org_f - 1; i > chg_f; i--){
                if(tab[i][org_c].sbl != '_'){
                    return 1;
                }
            }
        }
        //baja
        if (dif_f > 0){
            for (int i = org_f + 1; i < chg_f; i++){
                if(tab[i][org_c].sbl != '_'){
                    return 1;
                }
            }
        }
    }
    //movimiento horizontal
    if (dif_f == 0){
        //derecha
        if (dif_c > 0){
            for (int  i = org_c + 1;i < chg_c; i++){
                if (tab[org_f][i].sbl != '_'){
                    return 1;
                }
            }
        }
        //izquierda
        if (dif_c < 0){
            for (int i = org_c - 1;i > chg_c; i--){
                if (tab[org_f][i].sbl != '_'){
                    return 1;
                }
            }
        }
    }
    //validar casilla de destino final
    if (tab[chg_f][chg_c].sbl != '_' && tab[chg_f][chg_c].color == tab[org_f][org_c].color) {
        return 1;
    }
    return 0;
}


//validar el movimiento de los caballos
int vltr_cbll(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    int dif_f = chg_f - org_f;
    int dif_c = chg_c - org_c;
    
    //caballo negro
    if (abs(dif_c * dif_f) == 2){
        if (tab[chg_f][chg_c].color != tab[org_f][org_c].color){
            return 0;
        }
    }
    return 1;
}


//validar el movimiento de los alfiles
int vltr_alfl(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    int dif_f = chg_f - org_f;
    int dif_c = chg_c - org_c;

    //validar movimiento diagonal
    if(abs(dif_c) != abs(dif_f)){
        return 1;
    }
    //direccion del movimiento
    int f_sgn = (dif_f > 0) ? 1 : -1;
    int c_sgn = (dif_c > 0) ? 1 : -1;

    //iniciar variables
    int f = org_f;
    int c = org_c;

    for (int i = 0; i < abs(dif_c) - 1; i++){
        f += f_sgn;
        c += c_sgn;
        if (tab[f][c].sbl != '_'){
            return 1;
        }
    }
    //destino o comer
    if(tab[chg_f][chg_c].sbl != '_' && tab[org_f][org_c].color == tab[chg_f][chg_c].color){
        return 1;
    }
    return 0;
}


//validar rey
int vltr_rey(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    int dif_f = chg_f - org_f;
    int dif_c = chg_c - org_c;
    //descartar que no se movio
    if (dif_f == 0 && dif_c == 0){
        return 1;
    }
    //no puede avanzar mas de una casilla
    if (abs(dif_f) > 1 || abs(dif_c)>1){
        return 1;
    }
    //validar llegada
    if (tab[chg_f][chg_c].sbl != '_' && tab[org_f][org_c].color == tab[chg_f][chg_c].color){
        return 1;
    }
    return 0;
}


//validar reina
int vltr_reina(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c){
    if (vltr_torre(tab, org_f, org_c, chg_f, chg_c) == 0 || vltr_alfl(tab, org_f, org_c, chg_f, chg_c) == 0){
        return 0;
    }
    return 1;
}

//dibujar posibles movimientos
void dibujar_posibles_movimientos(pieza tab[8][8], int org_f, int org_c) {
    Color colPunto = (Color){ 0, 0, 0, 80 };     // Círculo grisáceo/oscuro translúcido

    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            // Evaluamos si el movimiento desde (org_f, org_c) hasta (f, c) es legal
            if (es_movimiento_valido(tab, org_f, org_c, f, c)) {
                int centroX = c * TAM_CASILLA + (TAM_CASILLA / 2);
                int centroY = f * TAM_CASILLA + (TAM_CASILLA / 2);

                if (tab[f][c].sbl == '_') {
                    // Casilla vacía: un puntito en el centro
                    DrawCircle(centroX, centroY, 12, colPunto);
                } else {
                    // Hay pieza enemiga: un aro o anillo exterior que indica captura
                    DrawCircleLines(centroX, centroY, (TAM_CASILLA / 2) - 4 , (Color){ 200, 50, 50, 180 });
                }
            }
        }
    }
}