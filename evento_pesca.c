#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"
/*
 * Función que dado un archivo carga los pokémon que viven en el arrecife
 * reservando la memoria necesaria para el mismo. Se debe intentar leer la mayor
 * cantidad posible de registros del archivo. Al encontrar el primer registro
 * erróneo (o al llegar al final del archivo) se deben finalizar la lectura y
 * crear el arrecife con los pokémon leídos exitosamente. En caso de no
 * encontrar ningún registro con el formato correcto, se debe devolver error.
 * Devuelve un puntero a un arrecife válido o NULL en caso de error.
 * Es importante notar que tanto
 */

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
*/

// especie1;velocidad1;peso1;color1
#define FORMATO_ARRECIFE "%[^;];%i;%i;%[^\n]\n"

arrecife_t* agregar_pokemon(arrecife_t* arrecife, pokemon_t pokemon_leido){
    pokemon_t *nuevo_pokemon = realloc((*arrecife).pokemon, ((*arrecife).cantidad_pokemon + 1) * sizeof(pokemon_t));
    if (nuevo_pokemon == NULL) {
        return NULL;
    }
    (*arrecife).pokemon[(*arrecife).cantidad_pokemon] = pokemon_leido;
    ((*arrecife).cantidad_pokemon) ++;
    return arrecife;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){
    
    if (ruta_archivo[0] == 0){
        return NULL;
    }

    FILE* arch_arrecife = fopen (ruta_archivo, "r");
    arrecife_t *arrecife = malloc(sizeof(arrecife_t));
    pokemon_t pokemon_leido;
    int leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
    while (leidos == 4) {
        arrecife = agregar_pokemon(arrecife, pokemon_leido);
    }
    return arrecife;
}