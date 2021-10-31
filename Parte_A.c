/*
* @file    : <nombre del archivo: por ejemplo, “tarea01.c”>
* @author  : <integrantes del grupo, en líneas diferentes>
* @date    : 04/10/2021
* @brief   : Código para tarea 01 en ELO 321, semestre 2021-2
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
 * Recordar reclamar que la sucession de fibonacci comienza en 0 siendo este el primer indice
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
 * Sucession de fibonacci como tal
 * @return
 */
int Fibonacci_serie(unsigned int value);

/**
 * Sucession de fibonacci como tal
 * @return
 */
int search_Fibonacci_series(unsigned int value);

/**
 * Sucession de fibonacci como tal
 * @return
 */
void child_time_proccess();

/**
 * Sucession de fibonacci como tal
 * @return
 */
int ordinary_pipe();

int main(int argc, char **argv) {
    if (argc==2){
        //char *ptr;
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
        //indice++;
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
        // this is the child process
        //printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
        time_t result;
        result = time(NULL);
        printf("%s\n",asctime(localtime(&result)));
        exit(0);
    }else{
        //this is the parent process
    }
    sleep(50);
    wait(NULL);
}

int ordinary_pipe(int value){

    /*ordinary_pipe creation*/

    char read_msg[BUFFER_SIZE];
    char write_msg[BUFFER_SIZE];


    pid_t pid;
    int fd[2];
    /* create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    if(fork() == 0)
    {
        // this is the child process
        //printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());

        int respond = search_Fibonacci_series(value);

        sprintf(write_msg, "%d",respond);

        /* close the unused end of the pipe */
        close(fd[READ_END]);

        /* write to the pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

        /* close the write end of the pipe */
        close(fd[WRITE_END]);

        exit(0);
    }else{
        //this is the parent process

        /* close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);

        if (strcmp (read_msg, "-1") == 0){
            printf("El numero no es parte de la succesion.");
        }else{
            printf("El mensaje fue recibido correctamente,\nel numero es parte de la succesion de fibonacci y su indice es: %s\n",read_msg);
        }
        /* close the write end of the pipe */
        close(fd[READ_END]);

    }
    wait(NULL);
}