# Descripción del programa 
Este repositorio corresponde a una versión mejorada de una solución propuesta para un curso de MPI realizado por PRACE para la ecuación de calor bidimensional, dicha solución esta realizada en MPI con C. A continuación se dara una descripción de cada uno de los archivos que hace parte de esta solución: 
- **core.c**: contiene funciones esenciales para resolver la ecuación de calor en un entorno de procesamiento paralelo utilizando MPI. Las funciones se encargan de intercambiar valores en los bordes del dominio y actualizar los valores de temperatura en el interior y en los bordes del dominio en cada paso de tiempo.
- **heat.h**: proporciona las definiciones y prototipos necesarios para la implementación del programa de simulación de la ecuación de calor. Define las estructuras de datos y funciones que se utilizan en el programa principal para llevar a cabo la simulación de difusión de calor en un dominio de dos dimensiones.
- **io.c**: contiene funciones para la entrada y salida de datos utilizadas en el programa de simulación de la ecuación de calor. Estas funciones permiten cargar datos iniciales desde archivos, escribir imágenes de la distribución de temperatura y crear puntos de reinicio para continuar la simulación desde un estado anterior.
- **main.c (código principal)**: es el archivo principal del programa de resolución de la ecuación de calor en 2D. Realiza la simulación de la ecuación de calor en 2D y realiza la salida de datos, incluyendo imágenes y puntos de reinicio, en intervalos específicos.
- **pngwriter.c**: permite la generación de imágenes PNG a partir de matrices de datos y es útil para visualizar resultados numéricos en aplicaciones científicas y de procesamiento de imágenes. La función cmap se encarga de asignar colores a los valores de los datos, y la paleta de colores se define en la matriz heat_colormap.
- **pngwriter.h**: es un archivo de encabezado que se utiliza para declarar la función save_png, la cual permite para guardar datos en formato PNG.
- **setup.c**: proporciona una serie de funciones para inicializar, configurar y finalizar la simulación de la ecuación del calor en un entorno de procesamiento paralelo. Además, gestiona la lectura de archivos de entrada y permite la reanudación de simulaciones a partir de un punto de control anterior. Este código es una parte esencial de la preparación de la simulación antes de ejecutarla en un entorno paralelo.
- **utilities.c**: proporciona una serie de funciones de utilidad para gestionar la asignación de memoria, copia y asignación de campos de temperatura. Estas funciones son esenciales para la manipulación eficiente de datos y la gestión de memoria en el programa general.
- **Makefile**: se utiliza para compilar y vincular el programa "heat_mpi" a partir de varios archivos fuente, incluidos "core.c", "setup.c", "utilities.c", "io.c" y "main.c", que forman parte de la solución para la ecuación de calor. El programa se compila con optimización y se vincula con las bibliotecas necesarias, como "libpng" y "libm".
- **bottle.dat**: ilustra lo que le sucede a una botella de refresco fría que se somete a temperaturas externas. 

# Modificaciones realizadas
#### En el código (main.c)

Se crearon las variables rank y size para guardar a parallelization.rank y parallelization.size respectivamente. 

![img1](./Recursos/modificacionMain1.jpg)

Se crearon las variables local_nsteps y extra_nsteps para determinar cuántos pasos de ejecución o iteraciones de un bucle se asignarán a cada uno de los procesos o hilos.

![img2](./Recursos/modificacionMain2.jpg)

El bucle de tiempo se divide entre los procesos MPI de manera equitativa, y se utiliza la variable local_nsteps para controlar la cantidad de pasos de tiempo que cada proceso realice. Los pasos de tiempo adicionales se distribuyen a los procesos según sea necesario. Esto asegura que todos los procesos estén ocupados y trabajen de manera eficiente.

![img3](./Recursos/modificacionMain3.jpg)

Se utiliza la variable rank en vez de parallelization.rank.

![img4](./Recursos/modificacionMain4.jpg)

#### En la ejecución y en la compilación del programa
# Instrucciones de compilación y ejecución 
#### Modo interactivo
Para compilar y ejecutar el código en el clúster de GUANE-1, siga las siguientes instrucciones:
1. Descargue el archivo en formato zip.
   
2. Entre en GUANE-1 con sus respectivas credenciales y ejecute los siguientes comandos:
  ```
  ssh guane
  ```
  ```
  srun -n 4 -w guane10 --pty /bin/bash
  ```
5. Cargue el archivo descarga en su espacio.
6. Descomprima el archivo utilizando el siguiente comando:
7. Ingrese en la carpeta donde se encuentra el programa, usando los siguientes comandos:
8. Utilice el archivo make para hacer la compilación del programa de la siguiente forma:
9. Utilice los siguientes comandos para relizar la ejecución del programa:
   - Ejecutando con los valores predeterminados: mpirun -np 4 ./heat_mpi
   - Campo inicial desde un archivo: mpirun -np 4 ./heat_mpi bottle.dat
   - Campo inicial desde un archivo, con un número dado de pasos de tiempo: mpirun -np 4 ./heat_mpi bottle.dat 1000
   - Patrón predeterminado con dimensiones y pasos de tiempo especificados: mpirun -np 4 ./heat_mpi 800 800 1000
 En  número al lado de -np es el número de procesos, para este ejemplo se utilizaron 4, pero se puede cambiar. Al igual que se pueden cambiar los valores de las dimensiones y el número de pasos. 

Modo pasivo
# Resultados obtenidos 
Código original 
Código modificado 
Código modificado con mejoras en la ejecución y compilación 
# Conclusiones

