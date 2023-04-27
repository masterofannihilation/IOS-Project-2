/**
 *
 * @file main.c
 * @author Boris Hatala (xhatal02)
 * @date 30.04.2023
 * @brief IOS project 2 - synchronization
 *
 **/

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief check amount, value and format of command line arguments
 * @param int argc amount of command line arguments
 * @param char **argv array of command line arguments
 * @return
 */
void arg_check(int argc,char **argv) {
  //check amount of arguments
  if (argc != 6) {
    fprintf(stderr, "Invalid amount of command line arguments.Exiting.\n");
    exit(EXIT_FAILURE);
  }

  //chceck if arguments only consist of integer
  for (int i = 0; i < argc; i++) {
    char *argument = argv[i];
    int j = 0;
    while (argument[j] != '\0') {
      if (!isdigit(argv[j])) {
        fprintf(stderr, "Invalid format of command line argument. Arguments must be integers.Exiting.\n");
        exit(EXIT_FAILURE);
      }
      j++;
    }
  }

  //check if arguments have correct values
  if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) {
    fprintf(stderr, "Invalid amount of customers or workers.\n");
    exit(EXIT_FAILURE);
  }

  int wait_time = atoi(argv[3]);
  if (wait_time < 0 || wait_time > 10000) {
    fprintf(stderr, "Invalid amount of wait time.\n");
    exit(EXIT_FAILURE);
  }

  int break_time = atoi(argv[4]);
  if (break_time < 0 || break_time > 100) {
    fprintf(stderr, "Invalid amount of break time.\n");
    exit(EXIT_FAILURE);
  }

  int close_time = atoi(argv[5]);
  if (close_time < 0 || close_time > 10000) {
    fprintf(stderr, "Invalid amount of close time.\n");
    exit(EXIT_FAILURE);
  }

  return;
}

int main(int argc, char *argv[]) {

arg_check (argc, argv);

//number of customers
int customers = atoi(argv[1]); 
//number of workers
int workers = atoi(argv[2]);
//maximum time in miliseconds after which customers wait
int wait_time = atoi(argv[3]);
//maximum length of a break
int break_time = atoi(argv[4]);
//maximum time in milliseconds after which postal office is closed
int close_time = atoi(argv[5]);



}

//*** End of file main.c ***//
