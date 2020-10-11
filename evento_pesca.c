#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

/******************************************************************************************** Constantes *********************************************************************************************/

#define FORMATO_ARRECIFE "%[^;];%i;%i;%[^\n]\n"

/*
    typedef struct arrecife {
        pokemon_t* pokemon;
        int cantidad_pokemon;
    } arrecife_t;

    typedef struct pokemon{
        char especie[MAX_ESPECIE];
        int velocidad;
        int peso;
        char color[MAX_COLOR];
    } pokemon_t;

    typedef struct acuario{
        pokemon_t* pokemon;
        int cantidad_pokemon;
    } acuario_t;
*/
/****************************************************************************************** Crear arrecife *******************************************************************************************/

/*
*   Precondiciones: Debe recibir un pokemon leido valido, un puntero a un pokemon valido y una cantidad actual mayor o igual a 0.
*   Postcondiciones: Devolvera un puntero a un pokemon con el nuevo pokemon agregado (en caso de poder), en caso contrario devolvera el puntero que recibió.
*/
pokemon_t* agregar_pokemon(pokemon_t* pokemon, pokemon_t pokemon_leido, int cantidad_actual){
    
    pokemon_t *nuevo_pokemon = realloc(pokemon, (cantidad_actual + 1) * sizeof(pokemon_t));
    
    if (nuevo_pokemon == NULL) {
        return pokemon;
    }

    pokemon = nuevo_pokemon;
    pokemon[cantidad_actual] = pokemon_leido;
    return pokemon;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){
    
    if (ruta_archivo[0] == 0){
        return NULL;
    }

    FILE* arch_arrecife = fopen (ruta_archivo, "r");
    if (!arch_arrecife) {
        return NULL;
    }

    arrecife_t *arrecife = malloc(sizeof(arrecife_t));
    if (arrecife == NULL) {
        return NULL;
    }

    pokemon_t pokemon_leido;
    arrecife -> cantidad_pokemon = 0;
    int leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
    while (leidos == 4) {
        pokemon_leido.color[strlen(pokemon_leido.color) - 1] = 0;
        (arrecife -> pokemon) = agregar_pokemon(arrecife -> pokemon, pokemon_leido, arrecife -> cantidad_pokemon);
        (arrecife -> cantidad_pokemon) ++;
        leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
    }

    if (arrecife -> cantidad_pokemon == 0) {
        return NULL;
    }

    fclose (arch_arrecife);
    return arrecife;

}

/******************************************************************************************  Crear acuario *******************************************************************************************/

acuario_t* crear_acuario () {
    acuario_t* acuario = malloc (sizeof(acuario_t));
    if (acuario == NULL) {
        return NULL;
    }
    (acuario -> pokemon) = NULL;
    (acuario -> cantidad_pokemon) = 0;
    return acuario;
}

/****************************************************************************************** Censar arrecife ******************************************************************************************/

void mostrar_pokdemon (pokemon_t* pokemon) {
    printf("|%-15s", pokemon -> especie);
    printf("|%-3i", pokemon -> peso);
    printf("|%-3i", pokemon -> velocidad);
    printf("|%-15s", pokemon -> color);
    printf("|\n");
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
    
    printf("|         Especie         | Velocidad |   Peso   |          Color          |\n");
    for (int i = 0; i < (arrecife -> cantidad_pokemon); i++) {
        mostrar_pokdemon(&((*arrecife).pokemon[i]));
    }
    printf("En total hay %i pokemones", arrecife -> cantidad_pokemon);
}

/****************************************************************************************** Liberar acuario ******************************************************************************************/

void liberar_acuario(acuario_t* acuario) {
    free (acuario -> pokemon);
    free (acuario);
}

/***************************************************************************************** Liberar arrecife ******************************************************************************************/

void liberar_arrecife(arrecife_t* arrecife){
    free (arrecife -> pokemon);
    free (arrecife);
}

/*****************************************************************************************************************************************************************************************************/