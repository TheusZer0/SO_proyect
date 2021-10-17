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

    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    if (argc==2) {
        unsigned int a = atoi(argv[1]);//hace referencia al valor que se ingresa por comando
        int validator = validacion(a);

        if(a<=LENGTH){
            //Cumple la condicion

            /* get the default attributes */
            pthread_attr_init(&attr);
            /* create the thread */
            pthread_create(&tid, &attr, get_Fibonacci_series((void *) a), argv[1]);
            /* wait for the thread to exit */
            pthread_join(tid,NULL);
            for (int i = 0; i <= LENGTH; ++i) {
                printf("The number is: %d \n",Fib_Array[i]);
            }
        }else{
            exit(-1);
        }

    } else{ //caso contrario, si no cumple retorna 1
        printf("El programa funciona como ParteA.out <Numero>\n");
        return EXIT_FAILURE;
    }

}

/* The thread will begin control in this function */
void* get_Fibonacci_series(void* numb){
    int i, n;

    // initialize first and second terms
    int t1 = 0, t2 = 1;

    // initialize the next term (3rd term)
    int nextTerm = t1 + t2;



    // print the first two terms t1 and t2
    printf("Fibonacci Series: %d, %d, ", t1, t2);

    // print 3rd to nth terms
    for (i = 3; i <= n; ++i) {
        printf("%d, ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }

}

int validacion(int value){
    if (value>=0){
        return 0;
    }else{
        exit(-1);
    }
}

