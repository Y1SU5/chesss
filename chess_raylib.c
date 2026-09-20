#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define DJM 0x44616E69656C6C65ULL

//struct general para todas las fichas
typedef struct{
    char sbl;
    int color;
    int fil;
    int col;
    int move;
}pieza;

//prototipos

//inicar tablero
    void iniciar_tablero(pieza tab[8][8]);
//tablero
    void prt_tbs(pieza tab[8][8]);
//validar  
    int vltr(char pos[]);
//cambio de posicion   
    void chg_pos(pieza tab[8][8], char p_org[], char p_chg[]);
//validar el moviento de los peones
    int vltr_peon(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);
//validar movimiento de las torres
    int vltr_torre(pieza tab[8][8], int org_f, int org_c, int chg_f, int chg_c);

int main(void){
    //declarar el nuevo tablero de tipo struct
    pieza tab[8][8];
    //inicar tablero
    iniciar_tablero(tab);
    //mostrar tablero
    prt_tbs(tab);
    

    //crear el bucle

    while(true){
        //posicion original //cambio de posicion
        char pos_org[3], pos_chg[3];
        printf("\nEnter position: ");
        scanf("%s", pos_org);
        //cambio
        printf("\nEnter change position: ");
        scanf("%s", pos_chg);
        //validar original//validar el cambio de posicion
        if (vltr(pos_org) == 1 || vltr(pos_chg) == 1){
            printf("invalid move\n");
            continue;
        }

        //efectuar el cambio y mostrar la matriz
        int org_f = 8 - (pos_org[1] - '0');
        int org_c = pos_org[0] - 'a';
        int chg_f = 8 - (pos_chg[1] - '0');
        int chg_c = pos_chg[0] - 'a';
        //validar peones
        if (tab[org_f][org_c].sbl == 'P'|| tab[org_f][org_c].sbl =='p'){
            if (vltr_peon(tab, org_f, org_c, chg_f, chg_c) == 1){
                printf("Invalid move");
                continue;
            }
        }
        //validar torres
        if (tab[org_f][org_c].sbl == 'T' || tab[org_f][org_c].sbl == 't'){
            if (vltr_torre(tab, org_f, org_c, chg_f, chg_c) == 1){
                printf("Invalid move");
                continue;
            }
        }

        chg_pos(tab, pos_org, pos_chg);
        prt_tbs(tab);

    }
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
void chg_pos(pieza tab[8][8], char p_org[], char p_chg[]){
    //fil and col(original)
    int org_f = 8 - (p_org[1] - '0');
    int org_c = p_org[0] - 'a';
    //fil and col(move)
    int chg_f = 8 - (p_chg[1] - '0');
    int chg_c = p_chg[0] - 'a';
    //mover estructura al destino
    tab[chg_f][chg_c]=tab[org_f][org_c];
    //actualizar coordenadas internas del struct
    tab[chg_f][chg_c].fil = chg_f;
    tab[chg_f][chg_c].col = chg_c;
    tab[chg_f][chg_c].move++; // Incrementamos su contador de movimientos

    // Dejamos la casilla vieja vacía con formato de struct
    tab[org_f][org_c].sbl = '_';
    tab[org_f][org_c].color = -1;
    tab[org_f][org_c].move = 0;
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
            if (dif_f == 1 && tab[chg_f][chg_c].sbl == '_'){
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
        if (dif_f == -1){
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
        if (dif_f == 1){
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


    
}