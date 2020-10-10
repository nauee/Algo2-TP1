#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

int main () {
    arrecife_t *arrecife = crear_arrecife("arrecife.txt");
    printf("%p\n", arrecife);
    for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) {
        printf("%s\n",(*arrecife).pokemon[i].especie);
        printf("%i\n",(*arrecife).pokemon[i].velocidad);
        printf("%i\n",(*arrecife).pokemon[i].peso);
        printf("%s\n",(*arrecife).pokemon[i].color);
        printf("------------\n");
    }
    printf("%i\n", (*arrecife).cantidad_pokemon);
    liberar_arrecife(arrecife);
}