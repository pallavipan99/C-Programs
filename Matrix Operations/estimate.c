#include <stdio.h>
#include <stdlib.h>

void multiply(double **matrix_x, double **matrix_y, double **matrix_result, int rows, int cols_one, int cols_two){
    for(int x = 0; x<rows; x++){
        for(int y = 0; y<cols_two; y++){
            matrix_result[x][y] = 0;
            for(int z = 0; z<cols_one; z++){
                matrix_result[x][y]+= matrix_x[x][z]*matrix_y[z][y];
            }
        }
    }
}

void transpose(double **matrix_x, double **matrix_result, int rows, int cols){
    for(int x = 0; x<rows; x++){
        for(int y = 0; y<cols; y++){
            matrix_result[y][x] = matrix_x[x][y];
        }
    }
}

