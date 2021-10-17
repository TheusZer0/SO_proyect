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

#define LENGTH 20

int validacion(int value);

int main(int argc, char **argv) {
    if (argc==2) {
        unsigned int a = atoi(argv[1]);//hace referencia al valor que se ingresa por comando
        int validator = validacion(a);

        if(a<=LENGTH){
            //Cumple la condicion

        }else{
            exit(-1);
        }

    } else{ //caso contrario, si no cumple retorna 1
        printf("El programa funciona como ParteA.out <Numero>\n");
        return EXIT_FAILURE;
    }
}

int validacion(int value){
    if (value>=0){
        return 0;
    }else{
        exit(-1);
    }
}

