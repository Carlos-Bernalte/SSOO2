# Practica3-SSOO2


Carlos Bernalte García-Junco <carlos.bernalte@alu.uclm.es>

Paulino De La Fuente Lizcano <paulino.lafuente@alu.uclm.es>

## Compilación y ejecución del código

Para la compilación automática de todos los programas .cpp ubicado en la carpeta src llamaremos al regla all del archivo Makefile. Si se quisiera cambiar el número de clientes, hilos por cliente y número de clientes a la vez activos para realizar busquedas, se tendría que cambiar las variables estáticas (NCLIENTES, NTHREADS y BUFFER respectivamente) que se encuentran en definitions.h
```sh
$ make all
```
Para probar el código con ejemplos de prueba se podran llamar a test:
```sh
$ make test
```
Si queremos limpiar el entorno de trabajo podremos llamar a la regla clean:
```sh
$ make clean
```