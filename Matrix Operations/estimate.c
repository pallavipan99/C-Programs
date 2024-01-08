#include <stdio.h>
#include <stdlib.h>

// Function to multiply two matrices
void multiply(double **matrix_x, double **matrix_y, double **matrix_result, int rows, int cols_one, int cols_two){
    for(int x = 0; x<rows; x++){
        for(int y = 0; y<cols_two; y++){
            matrix_result[x][y] = 0;
            for(int z = 0; z<cols_one; z++){
                matrix_result[x][y] += matrix_x[x][z] * matrix_y[z][y];
            }
        }
    }
}

// Function to transpose a matrix
void transpose(double **matrix_x, double **matrix_result, int rows, int cols){
    for(int x = 0; x<rows; x++){
        for(int y = 0; y<cols; y++){
            matrix_result[y][x] = matrix_x[x][y];
        }
    }
}

// Function to invert a square matrix using Gaussian elimination
void invert(double **matrix_x, double **matrix_result, int rows, int cols){
    // Initialize result as identity matrix
    for(int x = 0; x<rows; x++){
        for(int y = 0; y<rows; y++){
            if(x == y){
                matrix_result[x][y] = 1;
            } else {
                matrix_result[x][y] = 0;
            }
        }
    }

    // Forward elimination
    for(int p = 0; p<rows; p++){
        double f = matrix_x[p][p];
        for(int y = 0; y<rows; y++){
            matrix_x[p][y] /= f;             // Normalize pivot row
            matrix_result[p][y] /= f;
        }
        for(int i = p+1; i<rows; i++){
            f = matrix_x[i][p];
            for(int x = 0; x<rows; x++){
                matrix_x[i][x] -= matrix_x[p][x] * f;       // Eliminate lower rows
                matrix_result[i][x] -= matrix_result[p][x] * f;
            }
        }
    }

    // Backward substitution
    for(int p = rows-1; p>=0; p--){
        for(int i = p-1; i>=0; i--){
            double f = matrix_x[i][p];
            for(int x = 0; x<rows; x++){
                matrix_x[i][x] -= matrix_x[p][x] * f;
                matrix_result[i][x] -= matrix_result[p][x] * f;
            }
        }
    }  
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        // Program requires exactly 2 input files
        return 1;
    } else {
        // Open first input file for reading
        FILE *ptr_file = fopen(argv[1], "r");
        char file_name_one[6];
        int k, n;

        // Read file name, number of features (k) and number of samples (n)
        fscanf(ptr_file, "%5s %d %d", file_name_one, &k, &n);

        // Allocate memory for feature matrix X and output vector Y
        double **matrix_x = (double **)malloc(n * sizeof(double *));
        double **matrix_y = (double **)malloc(n * sizeof(double *));
        for(int x = 0; x<n; x++){
            matrix_x[x] = (double *)malloc((k+1) * sizeof(double)); // +1 for bias term
            matrix_y[x] = (double *)malloc(sizeof(double));
            matrix_x[x][0] = 1.0; // Set bias term to 1
            for(int y = 1; y<=k; y++){ // Read feature values
                fscanf(ptr_file, "%lf", &matrix_x[x][y]);
            }
            fscanf(ptr_file, "%lf", &matrix_y[x][0]); // Read target value
        }
        fclose(ptr_file);

        // Open second input file (for predictions)
        FILE *ptr_data_file = fopen(argv[2], "r");
        char file_name_two[5];
        int second_k, second_n;
        fscanf(ptr_data_file, "%4s %d %d", file_name_two, &second_k, &second_n);

        if(k != second_k){
            // Feature dimension mismatch
            return 1;
        }

        // Allocate memory for second matrix
        double **second_matrix_x = (double **)malloc(second_n * sizeof(double *)); 
        for(int x = 0; x<second_n; x++){
            second_matrix_x[x] = (double *)malloc((k+1) * sizeof(double)); 
            second_matrix_x[x][0] = 1.0; // Bias term
            for(int y = 1; y<=second_k; y++){
                fscanf(ptr_data_file, "%lf", &second_matrix_x[x][y]);
            }
        }
        fclose(ptr_data_file);

        // Allocate matrices for calculations
        double **matrix_w = (double **)malloc((k+1) * sizeof(double *));
        double **matrix_xT = (double **)malloc((k+1) * sizeof(double *));
        double **matrix_xTx = (double **)malloc((k+1) * sizeof(double *));
        double **matrix_xTx_result = (double **)malloc((k+1) * sizeof(double *));
        double **matrix_xTy = malloc((k+1) * sizeof(double *));
        for(int x = 0; x<=k; x++){
            matrix_w[x] = (double *)malloc(sizeof(double));
            matrix_xT[x] = (double *)malloc(n * sizeof(double));
            matrix_xTx[x] = (double *)malloc((k+1) * sizeof(double));
            matrix_xTx_result[x] = (double *)malloc((k+1) * sizeof(double));
            matrix_xTy[x] = (double *)malloc(sizeof(double));
        }

        // Perform calculations
        transpose(matrix_x, matrix_xT, n, k+1);
        multiply(matrix_xT, matrix_x, matrix_xTx, k+1, n, k+1);
        invert(matrix_xTx, matrix_xTx_result, k+1, n);
        multiply(matrix_xT, matrix_y, matrix_xTy, k+1, n, 1);
        multiply(matrix_xTx_result, matrix_xTy, matrix_w, k+1, k+1, 1);

        // Make predictions for second matrix
        double price = 0.0;
        for(int x = 0; x<second_n; x++){
            for(int y = 0; y<=k; y++){
                price += second_matrix_x[x][y] * matrix_w[y][0];
            }
            printf("%.0f\n", price);
            price = 0.0;
        }  

        // Free allocated memory
        for(int x = 0; x<n; x++){
            free(matrix_x[x]);
            free(matrix_y[x]);
        }
        for(int x = 0; x<second_n; x++){
            free(second_matrix_x[x]);
        }
        for(int x = 0; x<=k; x++){
            free(matrix_w[x]);
            free(matrix_xT[x]);
            free(matrix_xTx[x]);
            free(matrix_xTx_result[x]);
            free(matrix_xTy[x]);
        }
        free(matrix_x);
        free(matrix_y);
        free(second_matrix_x);
        free(matrix_w);
        free(matrix_xT);
        free(matrix_xTx);
        free(matrix_xTx_result);
        free(matrix_xTy);  

        return 0;
    }
}

