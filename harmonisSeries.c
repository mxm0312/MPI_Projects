#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int commsize, my_rank;
    float full_summ = 0;
    int n = atoi(argv[1]);
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    for (int i = 1; i < commsize; i++) {
        if (my_rank == 0) {
            float recieved_sum = 0;
            MPI_Recv(&recieved_sum, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            full_summ += recieved_sum;
        } else {
            int step = n/(commsize-1);
            int startIndex = (my_rank-1)*step;
            int endIndex = startIndex + step;
            if (startIndex == 0) {
                startIndex = 1;
            }
            float part_sum = 0;
            for (int i = startIndex; i < endIndex; i++) {
                part_sum += 1.0/((float)i);
            }
            MPI_Send(&part_sum, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (my_rank == 0) {
        for (int i = (commsize-1)*(n/(commsize-1)); i <= n; i++) {
            full_summ += 1.0/((float)i);
        }
        printf("N = %d\n", n);
        printf("Full summ is equals to %f\n", full_summ);
    }

    MPI_Finalize();
    return 0;
}
