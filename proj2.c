/**
 * @file main.c
 * @author Boris Hatala (xhatal02)
 * @date 30.04.2023
 * @brief IOS project 2 - synchronization
 */

#include "proj2.h"

/**
 * @brief function for custom print to output file
 * @param format 
 * @param ...
 * @return 
 */
void custom_print(const char * format, ...) {
  (*line_number)++;
  va_list args;
  va_start (args, format);
  fprintf(file, "%d:", *line_number);
  vfprintf(file, format, args);
  fflush(file);
  va_end(args);
  return;
}

/**
 * @brief process for worker
 * @param id_w id of every office worker
 * @param break_time maximum time a worker can take a break
 * @return 
 */
void worker_process(int id_w, int break_time) {

  //initialize random seed
  srand(time(NULL) * getpid());

  //initial print, worker is starting
  sem_wait(mutex);
  custom_print(" U %d: started\n",id_w);
  sem_post(mutex);

  //choosing service to serve;
  int service = 0;
  while (1) {
    service = rand() % 3 + 1;
    // service = 1;
    printf("U : %d, queue %d queue %d queue %d service %d\n", id_w, *letter_queue, *packages_queue, *money_queue, service);
    if (service == 1 && *letter_queue > 0) {
      //choosing queue, decrementing queue variable and posting semaphore so customer knows he is called
      sem_wait(mutex);
      (*letter_queue)--;
      sem_post(letters);
      sem_post(mutex);

      //giving customer notice he is working on it and is done
      sem_wait(mutex);
      custom_print(" U %d: serving a service of type %d\n", id_w, service);
      sem_post(mutex);

      //wait random time to finish service
      usleep(rand() % (11 * 1000));
      sem_wait(mutex);
      custom_print(" U %d: service finished\n", id_w);
      sem_post(mutex);
    }
    else if (service == 2 && *packages_queue > 0) {
      //choosing queue, decrementing queue variable and posting semaphore so customer knows he is called
       sem_wait(mutex);
      (*packages_queue)--;
      sem_post(packages);
      sem_post(mutex);

      //giving customer notice he is working on it and is done
      sem_wait(mutex);
      custom_print(" U %d: serving a service of type %d\n", id_w, service);
      sem_post(mutex);

      //wait random time to finish service
      usleep(rand() % (11 * 1000));
      sem_wait(mutex);
      custom_print(" U %d: service finished\n", id_w);
      sem_post(mutex);
    }
    else if (service == 3 && *money_queue > 0) {
      //choosing queue, decrementing queue variable and posting semaphore so customer knows he is called
       sem_wait(mutex);
      (*money_queue)--;
      sem_post(money);
      sem_post(mutex);

      //giving customer notice he is working on it and is done
      sem_wait(mutex);
      custom_print(" U %d: serving a service of type %d\n", id_w, service);
      sem_post(mutex);

      //wait random time to finish service
      usleep(rand() % (11 * 1000));
      sem_wait(mutex);
      custom_print(" U %d: service finished\n", id_w);
      sem_post(mutex);
    }
    else {
      sem_wait(mutex);
      if (*post_closed == 0) {
        sem_post(mutex);
        sem_wait(mutex);
        custom_print(" U %d: taking break\n", id_w);
        usleep(rand() % ((break_time + 1) * 1000));
        custom_print(" U %d: break finished\n", id_w);
        sem_post(mutex);        
      }
      else{        
        sem_post(mutex);
        sem_wait(mutex);
        custom_print(" U %d: going home\n", id_w);
        sem_post(mutex);
        break;
      }
      sem_post(mutex);
    }
  }  

  exit(EXIT_SUCCESS);
}

/**
 * @brief process for customer
 * @param id_c id of customer
 * @param max_time maximum time customer will wait before entering postal office
 * @return
 */
void customer_process(int id_c, int max_time) {

  //intialize random seed
  srand(time(NULL) * getpid());

  //initial print, customer is starting  
  sem_wait(mutex);
  custom_print(" Z %d: started\n", id_c);
  sem_post(mutex);

  // wait random time in <0,max_time> interval before entering the office
  usleep(rand() % ((max_time + 1) * 1000));

  //if office is closed, go home
  sem_wait(mutex);
  if((*post_closed) == 1) {
    sem_post(mutex);
    custom_print(" Z %d: going home\n", id_c);
    exit(EXIT_SUCCESS);
  }
  sem_post(mutex);


  //chose a service when entering the office
  int service = rand() % 3 + 1;
  // int service = 1;
  switch (service) {
  case 1:
    //entering office and incrementing queue variable, so that officer knows queue is not empty
    sem_wait(mutex);
    custom_print(" Z %d: entering office for a service %d\n", id_c, service);
    (*letter_queue)++;
    sem_post(mutex);

    //waiting for officer to post letters semaphore
    sem_wait(letters);

    //then he is called by him
    sem_wait(mutex);
    custom_print(" Z %d: called by office worker\n", id_c);
    sem_post(mutex);
    usleep(rand() % (11 * 1000));

    //copying signal he can go home
    sem_wait(mutex);
    custom_print(" Z %d: going home\n", id_c);
    sem_post(mutex);
  break;  

  case 2:
    //entering office and incrementing queue variable, so that officer knows queue is not empty
    sem_wait(mutex);
    custom_print(" Z %d: entering office for a service %d\n", id_c, service);
    (*packages_queue)++;
    sem_post(mutex);

    //waiting for officer to post letters semaphore
    sem_wait(packages);

    //then he is called by him
    sem_wait(mutex);
    custom_print(" Z %d: called by office worker\n", id_c);
    sem_post(mutex);
    usleep(rand() % (11 * 1000));

    //copying signal he can go home
    sem_wait(mutex);
    custom_print(" Z %d: going home\n", id_c);
    sem_post(mutex);
  break;

  case 3:
    //entering office and incrementing queue variable, so that officer knows queue is not empty
    sem_wait(mutex);
    custom_print(" Z %d: entering office for a service %d\n", id_c, service);
    (*money_queue)++;
    sem_post(mutex);

    //waiting for officer to post letters semaphore
    sem_wait(money);

    //then he is called by him
    sem_wait(mutex);
    custom_print(" Z %d: called by office worker\n", id_c);
    sem_post(mutex);
    usleep(rand() % (11 * 1000));

    //copying signal he can go home
    sem_wait(mutex);
    custom_print(" Z %d: going home\n", id_c);
    sem_post(mutex);
  break;
  }
  
  exit(EXIT_SUCCESS);
}

/**
 * @brief Main function of the program
 * @param argc 
 * @param argv
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
  
  initialization();
  
  //forking processes for workers
  for(int i = 1; i <= workers; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      worker_process(i, break_time);
    }
    else if(pid < 0 ) {
      fprintf(stderr, "Fork failed.\n");
      clean();
      exit(EXIT_FAILURE);
    }
  }

  //forking processes for customers
  for(int i = 1 ; i <= customers; i++) {
    pid_t pid = fork();
    if(pid == 0) {
      customer_process(i, wait_time);
    }
    else if(pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      clean();
      exit(EXIT_SUCCESS);
    }
  }

  //opening postal office for random time
  int close = rand() % (((close_time - (close_time / 2) + 1) + (close_time / 2)) * 1000);
  usleep(close);
  sem_wait(mutex);
  *post_closed = 1;
  custom_print(" closing\n");
  sem_post(mutex);
  
  //waiting for all the child processes to end
  while(wait(NULL) > 0);
  clean();
  return EXIT_SUCCESS;
}

/**
 * @brief check amount, value and format of command line arguments
 * @param argc 
 * @param argv
 * @return
 */
void arg_check(int argc,char *argv[]) {
  //check amount of arguments
  if (argc != 6) {
    fprintf(stderr, "Invalid amount of command line arguments.Exiting.\n");
    exit(EXIT_FAILURE);
  }

  //check format of each comamnd line arguments, must be integer
  for(int i = 1; i < argc; i++) {
    for(int j = 0; argv[i][j] != '\0'; j++) {
      if(!isdigit(argv[i][j])){
        fprintf(stderr, "Invalid format of command line argument number %d. Only integers!\n", i);
        exit(EXIT_FAILURE);
      }
    }
  }
  
  //check if arguments have correct values
  if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
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
void initialization() {
  //open output file
  file = fopen("proj2.out", "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening output file.\n");
    exit(EXIT_FAILURE);
  }

  //intialize shared variables
  line_number = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  post_closed = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  letter_queue = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  packages_queue = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  money_queue = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

  
  //initialize semaphores
  mutex = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  letters = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  packages = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  money = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  
  //check initilization
  if(mutex == MAP_FAILED ||  
    letters == MAP_FAILED || 
    packages == MAP_FAILED || 
    money == MAP_FAILED || 
    output == MAP_FAILED){
    fprintf(stderr, "Initilization of semaphores failed.\n");
    exit(EXIT_FAILURE);
  }
     
  //check initilization
  if(sem_init(mutex, 1, 1) == -1 || 
    sem_init(letters, 1, 0) == -1 || 
    sem_init(packages, 1, 0) == -1 || 
    sem_init(money, 1, 0) == -1 ){
    fprintf(stderr, "Initilization of semaphores failed.\n");
    exit(EXIT_FAILURE);
  }
  
  return;
}

/**
 * @brief destroys all the semaphores and unmaps shared variables
 * @param
 * @return 
 */
void clean() {
  fclose(file);

  //unmap all shared variables
  munmap((line_number), sizeof(line_number));
  munmap((post_closed), sizeof(post_closed));
  munmap((letter_queue), sizeof(letter_queue));
  munmap((packages_queue), sizeof(packages_queue));
  munmap((money_queue), sizeof(money_queue));
  
  //destroy semaphores
  sem_destroy(mutex);
  sem_destroy(letters);
  sem_destroy(packages);
  sem_destroy(money);

  return;
}
//*** End of file main.c ***//