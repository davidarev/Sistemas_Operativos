### EJERCICIO 1 -- 10 pts
Escribir un programa que genere 3 procesos en paralelo y que colaboran de forma conjunta para realizar la siguiente tarea: Justificar el proceso.
1. El primer proceso, utiliza el comando grep para encontrar en el (file_1), la palabra que se pasa por la línea de comandos.
2. EL segundo proceso, utiliza el comando grep para encontrar en el (file_2)), la palabra que se pasa por la línea de comandos.
3. El tercer proceso, utilizando el comando wc -l leerá por el pipe el número de coincidencias en los ficheros (file_1, file_2) y los escribirá en el (file_3).
La instrucción de ejecución será la siguiente: ./ejecutable palabra file_1 file_2 file_3
