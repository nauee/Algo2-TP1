#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

/******************************************************************************************** Constantes *********************************************************************************************/

#define FORMATO_ARRECIFE "%[^;];%i;%i;%[^\n]\n"
#define FORMATO_ACUARIO "%s;%i;%i;%s\n"

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

/*
*   Precondiciones: Debe recibir un archivo con el arrecife abierto correctamente.
*   Postcondiciones: Leera una linea del archiva y la guardara en 
*   los distintos campos del pokemon.
*/
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

/*
*   Precondiciones: Debe recibir un puntero a un arrecife valido, una puntero a funcion bool,
*   una cantidad maxima de pokemones, y un vector de posiciones a trasladar con su tope.
*   Postcondiciones: Llenara el vector de posiciones a trasladar con las posiciones de los pokemones
*   que hagan a la funcion bool devolver true. Devolvera -1 en caso de error y 0 en caso contrario.
*/
int encontrar_pokemones_trasladar (arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*),int cant_seleccion, int** pos_trasladar, int* cant_trasladar) {
    int estado = 0;
    int i = 0;
    while (i < (*arrecife).cantidad_pokemon && estado == 0 && (*cant_trasladar) < cant_seleccion){
        if (seleccionar_pokemon(&(*arrecife).pokemon[i])) {
            int* nueva_pos_trasladar = NULL;
            nueva_pos_trasladar = realloc (*pos_trasladar, (size_t)((*cant_trasladar) + 1) * (sizeof(int))); 
            if (nueva_pos_trasladar != NULL) {
                *pos_trasladar = nueva_pos_trasladar;
                (*pos_trasladar)[(*cant_trasladar)] = i;
                (*cant_trasladar) ++;
            } else {
                estado = -1;
            }
        }
        i++;
    }
    return estado;
}

/*
*   Precondiciones: Debe recibir un puntero doble a un acuario valido, 
*   un puntero a un vector de posiciones a trasladar y su respectivo tope.
*   Ademas debe recibir un puntero a un arrecife valido de donde sacar pokemones.
*   Postcondiciones: Copiara en el acuario los pokemones que esten en el arrecife
*   en las posiciones indicadas en el vector de posiciones a trasladar.
*   Devolvera -1 en caso de error y 0 en caso contrario.
*/
int pasar_al_acuario(arrecife_t* arrecife, acuario_t** acuario, int* pos_trasladar, int cant_trasladar) {
    int i = 0;
    int estado = 0;
    while (i < cant_trasladar && estado == 0){
        pokemon_t* tmp = realloc( ((*(*acuario)).pokemon), (size_t)(((*(*acuario)).cantidad_pokemon) + 1) * sizeof(pokemon_t) );
        if (tmp == NULL) {
            estado = -1;
        } else {
            (*(*acuario)).pokemon = tmp;
            (*(*acuario)).pokemon[(*(*acuario)).cantidad_pokemon] = (*arrecife).pokemon[pos_trasladar[i]];
            ((*(*acuario)).cantidad_pokemon) ++;
        }
        i++;
    }
    return estado;
}

/*
*   Precondiciones: Debe recibir un puntero doble a un arrecife valido, 
*   un puntero a un vector de posiciones a eliminar y su respectivo tope.
*   Postcondiciones: Eliminara del vector de pokemones en el arrecife los pokemones 
*   en las posiciones indicadas en el vector de posiciones a eliminar.
*   Devolvera -1 en caso de error y 0 en caso contrario.
*/
int sacar_del_arrecife(arrecife_t** arrecife, int* pos_eliminar, int cant_eliminar) {
    for (int i = 0; i < (*(*arrecife)).cantidad_pokemon; i++) {
        int cantidad_a_mover = 0;
        int j = 0;
        bool inserto = false;
        while(j < cant_eliminar && !inserto){
            if (i > pos_eliminar[j]) {
                cantidad_a_mover = j + 1;
            }
            j++;
        }
        ((*(*arrecife)).pokemon)[i - cantidad_a_mover] = ((*(*arrecife)).pokemon)[i];
    }
    ((*(*arrecife)).cantidad_pokemon) -= cant_eliminar;
    pokemon_t* tmp = realloc( ((*(*arrecife)).pokemon), (size_t)((*(*arrecife)).cantidad_pokemon) * sizeof(pokemon_t) );
    if (tmp == NULL) {
        return -1;
    } else {
        (*(*arrecife)).pokemon = tmp;
        return 0;
    }
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {
    int* pos_trasladar = NULL;
    int cant_trasladar = 0;
    int estado = 0;
    estado = encontrar_pokemones_trasladar(arrecife, seleccionar_pokemon, cant_seleccion, &pos_trasladar, &cant_trasladar);
    if (cant_trasladar > 0 && cant_trasladar < cant_seleccion && estado == 0) {
        estado = -1;
    }
    if (estado == 0) {
        estado = pasar_al_acuario(arrecife, &acuario, pos_trasladar, cant_trasladar);
    }
    if (estado == 0) {
        estado = sacar_del_arrecife(&arrecife, pos_trasladar, cant_trasladar);
    }
    if (cant_trasladar > 0) {
        free (pos_trasladar);
    }
    return estado;
}

/****************************************************************************************** Censar arrecife ******************************************************************************************/

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
    
    printf("Datos : Especie - Color - Velocidad - Peso\n\n");
    for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) {
        mostrar_pokemon(&((*arrecife).pokemon[i]));
    }
    printf("En total hay %i pokemones\n", (*arrecife).cantidad_pokemon);
}

/*************************************************************************************** Guardar datos acuario ***************************************************************************************/

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {
    FILE* arch_acuario = fopen (nombre_archivo, "w");
    if (!arch_acuario) {
        return -1;
    }
    for(int i = 0; i < (*acuario).cantidad_pokemon; i++) {
        fprintf(arch_acuario, FORMATO_ACUARIO, ((*acuario).pokemon)[i].especie, ((*acuario).pokemon)[i].velocidad, ((*acuario).pokemon)[i].peso, ((*acuario).pokemon)[i].color);
    }
    fclose(arch_acuario);
    return 0;
}

/****************************************************************************************** Liberar acuario ******************************************************************************************/

void liberar_acuario(acuario_t* acuario) {
    if((*acuario).cantidad_pokemon != 0) {
        free ((*acuario).pokemon);
    }
    free (acuario);
}

/***************************************************************************************** Liberar arrecife ******************************************************************************************/

void liberar_arrecife(arrecife_t* arrecife){
    if((*arrecife).cantidad_pokemon != 0) {
        free ((*arrecife).pokemon);
    }
    free (arrecife);
}

/*****************************************************************************************************************************************************************************************************/