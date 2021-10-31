/*
* @file    : <nombre del archivo: por ejemplo, “tarea01.c”>
* @author  : <integrantes del grupo, en líneas diferentes>
* @date    : 04/10/2021
* @brief   : Código para tarea 01 en ELO 321, semestre 2021-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LENGTH 15

int Fib_Array [LENGTH];

int validacion(int value);

void* get_Fibonacci_series(void*);

int main(int argc, char **argv) {
    int *NumFibonacci = NULL;

    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    if (argc != 2) {
        printf("El programa funciona como ParteB.out <Numero>\n");
        return EXIT_FAILURE;
    }

    if ((atoi(argv[1]) >= LENGTH) | ((atoi(argv[1]) < 0)) ){
        printf("Ta malo\n");
        return EXIT_FAILURE;
    }

    int a = (atoi(argv[1]));//hace referencia al valor que se ingresa por comando
    int validator = validacion(a);
    NumFibonacci = &a;
    //Cumple la condicion
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, get_Fibonacci_series, argv[1]);
    /* wait for the thread to exit */
    pthread_join(tid,NULL);
    for (int i = 0; i <= (atoi(argv[1])); ++i) {
        printf("Los numeros almacenados corresponden a: %d \n",Fib_Array[i]);
    }

}

/* The thread will begin control in this function */
void* get_Fibonacci_series(void* param){

    int i;
    int numb = atoi(param);
    // initialize first and second terms
    int t1 = 0, t2 = 1;
    Fib_Array[0] = t1;
    // initialize the next term (3rd term)
    int nextTerm = t1 + t2;

    if(numb > 1){
        Fib_Array[1] = 1;
    }

    // print 3rd to nth terms
    for (i = 2; i <= numb; ++i) {
        t1 = t2;
        t2 = nextTerm;
        Fib_Array[i] = nextTerm;
        nextTerm = t1 + t2;
    }

    // Thread ID: #### calculó los ## números de la serie Fibonacci
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

