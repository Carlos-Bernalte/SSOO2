# Practica1-SSOO2


Carlos Bernalte García-Junco <carlos.bernalte@alu.uclm.es>



## Compilación y ejecución del código:

Para la compilación automática de todos los programas .c ubicado en la carpeta src llamaremos al regla all del archivo Makefile:
```sh
$ make all
```
Para llevar acabo la ejecución del programa utilizaremos la regla run:
```sh
$ make run
```
Si queremos limpiar el entorno de trabajo de los archivos compilados generados y ficheros/directorios generados por la ejecución del programa podremos llamar a la regla clean:
```sh
$ make clean
```
Para matar a los procesos demonio que crean copias de seguridad cada minuto:
```sh
$ make killdemonio
```
