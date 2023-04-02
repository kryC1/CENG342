/*
 * Author: Koray ÇELİK
 * Date: 23-04-03, 12:09
 * Description: This is the HW3 of CENG342
 *
 * Copyright (c) 2023 Koray ÇELİK
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <hellomake.h>

void myMatrixVectorMul(int matrixSize, int unusedSize, int my_rank, int num_procs, char * filename) {
    double start_time1, end_time1, start_time2, end_time2, time3;
    FILE *fptr;

    long int myID = 18050111056;
    srand(myID);

    // create 2d array (square matrix) using malloc
    double **myArray = malloc(matrixSize * sizeof(double *));
    for (int i = 0; i < matrixSize; i++) {
        myArray[i] = malloc(matrixSize * sizeof(double));
    }

    // fill the matrix with random numbers, seed:18050111056
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            myArray[i][j] = ((double)rand() / RAND_MAX) * 100.0;
        }
    }

    // create and fill the vector with random numbers
    double *myVector = malloc(matrixSize * sizeof(double));
    for (int i = 0; i < matrixSize; i++) {
        myVector[i] = ((double)rand() / RAND_MAX) * 100.0;
    }

    // create result array and perform matrix-vector multiplication
    double *myResult = calloc(matrixSize, sizeof(double));

    start_time1 = MPI_Wtime();

    // divide the work among the processes
    int chunk_size = matrixSize / num_procs;
    int start = my_rank * chunk_size;
    int end = (my_rank == num_procs - 1) ? matrixSize : start + chunk_size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < matrixSize; j++) {
            myResult[i] += myArray[i][j] * myVector[j];
        }
    }

    end_time1 = MPI_Wtime();

    // collect the results from all processes
    if (my_rank == 0) {
        start_time2 = MPI_Wtime();

        double *result = calloc(matrixSize, sizeof(double));

        for (int i = 0; i < chunk_size; i++) {result[i] = myResult[i];}

        for (int i = 1; i < num_procs; i++) {MPI_Recv(result + i * chunk_size, chunk_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);}

        end_time2 = MPI_Wtime();

        //--------------------WRITING STARTS HERE---------------------------
        // open output file depending on the situation "w" or "a". "a" for the second time writing, for the smaller matrix.
        fptr = (matrixSize > unusedSize) ? fopen(filename, "w") : fopen(filename, "a");

        // check if the output file exists
        if (fptr == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        // writing matrix into the file 
        fprintf(fptr, "Matrix:\n");
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {fprintf(fptr, "%f ", myArray[i][j]);}
            fprintf(fptr, "\n");
        }

        // writing vector into the file
        fprintf(fptr, "\nVector:\n");
        for (int i = 0; i < matrixSize; i++) {fprintf(fptr, "%f ", myVector[i]);}

        // writing result into the file
        fprintf(fptr, "\n\nResult:\n");
        for (int i = 0; i < matrixSize; i++) {fprintf(fptr, "%f ", result[i]);}

        fprintf(fptr, "\n\n\n");

        fclose(fptr);
        //--------------------WRITING ENDS HERE-----------------------------

        free(result);

        if (matrixSize > unusedSize)
            printf("Elapsed time is %lf seconds for parallel mxv with %d processes (large matrix)\n", ((end_time1 - start_time1) + (end_time2 - start_time2)), num_procs);
        else
            printf("Elapsed time is %lf seconds for parallel mxv with %d processes (small matrix)\n", ((end_time1 - start_time1) + (end_time2 - start_time2)), num_procs);
    } 
    else {
        double temp_start = MPI_Wtime();
        MPI_Send(myResult + start, chunk_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        double temp_end = MPI_Wtime();

        time3 += (temp_end - temp_start);
    }

    free(myArray);
    free(myVector);
    free(myResult);
}