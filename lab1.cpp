#include <iostream>
using namespace std;
#include <chrono>
#include <unistd.h>

const int MAX = 10000;
double A[MAX][MAX], x[MAX], y[MAX];

/* Initialize A and x, assign y = 0 */
void initArray(){
    for(int i=0; i<MAX; i++){
        y[i] = 0;
        x[i] = 2;
        for (int j=0; j<=i; j++){
            A[i][j] = 2;
        }
    }
}

void initSumArray(){
    for(int i=0; i<MAX; i++){
        y[i] = 0;
    }
}


int main(){
    int i,j;
    unsigned t0, t1;
    initArray();
    
    auto start = chrono::steady_clock::now();

    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            y[i] += A[i][j]*x[j];
    
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution Time: " << time << endl;

    /* Assign y = 0 */
    initSumArray();

    start = chrono::steady_clock::now();

    for (j = 0; j < MAX; j++)
        for (i = 0; i < MAX; i++)
            y[i] += A[i][j]*x[j];
        
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution Time: " << time << endl;
}