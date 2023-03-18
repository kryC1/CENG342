#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <hellomake.h>

void myMatrixVectorMul(int rows, int cols, char* filename) {

	long int myID = 18050111056;

    // create 2d array using malloc
    double **myArray = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {myArray[i] = malloc(cols * sizeof(double));}
    
    // fill the array with random numbers, seed:18050111056
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            myArray[i][j] = ((double)rand() / RAND_MAX) * 100.0;
        }
    }

    // create and fill the vector with random numbers
    double *myVector = malloc(cols * sizeof(double));
    srand(myID);
    for (int i = 0; i < cols; i++) {
        myVector[i] = ((double)rand() / RAND_MAX) * 100.0;
    }

    // create result array and perform matrix-vector multiplication
    double *myResult = calloc(rows, sizeof(double));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            myResult[i] += myArray[i][j] * myVector[j];
        }
    }

    // create output file
    FILE *fptr = fopen(filename, "w");

    // check if the output file exists
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // writing array into the file 
    fprintf(fptr, "Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fptr, "%f ", myArray[i][j]);
        }
        fprintf(fptr, "\n");
    }

    // writing vector into the file
    fprintf(fptr, "\nVector:\n");
    for (int i = 0; i < cols; i++) {
        fprintf(fptr, "%f ", myVector[i]);
    }

    // writing multiplication result into the file
    fprintf(fptr, "\n\nResult:\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fptr, "%f ", myResult[i]);
    }

    // close the file
    fclose(fptr);

    // free the allocated memory
    for (int i = 0; i < rows; i++) {
        free(myArray[i]);
    }
    free(myArray);
    free(myVector);
    free(myResult);
}
