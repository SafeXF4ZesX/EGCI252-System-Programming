#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

static int set_semvalue(int sem_id);
static void del_semvalue(int sem_id);
static int semaphore_p(int sem_id);
static int semaphore_v(int sem_id);
static int sem_id1, sem_id2;

void f1() { printf("Function f1\n"); }

void f2() { printf("Function f2\n"); }

int main(int argc, char *argv[]) {
  pid_t pid;

  sem_id1 = semget((key_t)1234, 1, 0666 | IPC_CREAT);
  sem_id2 = semget((key_t)5678, 1, 0666 | IPC_CREAT);

  if (!set_semvalue(sem_id1) || !set_semvalue(sem_id2)) {
    fprintf(stderr, "Failed to initialize semaphores\n");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) { // Child process
    if (!semaphore_p(sem_id2))
      exit(EXIT_FAILURE);
    f2();
    sleep(1); // Simulate some work
    if (!semaphore_p(sem_id1))
      exit(EXIT_FAILURE);
    f1();
    printf("Child: Done!\n");
    semaphore_v(sem_id1);
    semaphore_v(sem_id2);
  } else { // Parent process
    if (!semaphore_p(sem_id1))
      exit(EXIT_FAILURE);
    f1();
    sleep(1); // Simulate some work
    if (!semaphore_p(sem_id2))
      exit(EXIT_FAILURE);
    f2();
    printf("Parent: Done!\n");
    semaphore_v(sem_id2);
    semaphore_v(sem_id1);
  }

  if (pid > 0) {
    sleep(10); // Wait for child process to finish
    del_semvalue(sem_id1);
    del_semvalue(sem_id2);
  }

  exit(EXIT_SUCCESS);
}

static int set_semvalue(int sem_id) {
  union semun sem_union;
  sem_union.val = 1;
  if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    return (0);
  return (1);
}

static void del_semvalue(int sem_id) {
  union semun sem_union;
  if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p(int sem_id) {
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1; /* P() */
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_p failed\n");
    return (0);
  }
  return (1);
}

static int semaphore_v(int sem_id) {
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1; /* V() */
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_v failed\n");
    return (0);
  }
  return (1);
}
