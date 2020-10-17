**************************************************************************************** Nahuel Castro 106551 *****************************************************************************************

Aclaracion: Se modifico el nombre del makefile por errores en las pruebas, modificar manualmente a "makefile"

Funcionamiento:
    
    El trabajo se basa en una biblioteca que consta de 7 funciones, las cuales son:
        crear_arrecife (crea un arrecife con todos los pokemones contenidos en un archivo .txt)
        crear_acuario (crea un acuario vacio listo para recibir pokemones)
        trasladar_pokemon (traslada del arrecife al acuario a los pokemones que cumplan las condiciones pedidas)
        censar_arrecife (muestra los pokemones contenidos en el arrecife)
        guardar_datos_acuario (va a guardar en un archivo los pokemones contenidos en el acuario)
        liberar_arrecife (libera el arrecife luego de ser utilizado)
        liberar_acuario (libera el acuario luego de ser utilizado)
    
    A su vez se incluye un archivo main.c con un ejemplo del funcionamiento de la biblioteca en donde se 
    lee un archivo de arrecife y se trasladan al acuario pokemones segun 5 condiciones.
    Cada vez que se trasladan pokemones se censa el arrecife para mostrar los pokemones restantes.
    Luego de trasladar todos los pokemones pedidos se guarda en un archivo .txt los datos del acuario
    y se liberan tanto el arrecife como el acuario.

Linea de compilacion:

    Puede compilarse ingresando make o ingresando la linea original:
    gcc evento_pesca.c main.c -g -std=c99 -Wall -Werror -Wconversion -o evento_pesca

Linea de ejecución:

    Para ejecutarse se debe ingresar ./evento_pesca <ruta_lectura> <ruta_escritura>
    Tanto <ruta_lectura> como <ruta_escritura> son opcionales, en caso de no ingresarse alguna
    automaticamente se utilizara la ruta por defecto
    (arrecife.txt para lectura y acuario.txt para ruta_escritura).
    Se debe respetar el orden en el que se ingresan las rutas.
    Si se ingresa solo una ruta, se tomara como si fuera la ruta de lectura.
    En caso de no querer ejecutar con parametros, tambien puede ejecutar
    el programa ingresando "make ejecutar" que compilara y ejecutara el programa.

Explicaciones:

    Punteros:
        Un puntero es una variable que contienen la direccion de memoria de otra variable.
    Aritmetica de punteros:
        Operador de direccion (&): Nos da la direccion de memoria de una variable.
        Operador de indireccion (*): Nos da el valor contenido en una direccion dada.
        Operadores de incremento (++) y decremento (--): Nos permite movernos entre direcciones de memoria,
        aumentandola en 1 o decrementandola en 1 respectivamente.
    Punteros a funciones:
        Al igual que los punteros normales contienen una direccion de memoria, pero en este
        caso esta direccion se refiere a una funcion. Esto nos permite muchas cosas
        como por ejemplo pasar funciones como parametro. Tienen la siguiente sintaxis:
        tipo (*nombre_funcion) (parametro1, ..., parametroN)

*******************************************************************************************************************************************************************************************************