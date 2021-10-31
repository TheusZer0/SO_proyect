/*
* @file    : Parte_A.c
* @author  : Robert Parra
* @date    : 31/10/2021
* @brief   : Código de la parte A para tarea 01 en ELO 321, semestre 2021-2
*/

/**
 * Links used:
 *
 * https://man7.org/linux/man-pages/man2/time.2.html
 * https://www.geeksforgeeks.org/pipe-system-call/
 * https://man7.org/linux/man-pages/man2/syscalls.2.html
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/time.html
 * https://www.qnx.com/developers/docs/6.4.0/neutrino/lib_ref/t/time.html
 * https://bencane.com/2012/07/02/when-zombies-invade-linux-what-are-zombie-processes-and-what-to-do-about-them/
 * https://askubuntu.com/questions/111422/how-to-find-zombie-process
 * https://www.poftut.com/what-is-sleep-function-and-how-to-use-it-in-c-program/
 * https://www.cs.swarthmore.edu/~newhall/unixhelp/C_commandlineargs.php
 * https://www.geeksforgeeks.org/converting-strings-numbers-cc/
 * https://www.google.com/search?q=fibonacci+series&client=ubuntu&hs=DQ4&channel=fs&sxsrf=AOaemvIizB86WjZ0_U-1MUNhC1HyUYwk_g:1634455936886&source=lnms&tbm=isch&sa=X&ved=2ahUKEwj0iZPs9tDzAhVzE7kGHdapAdwQ_AUoAXoECAEQAw&biw=913&bih=939&dpr=1#imgrc=ID54bT3fJ_VDeM&imgdii=66JmiY1gJd8klM
 * https://tldp.org/LDP/lpg/node11.html
 * https://www.geeksforgeeks.org/pipe-system-call/
 */

/*
 * Aclaracion, el indice 0 de la sucesion de fibonacci correspondera al 0 mismo, siendo entonces, el numero 1 el indice 1, el indice 2 vuelve a ser el 1
 * y para el tercer indice correspondera al 2, de esa manera se cumple con lo pedido debido a que en el pdf se muestra al 55 como el indice 10.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define READ_END        0
#define WRITE_END       1

/**
 * Realiza una validacion del dato, es decir, si es o no un positivo.
 * en caso de que no, retorna un exit failure.
 * @return
 */
int validacion(int value);

/**
 * Funcion que realiza el calculo
 * de la sucession de fibonacci retornando un int correspondiente al
 * numero de fibonacci
 * @return
 */
int Fibonacci_serie(unsigned int value);

/**
 * recibe el número positivo como argumento y retorna el índice de este número en la serie de
 * Fibonacci, o retorna -1 en caso de que el número no esté en la serie,
 * si la función recibe como argumento el número 55, retornará el número 10
 * @return int
 */
int search_Fibonacci_series(unsigned int value);

/**
 * Genera un proceso hijo, a fin de ejecutar una llamada al
 * sistema e imprimir por pantalla la hora y fecha de ejecución del programa.
 */
void child_time_proccess();

/**
 * La funcion realiza el proceso de las funciones correspondientes a fibonacci, ya que esta manera
 * el proceso hijo creado en esta funcion debe enviar al proceso padre a través del ordinary pipe un mensaje/string
 * informando el resultado del procesamiento de estas funciones de fibonacci, y luego terminar su ejecución.
 * @return int
 */
int ordinary_pipe(int value);

int main(int argc, char **argv) {
    if (argc==2){
        unsigned int a = atoi(argv[1]);//hace referencia al valor que se ingresa por comando

        validacion(a);
        child_time_proccess();
        ordinary_pipe(a);

        //ps -elf
        //ps aux | grep 'Z'

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

int Fibonacci_serie(unsigned int value){

    int valid = 1;
    int indice = 0;

    int f1 = 0;
    int f2 = 1;

    int nextF = 0;

    while (nextF <= value) {
        if (nextF == value){
            valid = 0;
            return indice;
        }
        indice++;
        f1 = f2;
        f2 = nextF;
        nextF = f1 + f2;
    }
    return -1;
}

int search_Fibonacci_series(unsigned int value){
    int validator;
    validator = Fibonacci_serie(value);

    if(validator==-1){
        return -1;
    } else{
        return validator;
    }
}

void child_time_proccess(){
    if(fork() == 0)
    {
        // Este corresponde al proceso hijo
        time_t result;
        result = time(NULL);
        printf("%s\n",asctime(localtime(&result)));
        exit(0);
    }else{
        //Este corresponde al proceso padre
    }
    wait(NULL);
}

int ordinary_pipe(int value){

    /* creacion del ordinary_pipe */

    char read_msg[BUFFER_SIZE];
    char write_msg[BUFFER_SIZE];


    pid_t pid;
    int fd[2];
    /* creacion del pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    if(fork() == 0)
    {
        // Este corresponde al proceso hijo

        int respond = search_Fibonacci_series(value);

        sprintf(write_msg, "%d",respond);

        close(fd[READ_END]);

        /* escribe en el pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

        /* cierra la escritura del pipe */
        close(fd[WRITE_END]);

        exit(0);
    }else{
        //this is the parent process

        /* close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* lee desde el pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);

        if (strcmp (read_msg, "-1") == 0){
            printf("El numero no es parte de la succesion.");
        }else{
            printf("El mensaje fue recibido correctamente,\nel numero es parte de la succesion de fibonacci y su indice es: %s\n",read_msg);
        }
        /* cierra la escritura y el pipe mismo*/
        close(fd[READ_END]);

    }

    /*
     * Sleep pedido por el profesor para que el proceso hijo pase a ser un “zombie”.
     */
    sleep(50);

    wait(NULL);
}