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
            nueva_pos_trasladar = realloc (pos_trasladar, (size_t)((*cant_trasladar) + 1) * (sizeof(int))); 
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


int main() {
    int tope_vector = 10;
    int tope_eliminar = 4;
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
    int* eliminar = malloc (sizeof(int) * tope_eliminar);
    encontrar_eliminar(vector, tope_vector, eliminar, &tope_eliminar);
    int* nuevo_vector = sacar_heap(vector, eliminar, tope_vector, tope_eliminar);
    if (nuevo_vector == NULL) {
        return -1;
    }
    vector = nuevo_vector;
    tope_vector -= tope_eliminar;
    free(eliminar);
    for(int i = 0; i < tope_vector ;i++){
        printf("%i-",vector[i]);
    }
    free(vector);
}