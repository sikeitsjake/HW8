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

class Matrix {
    public:
        // 2D Vector Matrix
        vector<vector<int>> m_data;
        string m_name;
        int m_cols;
        int m_rows;

        Matrix(int rows, int cols, string name, int value = 0);
        void populate();
        void printMatrix();
        Matrix findTranspose();
        Matrix operator*(int scalar);
        Matrix operator*(const Matrix);
        Matrix operator+(const Matrix);

};

int main() {
    // make matrix A (2x2) and populate
    Matrix A(2, 2, "A");
    A.populate();

    // make a 2x3 matrix and populate
    Matrix B(2, 3, "B");
    B.populate();

    // make matrix C, populate, then find its transpose.
    Matrix C(2, 3, "C");
    C.populate();
    Matrix CTranspose = C.findTranspose();

    try {
        Matrix D = A + (B * 3) * CTranspose;
        D.printMatrix();
    }
    catch(const out_of_range error) {
        cout << "Execption has Occured: " << error.what() << endl;
        return 1;
    }

    return 0;
}

Matrix::Matrix(int rows, int cols, string name , int value) {
    m_data = vector<vector<int>>(rows, vector<int>(cols, value));
    m_name = name;
    m_cols = cols;
    m_rows = rows;
}

void Matrix::populate() {
    cout << "Populating Matrix: " << m_name << endl;
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            cout << "Enter element for matrix position (" << i << ", " << j << "): ";
            cin >> m_data[i][j];
        }
    }
    cout << endl;
}

void Matrix::printMatrix() {

    // Iterates the matrix and prints each index
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            cout << m_data[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::findTranspose() {
    Matrix tranpose(m_cols, m_rows, m_name + "Trans");

    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            tranpose.m_data[j][i] = m_data[i][j];
        }
    }

    return tranpose;
}

Matrix Matrix::operator*(int scalar) {

    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_data[i][j] = m_data[i][j] * scalar;
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix rhs) {

    if(m_rows != rhs.m_cols) {
        throw out_of_range("Matrix A cannot be multiplied by Matrix B");
    }

    Matrix result(m_rows, rhs.m_cols, "result");

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < rhs.m_cols; ++j) {
            result.m_data[i][j] = 0;
            for (int k = 0; k < m_cols; ++k) {
                result.m_data[i][j] += m_data[i][k] * rhs.m_data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix rhs) {
    if(rhs.m_rows != m_rows || rhs.m_cols != m_cols) {
        throw out_of_range("Cannot add these Matricies");
    }

    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_data[i][j] += rhs.m_data[i][j];
        }
    }
    return *this;
}