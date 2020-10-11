#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "evento_pesca.h"

void sacar(int vector[10], int eliminar[4], int *tope_vector, int cant_eliminar) {
    for (int i = 0; i < *tope_vector; i++){
        int cantidad_a_mover = 0;
        for (int j = 0; j < cant_eliminar; j++){
            if (i > eliminar[j]) {
                cantidad_a_mover = j + 1;
            }
        }
        vector[i - cantidad_a_mover] = vector[i];
        for(int i = 0; i < *tope_vector ;i++){
            printf("%i-",vector[i]);
        }
        getchar();
    }
    (*tope_vector) -= cant_eliminar;
}

int* sacar_heap(int* vector, int* eliminar, int tope_vector, int tope_eliminar) {
    for (int i = 0; i < tope_vector; i++) {
        int cantidad_a_mover = 0;
        for (int j = 0; j < tope_eliminar; j++) {
            if (i > eliminar[j]) {
                cantidad_a_mover = j + 1;
            }
        }
        vector[i - cantidad_a_mover] = vector[i];
    }
    int* nuevo_vector = realloc (vector, sizeof(int) * (tope_vector - tope_eliminar));
    return nuevo_vector;
}

int encontrar_eliminar (int* vector, int tope_vector, int* pos_trasladar, int* cant_trasladar) {
    int estado = 0;
    int i = 0;
    while (i < tope_vector && estado == 0){
        if (vector[i] % 3 == 0) {
            int* nueva_pos_trasladar = NULL;
            nueva_pos_trasladar = realloc (pos_trasladar, (sizeof(int))); 
            if (nueva_pos_trasladar != NULL) {
                pos_trasladar = nueva_pos_trasladar;
                (*cant_trasladar) ++;
            } else {
                estado = -1;
            }
        }
        i++;
    }
    return estado;
}

int* agregar_posicion(int* posiciones, int pos, int cant_pos){
    
    int *tmp = realloc(posiciones, ((size_t)(cant_pos + 1) * sizeof(int)));
    
    if (tmp == NULL) {
        return NULL;
    }

    posiciones = tmp;
    posiciones[cant_pos] = pos;
    return posiciones;
}

int* agregar_pos(int* posiciones, int cant_posiciones, int posicion) {
    
    int *tmp = realloc(posiciones, ((size_t)(cant_posiciones + 1) * sizeof(int)));
    if (tmp == NULL) {
        return NULL;
    }
    posiciones = tmp;
    posiciones[cant_posiciones] = posicion;
    return posiciones;
}

int pasar(int* vector, int tope, int** posiciones, int* cant_pos, int cant_selecc) {
    int i = 0;
    bool error = false;
    while (i < tope && (*cant_pos) < cant_selecc && !error) {
        if (vector[i] % 3 == 0){
            int *tmp = agregar_posicion(*posiciones, i, *cant_pos);
            if (tmp == NULL) {
                error = true;
            } else {
                *posiciones = tmp;
                (*cant_pos) ++;
            }
        }
        i++;
    }
    return 0;
}


int main() {
    int tope_vector = 10;
    int* vector = malloc (sizeof(int) * tope_vector);
    vector[0] = 0;
    vector[1] = 1;
    vector[2] = 2;
    vector[3] = 3;
    vector[4] = 4;
    vector[5] = 5;
    vector[6] = 6;
    vector[7] = 7;
    vector[8] = 8;
    vector[9] = 9;
    int* posiciones = NULL;
    int i = 0;
    int cant_pos = 0;
    int cant_selecc = 3;
    int estado = pasar(vector, tope_vector, &posiciones, &cant_pos, cant_selecc);
    //int *tmp = agregar_posicion(posiciones, 1, cant_pos);
   /*if (tmp == NULL) {
        return -1;
    } else {
        posiciones = tmp;
        (cant_pos) ++;
     }*/
    for(int i = 0; i < cant_pos ;i++){
        printf("%i-",posiciones[i]);
    }
    return 0;
}