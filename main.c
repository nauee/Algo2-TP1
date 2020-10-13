#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "evento_pesca.h"

#define RUTA_ESCRITURA_DEFECTO "acuario.txt"
#define RUTA_LECTURA_DEFECTO "arrecife.txt"
#define MAX_FUNCIONES 5

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Mostrara el pokemon por pantalla en formato de tabla.
*/
void mostrar_por_tablas (pokemon_t* pokemon) {
    printf("|  %-15s", (*pokemon).especie);
    printf("|  %-15s", (*pokemon).color);
    printf("|    %-3i    ", (*pokemon).velocidad);
    printf("|    %-3i   ", (*pokemon).peso);
    printf("|\n");
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Mostrara el pokemon por pantalla en formato de mini-tarjetas.
*/
void mostrar_por_mini_tarjetas (pokemon_t* pokemon) {
    printf("╔════════════════════════════╗\n");
    printf("║  %-15s    %-3i    ║\n", (*pokemon).especie, (*pokemon).velocidad);
    printf("║  %-15s    %-3i    ║\n", (*pokemon).color, (*pokemon).peso);
    printf("╚════════════════════════════╝\n");
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Mostrara el pokemon por pantalla en formato de tarjetas.
*/
void mostrar_por_tarjetas (pokemon_t* pokemon) {
    printf("╔════════════════════════════╗\n");
    printf("║    Especie: %-15s║\n", (*pokemon).especie);
    printf("║      Color: %-15s║\n", (*pokemon).color);
    printf("║     Velocidad: %-3i         ║\n", (*pokemon).velocidad);
    printf("║         Peso: %-3i          ║\n", (*pokemon).peso);
    printf("╚════════════════════════════╝\n");
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Mostrara el pokemon por pantalla en formato de lista.
*/
void mostrar_por_lista(pokemon_t* pokemon) {
    printf("  Especie: %-15s\n", (*pokemon).especie);
    printf("  Velocidad: %-3i            \n", (*pokemon).velocidad);
    printf("  Peso: %-3i            \n", (*pokemon).peso);
    printf("  Color: %-15s\n", (*pokemon).color);
    printf("═════════════════════════════\n");
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Mostrara el pokemon por pantalla en formato de csv.
*/
void mostrar_como_csv(pokemon_t* pokemon) {
    printf("%s;%i;%i;%s\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Devolvera true si el pokemon pesa mas de 80 y false en caso contrario.
*/
bool rompe_la_red (pokemon_t* pokemon){
    return ((*pokemon).peso > 80);
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Devolvera true si el pokemon pesa menos de 5 y false en caso contrario.
*/
bool es_peso_pluma (pokemon_t* pokemon){
    return ((*pokemon).peso < 5);
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Devolvera true si el pokemon es de color naranja y false en caso contrario.
*/
bool es_naranja (pokemon_t* pokemon){
    return ((strcmp((*pokemon).color, "naranja") == 0) || (strcmp((*pokemon).color, "Naranja") == 0));
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Devolvera true si la especie del pokemon empieza con A y false en caso contrario.
*/
bool empieza_con_a (pokemon_t* pokemon){
    return (((*pokemon).especie)[0] == 'A' || ((*pokemon).especie)[0] == 'a');
}

/*
*   Precondiciones: Debe recibir un pokemon con sus campos validos.
*   Postcondiciones: Devolvera true si el pokemon es un magikarp y false en caso contrario.
*/
bool es_magikarp (pokemon_t* pokemon){
    return ((strcmp((*pokemon).especie, "magikarp") == 0) || (strcmp((*pokemon).especie, "Magikarp") == 0));
}

/*
*   Precondiciones: Debe recibir argumentos del main con su tope, 
*   una ruta vacia y un argumento de donde copiar la ruta que sea valido (1 o 2).
*   Postcondiciones: Devolvera un puntero a la ruta con la ruta copiada en su interior.
*/
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

/*
*   Precondiciones: Debe recibir un vector de punteros a funciones bool que reciban pokemon_t*.
*   Postcondiciones: Asignara los distintos seleccionar_pokemon al vector de punteros a funciones bool.
*/
void asignar_seleccionar_pokemon(bool (*seleccionar_pokemon[MAX_FUNCIONES]) (pokemon_t*)) {
    seleccionar_pokemon[0] = rompe_la_red;
    seleccionar_pokemon[1] = es_peso_pluma;
    seleccionar_pokemon[2] = es_naranja;
    seleccionar_pokemon[3] = empieza_con_a;
    seleccionar_pokemon[4] = es_magikarp;
}

/*
*   Precondiciones: Debe recibir un vector de punteros a funciones void que reciban pokemon_t*.
*   Postcondiciones: Asignara los distintos mostrar_pokemon al vector de punteros a funciones void.
*/
void asignar_mostrar_pokemon(void (*mostrar_pokemon[MAX_FUNCIONES])(pokemon_t*)) {
    mostrar_pokemon[0] = mostrar_por_tablas;
    mostrar_pokemon[1] = mostrar_por_mini_tarjetas;
    mostrar_pokemon[2] = mostrar_por_tarjetas;
    mostrar_pokemon[3] = mostrar_por_lista;
    mostrar_pokemon[4] = mostrar_como_csv;
}

int main (int argc, char** argv) {

    srand((unsigned)time(NULL));
    char* ruta_lectura = NULL;
    char* ruta_escritura = NULL;
    ruta_lectura = determinar_ruta(argc, argv, ruta_lectura, 1);
    ruta_escritura = determinar_ruta(argc, argv, ruta_escritura, 2);
    bool (*seleccionar_pokemon[MAX_FUNCIONES]) (pokemon_t*);
    void (*mostrar_pokemon[MAX_FUNCIONES])(pokemon_t*);
    asignar_seleccionar_pokemon(seleccionar_pokemon);
    asignar_mostrar_pokemon(mostrar_pokemon);

    arrecife_t *arrecife = crear_arrecife(ruta_lectura);
    if (arrecife == NULL) {
        return -1;
    }
    acuario_t *acuario = crear_acuario();
    if (acuario == NULL) {
        return -1;
    }

    int cantidad_requerida = (rand() % 10) + 5;
    for(int i = 0; i < MAX_FUNCIONES; i++) {
        censar_arrecife(arrecife, mostrar_pokemon[i]);
        trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], cantidad_requerida);
        getchar();
        system("clear");
        cantidad_requerida = (rand() % 10) + 5;
    }

    censar_arrecife(arrecife, mostrar_pokemon[2]);
    guardar_datos_acuario(acuario, ruta_escritura);
    free(ruta_lectura);
    free(ruta_escritura);
    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
    return 0;
}