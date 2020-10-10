#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

int main () {
    arrecife_t *arrecife_prueba = crear_arrecife("texto.txt");
    printf("%p", arrecife_prueba);
    printf("%i", (*arrecife_prueba).cantidad_pokemon);
    for (int i = 0; i < (*arrecife_prueba).cantidad_pokemon; i++) {
        printf("%s",(*arrecife_prueba).pokemon[i].especie);
        printf("%i",(*arrecife_prueba).pokemon[i].velocidad);
        printf("%i",(*arrecife_prueba).pokemon[i].peso);
        printf("%s",(*arrecife_prueba).pokemon[i].color);
        printf("\n");
    }//comentario
}