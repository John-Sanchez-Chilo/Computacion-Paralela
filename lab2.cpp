#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <chrono>
#include <unistd.h>
#include <cmath>
using namespace std;

int** create_random_matrix_nxm(int n, int m){
    int **new_matrix = new int*[n];
    for(int i=0;i<n;i++){
        new_matrix[i] = new int[m];
        for(int j=0; j<m; j++){
            new_matrix[i][j] = 1 + rand() % (10);
        }
    }
    return new_matrix;
}

int** create_0_matrix_nxm(int n, int m){
    int **new_matrix = new int*[n];
    for(int i=0;i<n;i++){
        new_matrix[i] = new int[m];
        for(int j=0; j<m; j++){
            new_matrix[i][j] = 0;
        }
    }
    return new_matrix;
} 

void classic_multiplication(int **matriz1, int f1, int c1, int **matriz2, int f2, int c2, int** rpta){
    if(c1 != f2){
        return ;
    }
    for (int i = 0; i < f1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                rpta[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}

void blocks_multiplication(int **matriz1, int f1, int c1, int **matriz2, int f2, int c2, int** rpta){
    int blockSize = 100;
    int n = f1;
    for(int bi=0; bi<n; bi+=blockSize)
        for(int bj=0; bj<n; bj+=blockSize)
            for(int bk=0; bk<n; bk+=blockSize)
                for(int i=0; i<blockSize; i++)
                    for(int j=0; j<blockSize; j++)
                        for(int k=0; k<blockSize; k++)
                            rpta[bi+i][bj+j] += matriz1[bi+i][bk+k] * matriz2[bk+k][bj+j];
}

void print_matrix(int **matrix, int n, int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    srand(time(NULL));
    int n = 1000;
    int **matrix1 = create_random_matrix_nxm(n, n);
    int **matrix2 = create_random_matrix_nxm(n, n);
    int **rpta = create_0_matrix_nxm(n, n);

    auto start = chrono::steady_clock::now();
    classic_multiplication(matrix1, n, n, matrix2, n, n, rpta);
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    //print_matrix(rpta1, n, n);
    cout << "Execution Time: " << time << endl;
    for (int i = 0; i < n; i++) {
        delete[] rpta[i];
    }
    delete[] rpta;

    rpta = create_0_matrix_nxm(n, n);
    start = chrono::steady_clock::now();
    blocks_multiplication(matrix1, n, n, matrix2, n, n, rpta);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    //print_matrix(rpta2, n, n);
    cout << "Execution Time: " << time << endl;
    for (int i = 0; i < n; i++) {
        delete[] rpta[i];
        delete[] matrix1[i];
        delete[] matrix2[i];
    }
    delete[] rpta;
    delete[] matrix1;
    delete[] matrix2;
    return 0;
}