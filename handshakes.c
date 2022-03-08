#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    int commsize, my_rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    int recieved_message;
    int message = rank;

    if (my_rank != commsize - 1) {
        MPI_Send(&message, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recieved_message, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Мой ранк: %d. Получил сообщение: %d\n", my_rank, recieved_message);
    } else if (my_rank == 0) {
        MPI_Send(&message, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recieved_message, 1, MPI_INT, commsize - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Мой ранк: %d. Получил сообщение: %d\n", my_rank, recieved_message);
    } else {
        MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&recieved_message, 1, MPI_INT, commsize - 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Мой ранк: %d. Получил сообщение: %d\n", my_rank, recieved_message);
    }

    MPI_Finalize();
    return 0;
}
