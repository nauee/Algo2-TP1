#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

#define RUTA_ESCRITURA_DEFECTO "acuario.txt"
#define RUTA_LECTURA_DEFECTO "arrecife.txt"

void mostrar_pokemon (pokemon_t* pokemon) {
    printf("|  %-23s", (pokemon -> especie));
    printf("|    %-3i    ", (pokemon -> velocidad));
    printf("|    %-3i   ", (pokemon -> peso));
    printf("|  %-23s", (pokemon -> color));
    printf("|\n");
}

bool rompe_la_red (pokemon_t* pokemon){
    return ((*pokemon).peso > 80);
}

bool es_peso_pluma (pokemon_t* pokemon){
    return ((*pokemon).peso < 5);
}
bool es_naranja (pokemon_t* pokemon){
    return ((strcmp((*pokemon).color, "naranja") == 0) || (strcmp((*pokemon).color, "Naranja") == 0));
}

bool empieza_con_a (pokemon_t* pokemon){
    return (((*pokemon).especie)[0] == 'A' || ((*pokemon).especie)[0] == 'a');
}

bool es_magikarp (pokemon_t* pokemon){
    return ((strcmp((*pokemon).especie, "magikarp") == 0) || (strcmp((*pokemon).especie, "Magikarp") == 0));
}

char* determinar_ruta(int argc, char** argv, char* ruta, int argumento){
    char* tmp = NULL;
    if (argc == argumento + 1) {
        tmp = realloc(ruta, strlen(argv[argumento]) + 1);
        if (tmp != NULL) {
            ruta = tmp;
            strcpy (ruta, argv[argumento]);
            return ruta;
        }
    } else {
        if (argumento == 1){
            tmp = realloc(ruta, strlen(RUTA_LECTURA_DEFECTO) + 1);
            if (tmp != NULL) {
                ruta = tmp;
                strcpy (ruta, RUTA_LECTURA_DEFECTO);
                return ruta;
            }   
        } else {
            tmp = realloc(ruta, strlen(RUTA_ESCRITURA_DEFECTO) + 1);
            if (tmp != NULL) {
                ruta = tmp;
                strcpy (ruta, RUTA_ESCRITURA_DEFECTO);
                return ruta;
            }
        }
    }
    return NULL;
}

int main (int argc, char** argv) {

    char* ruta_lectura = NULL;
    char* ruta_escritura = NULL;
    ruta_lectura = determinar_ruta(argc, argv, ruta_lectura, 1);
    ruta_escritura = determinar_ruta(argc, argv, ruta_escritura, 2);
    bool (*seleccionar_pokemon[5]) (pokemon_t*);
    seleccionar_pokemon[0] = rompe_la_red;
    seleccionar_pokemon[1] = es_peso_pluma;
    seleccionar_pokemon[2] = es_naranja;
    seleccionar_pokemon[3] = empieza_con_a;
    seleccionar_pokemon[4] = es_magikarp;

    arrecife_t *arrecife = crear_arrecife(ruta_lectura);
    if (arrecife == NULL) {
        return -1;
    }
    acuario_t *acuario = crear_acuario();
    if (acuario == NULL) {
        return -1;
    }
    int cantidad_requerida = 7;
    for(int i = 0; i < 5; i++) {
        trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], cantidad_requerida);
        censar_arrecife(arrecife, mostrar_pokemon);
        getchar();
    }
    censar_arrecife(arrecife, mostrar_pokemon);
    guardar_datos_acuario(acuario, ruta_escritura);
    free(ruta_lectura);
    free(ruta_escritura);
    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
    return 0;
}