/*
* @file    : Parte_B.c
* @author  : Robert Parra
* @date    : 31/10/2021
* @brief   : Código de la parte B para tarea 01 en ELO 321, semestre 2021-2
*/


/*
 * Links usados:
 *
 * https://www.tutorialspoint.com/pthread-self-in-c
 * https://stackoverflow.com/questions/52657858/implementing-pthread-self-in-c
 * https://tutorialspoint.dev/language/c/pthread_self-c-example
 * https://www.geeksforgeeks.org/pthread_self-c-example/
 * https://www.geeksforgeeks.org/multithreading-c-2/
 * https://www.geeksforgeeks.org/thread-functions-in-c-c/
 * http://profesores.elo.utfsm.cl/~agv/elo330/2s08/lectures/POSIX_Threads.html
 * https://man7.org/linux/man-pages/man7/pthreads.7.html
 * https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html
 * http://www.cs.fsu.edu/~baker/realtime/restricted/notes/pthreads.html
 * https://www.youtube.com/watch?v=ynCc-v0K-do
 * Ejemplos de clase
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LENGTH 15

int Fib_Array [LENGTH];

/**
 * Realiza una validacion del dato, es decir, si es o no un positivo.
 * en caso de que no, retorna un exit failure.
 * @return int
 */
int validacion(int value);

/**
 * genera 1 hilo (thread) cuyo propósito será calcular la cantidad indicada de números
 * de la serie de Fibonacci y almacenarlos en un arreglo global int Fib_Array [LENGTH], cuyo
 * largo indica la máxima cantidad de números que se pueden almacenar.
 * @return int
 */
void* get_Fibonacci_series(void*);

int main(int argc, char **argv) {
    int *NumFibonacci = NULL;

    pthread_t tid; /* identificador del thread */
    pthread_attr_t attr; /* setea los atributos del thread */

    /*
     * Condicionales para el mal uso del programa
     */
    if (argc != 2) {
        printf("El programa funciona como ParteB.out <Numero>\n");
        return EXIT_FAILURE;
    }
    if ((atoi(argv[1]) >= LENGTH) | ((atoi(argv[1]) < 0)) ){
        printf("Ingreso un numero fuera de alcance para el programa, recordar que el maximo es 15\n");
        return EXIT_FAILURE;
    }

    /*
     * funcionamiento del programa como tal, siendo este el uso del thread
     */
    int a = (atoi(argv[1]));//hace referencia al valor que se ingresa por comando
    int validator = validacion(a);

    /* le asignamos atributos default al thread */
    pthread_attr_init(&attr);
    /* se crea el thread y se le asigna la funcion controladora del mismo */
    pthread_create(&tid, &attr, get_Fibonacci_series, argv[1]);
    /* espera a la salida del thread */
    pthread_join(tid,NULL);
    for (int i = 0; i <= (atoi(argv[1])); ++i) {
        printf("Los numeros almacenados corresponden a: %d \n",Fib_Array[i]);
    }
}

/* El thread sera controlado por esta funcion */
void* get_Fibonacci_series(void* param){

    int i;
    int numb = atoi(param);
    // se inicializa el primer termino y el segundo
    int t1 = 0, t2 = 1;
    Fib_Array[0] = t1;
    // se realiza la inicializacion del 3r termino
    int nextTerm = t1 + t2;
    // si el numb ingresado es mayor a 1 entonces quiere decir que el indice 1 existe
    if(numb >= 1){
        Fib_Array[1] = 1;
    }
    // realiza el funcionamiento de fibonacci
    for (i = 2; i <= numb; ++i) {
        t1 = t2;
        t2 = nextTerm;
        Fib_Array[i] = nextTerm;
        nextTerm = t1 + t2;
    }
    // mensaje de exito
    printf("Thread ID = %lu calculó los %d números de la serie Fibonacci\n", pthread_self(),numb);
    pthread_exit(0);
}

int validacion(int value){
    if (value>=0){
        return 0;
    }else{
        exit(-1);
    }
}

