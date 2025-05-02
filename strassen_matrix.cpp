#include <iostream>
using namespace std;

void add(int A[][2], int B[][2], int C[][2], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[][2], int B[][2], int C[][2], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int A[][2], int B[][2], int C[][2], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int newSize = size/2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int P1[newSize][newSize], P2[newSize][newSize], P3[newSize][newSize], P4[newSize][newSize], P5[newSize][newSize], P6[newSize][newSize], P7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];
    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    subtract(B12, B22, temp1, newSize);
    strassen(A11, temp1, P1, newSize);
    
    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, P2, newSize);
    
    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, P3, newSize);
    
    subtract(B21, B11, temp1, newSize);
    strassen(A22, temp1, P4, newSize);
    
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, P5, newSize);
    
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, P6, newSize);
    
    subtract(A11, A21, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, P7, newSize);
    
    add(P5, P4, temp1, newSize);
    subtract(temp1, P2, temp2, newSize);
    add(temp2, P6, C11, newSize);
    
    add(P1, P2, C12, newSize);
    add(P3, P4, C21, newSize);
    
    add(P5, P1, temp1, newSize);
    subtract(temp1, P3, temp2, newSize);
    subtract(temp2, P7, C22, newSize);
    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2];
    strassen(A, B, C, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }
    return 0;
}