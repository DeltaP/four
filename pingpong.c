/*
 * Gregory Petropoulos
 *
 * This is my ping pong program for assignment 4
 *
 * To compile:  mpicc -g -Wall -std=c99 -o pingpong pingpong.c
 * To run:  mpiexec -n 8 ./butterfly [-verbose] <lth>
 *          <> -> mandatory
 *          [] -> optional
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define N 1000000


// -----------------------------------------------------------------
// the main program
int main(int argc, char *argv[]) {
  double message[N], start, finish, elapsed;
  int comm_sz, my_rank, i, len, n, stat;
  int send = 0;
  int recv = 17;
  char name[1000];

  MPI_Init(&argc, &argv);                               /* start up MPI                         */
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);              /* get the number of processes          */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);              /* get my rank among all the processes  */

  n = atoi(argv[1]);
  stat = atoi(argv[2]);

  for (i = 0; i < n; i++) {                             /* populates the message                */
    message[n]=0.00123*i;
  }

  if ((my_rank == send) || (my_rank == recv)) {
    MPI_Get_processor_name(name, &len);
    printf("I am %d of %d on %s\n", my_rank, comm_sz, name);
    fflush(stdout); 
  }

  for (i = 0; i < 100; i++) {                           /* warmups                              */
    if (my_rank == send) {
      MPI_Send(message, n, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD);
      MPI_Recv(message, n, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (my_rank == recv) {
      MPI_Recv(message, n, MPI_DOUBLE, send, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(message, n, MPI_DOUBLE, send, 0, MPI_COMM_WORLD);
    }
  }

  if (my_rank == send)
    start = MPI_Wtime();

  for (i = 0; i < stat; i++) {                           /* warmups                              */
    if (my_rank == send) {
      MPI_Send(&message, n, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD);
      MPI_Recv(&message, n, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (my_rank == recv) {
      MPI_Recv(&message, n, MPI_DOUBLE, send, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(&message, n, MPI_DOUBLE, send, 0, MPI_COMM_WORLD);
    }
  }
  if (my_rank == send) {
    finish = MPI_Wtime();
    elapsed = (finish-start) / (2 * stat);
    printf("TIME: %e\n", elapsed);
  }
  MPI_Finalize();
  return 0;
}
