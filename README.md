Este proyecto ha sido creado como parte del currículo de 42 por carltruj

## "Descripción"

get_next_line es un proyecto de la escuela 42 cuyo objetivo es implementar una función en C capaz de leer un archivo línea por línea, devolviendo una línea completa en cada llamada, incluyendo el carácter de salto de línea (\n) cuando exista.

La función debe gestionar correctamente:

Lecturas parciales usando un tamaño de buffer configurable (BUFFER_SIZE)

Archivos grandes

Final de archivo (EOF)

Errores de lectura

Múltiples file descriptors simultáneamente (parte bonus)

Este proyecto pone especial énfasis en la gestión de memoria, el uso correcto de read, y el diseño de funciones robustas y reutilizables.

### ⚙️ Instrucciones

📁 Archivos principales
    - get_next_line.c
    - get_next_line_utils.c
    - get_next_line.h

📁 Archivos bonus
    - get_next_line_bonus.c
    - get_next_line_utils_bonus.c
    - get_next_line_bonus.h

### 🛠️ Compilación

Ejemplo de compilación básica:

    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

Para la versión bonus (múltiples file descriptors):

    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c

### ▶️ Uso

Ejemplo de uso en un programa:
------------------------------------------------------------------------------
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("archivo.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
-------------------------------------------------------------------------------

Cada llamada a get_next_line devuelve:

    - Una línea válida
    - NULL cuando se alcanza el EOF o ocurre un error

### 📖 Documentación y referencias

Manual de Unix:

    - man read
    - man fopen
    - man close

Documentación oficial de 42:

    - Enunciado del proyecto get_next_line

### 🤖 Uso de Inteligencia Artificial

Se ha utilizado IA (ChatGPT) como herramienta de apoyo para:

- Comprender mejor el comportamiento de read y el manejo de buffers
- Analizar errores de compilación y mensajes de herramientas de test (Francinette)
- Revisar la gestión de memoria y detectar posibles memory leaks
- Clarificar la implementación correcta del bonus (múltiples file descriptors)

La IA no ha generado automáticamente el proyecto, sino que ha servido como soporte de aprendizaje, depuración y validación conceptual, manteniendo siempre el control del diseño y la implementación final por parte del autor.