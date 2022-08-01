/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II 
*
*   Program name: pd.c
*
*   Author: Carlos Bernalte García-Junco
*
*   Date created: 25-02-2021
*
*   Porpuse: Eliminación de los subdirectorios de los estudiantes.
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <definitions.h>

int main(int argc, char *argv[])
{
    char command[100];
    sprintf(command, "rm -rf %s", ESTUDIANTES);
    if (system(command) == -1)
    {
        fprintf(stderr, "[PROCESO D] No se pudo eliminar el directorio.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
