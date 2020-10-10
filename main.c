#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

int main () {
    arrecife_t *arrecife_prueba = crear_arrecife("texto.txt");
    printf("%i\n", (*arrecife_prueba).cantidad_pokemon);
    printf("%p\n", arrecife_prueba);
    for (int i = 0; i < (*arrecife_prueba).cantidad_pokemon; i++) {
        printf("%s\n",(*arrecife_prueba).pokemon[i].especie);
        printf("%i\n",(*arrecife_prueba).pokemon[i].velocidad);
        printf("%i\n",(*arrecife_prueba).pokemon[i].peso);
        printf("%s\n",(*arrecife_prueba).pokemon[i].color);
        printf("------------\n");
    }
    free(arrecife_prueba);
}