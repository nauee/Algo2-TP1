#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

void mostrar_pokemon (pokemon_t* pokemon) {
    printf("|  %-23s", (pokemon -> especie));
    printf("|    %-3i    ", (pokemon -> velocidad));
    printf("|    %-3i   ", (pokemon -> peso));
    printf("|  %-23s", (pokemon -> color));
    printf("|\n");
}

bool prueba_seleccion (pokemon_t* pokemon){
    if ((*pokemon).velocidad == 50) {
        return true;
    } else {
        return false;
    }
}

int main () {
    //char* ruta_archivo = determinar_ruta (args, argc);
    char* ruta_archivo = "arrecife.txt";
    arrecife_t *arrecife = crear_arrecife(ruta_archivo);
    if (arrecife == NULL) return -1;
    acuario_t *acuario = crear_acuario();
    if (acuario == NULL) return -1;
    censar_arrecife(arrecife, mostrar_pokemon);
    trasladar_pokemon(arrecife, acuario, prueba_seleccion, 5);
    getchar();
    system("clear");
    for (int i = 0; i < (*acuario).cantidad_pokemon; i++) {
        mostrar_pokemon(&((*acuario).pokemon[i]));
    }
    printf("\n\n");
    censar_arrecife(arrecife, mostrar_pokemon);
    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
}