/**
 * @file main.h
 * @author Boris Hatala (xhatal02)
 * @date 30.04.2023
 * @brief Header file for main.c
 */

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>


//shared variables
FILE *file; 
sem_t *mutex = NULL;
sem_t *customer = NULL;
sem_t *worker = NULL;
sem_t *customer_done = NULL;
sem_t *worker_done = NULL;


//function declaration
void arg_check(int argc, char **argv);
void initializaton();
void clean();
