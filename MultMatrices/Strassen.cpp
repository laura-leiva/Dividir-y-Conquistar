#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Función para leer matrices desde un archivo
pair<vector<vector<int>>, vector<vector<int>>> LeerMatrices(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    int rowsA, colsA, rowsB, colsB;
    file >> rowsA >> colsA;
    vector<vector<int>> matrixA(rowsA, vector<int>(colsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            file >> matrixA[i][j];
        }
    }
    file >> rowsB >> colsB;
    vector<vector<int>> matrixB(rowsB, vector<int>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            file >> matrixB[i][j];
        }
    }
    return make_pair(matrixA, matrixB);
}

// Función para guardar una matriz en un archivo
void GuardarMatriz(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file(filename);
    int rows = matrix.size();
    int cols = matrix[0].size();
    file << rows << " " << cols << endl;
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }
}

// Funciones auxiliares para la multiplicación de matrices
vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> C(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar dos matrices A y B de las mismas dimensiones
vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> C(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Función para multiplicar matrices en base al algoritmo de Strassen
vector<vector<int>> Strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int size = A.size();
    if (size == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int newSize = size / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
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
    vector<vector<int>> M1 = Strassen(addMatrix(A11, A22), addMatrix(B11, B22));
    vector<vector<int>> M2 = Strassen(addMatrix(A21, A22), B11);
    vector<vector<int>> M3 = Strassen(A11, subtractMatrix(B12, B22));
    vector<vector<int>> M4 = Strassen(A22, subtractMatrix(B21, B11));
    vector<vector<int>> M5 = Strassen(addMatrix(A11, A12), B22);
    vector<vector<int>> M6 = Strassen(subtractMatrix(A21, A11), addMatrix(B11, B12));
    vector<vector<int>> M7 = Strassen(subtractMatrix(A12, A22), addMatrix(B21, B22));
    vector<vector<int>> C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    vector<vector<int>> C12 = addMatrix(M3, M5);
    vector<vector<int>> C21 = addMatrix(M2, M4);
    vector<vector<int>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

// Función para rellenar una matriz con ceros hasta que sea de tamaño n x n
vector<vector<int>> padMatrix(const vector<vector<int>>& matrix, int newSize) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> padded(newSize, vector<int>(newSize, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded[i][j] = matrix[i][j];
        }
    }
    return padded;
}

// Función para encontrar la siguiente potencia de 2 mayor o igual a un número dado
int nextPowerOfTwo(int x) {
    int power = 1;
    while (power < x) power *= 2;
    return power;
}

// Función para multiplicar matrices en base al algoritmo de Strassen
vector<vector<int>> StrassenMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    int newSize = nextPowerOfTwo(max({m, n, p}));
    vector<vector<int>> paddedA = padMatrix(A, newSize);
    vector<vector<int>> paddedB = padMatrix(B, newSize);
    vector<vector<int>> paddedC = Strassen(paddedA, paddedB);
    vector<vector<int>> C(m, vector<int>(p));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            C[i][j] = paddedC[i][j];
        }
    }
    return C;
}

int main() {
    string inputFile, outputFile = "resultado.txt";
    cout << "Ingrese el nombre del archivo que contiene las matrices: ";
    cin >> inputFile;
    auto matrices = LeerMatrices(inputFile);
    vector<vector<int>> A = matrices.first;
    vector<vector<int>> B = matrices.second;

    auto start = high_resolution_clock::now();
    vector<vector<int>> C = StrassenMatrixMultiplication(A, B);
    auto end = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tiempo de ejecución del algoritmo Strassen: " << duration.count() << " microsegundos" << endl;
    GuardarMatriz(C, outputFile);
    return 0;
}
