#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

#define FORMATO_ARRECIFE "%[^;];%i;%i;%[^\n]\n"

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
/****************************************************************************************** Crear arrecife *******************************************************************************************/

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
    arrecife_t *arrecife = malloc(sizeof(arrecife_t));
    pokemon_t pokemon_leido;
    arrecife -> cantidad_pokemon = 0;
    int leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
    while (leidos == 4) {
        (arrecife -> pokemon) = agregar_pokemon(arrecife -> pokemon, pokemon_leido, arrecife -> cantidad_pokemon);
        (arrecife -> cantidad_pokemon) ++;
        leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
    }

    fclose (arch_arrecife);
    return arrecife;

}

