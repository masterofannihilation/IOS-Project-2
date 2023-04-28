/**
 * @file main.c
 * @author Boris Hatala (xhatal02)
 * @date 30.04.2023
 * @brief IOS project 2 - synchronization
 */

#include "main.h"

/**
 * @brief Main function of the program
 * @param int argc
 * @param char *argv[]
 * @return 
 */
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
  
  initilization();
  
  //creating processes for workers
  for(int i = 1; i <= 2; i++) {
    pid_t pid = fork();
    if (pid == 0) {

    }
    else if(pid < 0 ) {
      fprintf(stderr, "Fork failed.\n");
      clean();
      exit(EXIT_FAILURE);
    }
  }

  //creating processes for customers
  for(int i = 1 ; i <= 2; i++) {
    pid_t pid = fork();
    if(pid == 0) {

    }
    else if(pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      clean();
      exit(EXIT_SUCCESS);
    }
  }
  
  while(wait(NULL) > 0);
  clean();
  exit(EXIT_SUCCESS);
}

/**
 * @brief check amount, value and format of command line arguments
 * @param int argc amount of command line arguments
 * @param char **argv array of command line arguments
 * @return
 */
void arg_check(int argc,char *argv[]) {
  //check amount of arguments
  if (argc != 6) {
    fprintf(stderr, "Invalid amount of command line arguments.Exiting.\n");
    exit(EXIT_FAILURE);
  }
  
  //check if arguments only consist of integers
  //for (int i = 1; i <= argc; i++) {
  //  char *arg = argv[i];
  //  for (int j = 0; arg[j] != '\0'; j++) {
  //    if (!isdigit(arg[j])) {
  //      fprintf(stderr, "Invalid format of comamnd line arguments.\n");
  //      exit(EXIT_FAILURE);
  //    }
  //  }
  //}
  
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

/**
 * @brief open output file and intialize semaphores and shared memory
 * @param
 * @return 
 */
void initilization() {
  //open output file
  file = fopen("proj2.out", "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening output file.\n");
    exit(EXIT_FAILURE);
  }
  
  //initialize semaphores
  mutex = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  customer = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  worker = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  customer_done = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  worker_done = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  
  //check initilization
  if(mutex == MAP_FAILED || customer == MAP_FAILED || worker == MAP_FAILED || customer_done == MAP_FAILED || worker_done == MAP_FAILED ){
    fprintf(stderr, "Initilization of semaphores failed.\n");
    exit(EXIT_FAILURE);
  }
   
  sem_init(mutex, 1, 1);
  sem_init(customer, 1, 0);
  sem_init(worker, 1, 0);
  sem_init(customer_done, 1, 0);
  sem_init(worker_done, 1, 0);
  
  //check initilization
  if(sem_init(mutex, 1, 0) == -1 || sem_init(customer, 1, 0) == -1 || sem_init(worker, 1, 0) == -1 || 
     sem_init(customer_done, 1, 0) == -1 || sem_init(worker_done, 1, 0) == -1) {
    fprintf(stderr, "Initilization of semaphores failed.\n");
    exit(EXIT_FAILURE);
  }
  
  return;
}

/**
 * @brief 
 * @param
 * @return 
 */
void clean() {
  fclose(file);
  
  sem_destroy(mutex);
  sem_destroy(customer);
  sem_destroy(worker);
  sem_destroy(customer_done);
  sem_destroy(worker_done);
  
  exit(EXIT_SUCCESS);
}


//*** End of file main.c ***//
