/*
Author: Jacob Folderauer
Date: 4/13/2025
Class: Dr. Kidd UMBC CMSC 313, Section 0830
Title: matrix.cpp
*/

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class MatrixCalc {
    public:
        void calculateD(int A[2][2], int B[2][3], int CT[3][2], int finalMatrix[2][2]);
        void multiplyBCT(int B[2][3], int CT[3][2], int result[2][2]);
        void scalar3(int B[2][3], int scalar = 3);
        void addAResult(int A[2][2], int result[2][2]);
};

int main() {
    MatrixCalc calc;
    int A[2][2] = {{6, 4}, {8, 3}};
    int B[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int CT[3][2] = {{2, 1}, {4, 3}, {6, 5}};
    int resultMatrix[2][2];

    calc.calculateD(A, B, CT, resultMatrix);

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

void MatrixCalc::calculateD(int A[2][2], int B[2][3], int CT[3][2], int finalMatrix[2][2]) {
    scalar3(B, 3);
    multiplyBCT(B, CT, finalMatrix);
    addAResult(A, finalMatrix);
}

void MatrixCalc::multiplyBCT(int B[2][3], int CT[3][2], int result[2][2]) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for(int k = 0; k < 3; k++) {
                result[i][j] += B[i][k] * CT[k][j];
            }
        }
    }
    return;
}

void MatrixCalc::scalar3(int B[2][3], int scalar) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            B[i][j] *= scalar;
        }
    }
}

void MatrixCalc::addAResult(int A[2][2], int result[2][2]) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            result[i][j] += A[i][j];
        }
    }
}