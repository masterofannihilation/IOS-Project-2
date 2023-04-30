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
#include <stdarg.h>
#include <time.h>

//shared variables
sem_t *mutex = NULL;
sem_t *letter_done = NULL;
sem_t *package_done = NULL;
sem_t *money_done = NULL;
sem_t *letters = NULL;
sem_t *packages = NULL;
sem_t *money = NULL;
sem_t *output = NULL;

FILE *file;
int *line_number = NULL;
int *post_closed = NULL;
int *letter_queue = NULL;
int *packages_queue = NULL;
int *money_queue = NULL;
int *went_home = NULL;


//function declaration
void arg_check(int argc, char *argv[]);
void initialization();
void clean();
void worker_process(int id_w, int number_of_customers);
void customer_process(int id_c, int max_time);
void custom_print(const char * format, ...);
