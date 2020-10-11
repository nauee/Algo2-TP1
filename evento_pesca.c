#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
*   Postcondiciones: Devolvera un puntero a un pokemon con el nuevo pokemon agregado (en caso de poder), en caso contrario devolvera NULL.
*/
pokemon_t* agregar_pokemon(pokemon_t* pokemon, pokemon_t pokemon_agregar, int cantidad_actual){
    
    pokemon_t *nuevo_pokemon = realloc(pokemon, ((size_t)(cantidad_actual + 1) * sizeof(pokemon_t)));
    
    if (nuevo_pokemon == NULL) {
        return NULL;
    }

    pokemon = nuevo_pokemon;
    pokemon[cantidad_actual] = pokemon_agregar;
    return pokemon;
}

int leer_de_archivo (FILE* arch_arrecife, pokemon_t *pokemon) {
    char buffer[1024];
    char* linea = fgets(buffer, 1024, arch_arrecife);
    if (!linea) {
        return -1;
    }
    int leidos = sscanf(linea, FORMATO_ARRECIFE, (*pokemon).especie, &((*pokemon).velocidad), &((*pokemon).peso), (*pokemon).color);
    return leidos;
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
        fclose (arch_arrecife);
        return NULL;
    }

    pokemon_t pokemon_leido;
    arrecife -> cantidad_pokemon = 0;
    bool error = false;
    int leidos = leer_de_archivo(arch_arrecife, &pokemon_leido);
    while (leidos == 4 && !error) {
        pokemon_t *nuevo_pokemon = agregar_pokemon(arrecife -> pokemon, pokemon_leido, arrecife -> cantidad_pokemon);
        if (nuevo_pokemon == NULL) {
            error = true;
        } else {
            (*arrecife).pokemon = nuevo_pokemon;
            ((*arrecife).cantidad_pokemon) ++;
        }
        leidos = leer_de_archivo(arch_arrecife, &pokemon_leido);
    }
    fclose (arch_arrecife);
    if (arrecife -> cantidad_pokemon == 0) {
        return NULL;
    }
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

/***************************************************************************************** Trasladar pokemon *****************************************************************************************/

int encontrar_pokemones_trasladar (arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*),int cant_seleccion, int* pos_trasladar, int* cant_trasladar) {
    int estado = 0;
    int i = 0;
    while (i < (*arrecife).cantidad_pokemon && estado == 0){
        if (seleccionar_pokemon(&(*arrecife).pokemon[i])) {
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

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {
    int* pos_trasladar = NULL;
    int cant_trasladar = 0;
    int estado = 0;
    estado = encontrar_pokemones_trasladar(arrecife, seleccionar_pokemon, cant_seleccion, pos_trasladar, &cant_trasladar);
    /*if (cant_trasladar < cant_seleccion && estado == 0) {
        free (pos_trasladar);
        return 0;
    }
    if (estado == 0) {
        estado = pasar_al_acuario(arrecife, acuario, pos_trasladar, cant_trasladar);
    }
    if (estado == 0) {
        estado = sacar_del_arrecife(arrecife, pos_trasladar, cant_trasladar);
    }*/
    if (estado==-1){
        printf("error");
    } else {
        for (int i = 0; i < cant_trasladar; i++) {
            printf("%i - ", pos_trasladar[i]);
        }
    }
    free (pos_trasladar);
    return estado;
}


/****************************************************************************************** Censar arrecife ******************************************************************************************/

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
    
    printf("|         Especie         | Velocidad |   Peso   |          Color          |\n");
    for (int i = 0; i < (arrecife -> cantidad_pokemon); i++) {
        mostrar_pokemon(&((*arrecife).pokemon[i]));
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