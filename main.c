#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

void mostrar_pokemon (pokemon_t* pokemon) {
    printf("|%-15s", (pokemon -> especie));
    printf("|%-3i", (pokemon -> peso));
    printf("|%-3i", (pokemon -> velocidad));
    printf("|%s", (pokemon -> color));
    printf("%li", strlen(pokemon -> color));
    printf("|\n");
}

int main () {
    arrecife_t *arrecife = crear_arrecife("arrecife.txt");
    censar_arrecife(arrecife, mostrar_pokemon);
    liberar_arrecife(arrecife);
    acuario_t *acuario = crear_acuario();
    liberar_acuario(acuario);
}