#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>  

using namespace std;
using namespace std::chrono;  

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
            if (!(file >> matrixA[i][j])) {
                cerr << "Error al leer los datos de la primera matriz en el archivo: " << filename << endl;
                exit(1);
            }
        }
    }

    // Leer la segunda matriz
    file >> rowsB >> colsB;
    vector<vector<int>> matrixB(rowsB, vector<int>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            if (!(file >> matrixB[i][j])) {
                cerr << "Error al leer los datos de la segunda matriz en el archivo: " << filename << endl;
                exit(1);
            }
        }
    }

    return make_pair(matrixA, matrixB);
}

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

vector<vector<int>> transposeMatrix(const vector<vector<int>>& B) {
    int rows = B.size();
    int cols = B[0].size();
    vector<vector<int>> BT(cols, vector<int>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            BT[j][i] = B[i][j];
        }
    }
    return BT;
}

vector<vector<int>> Optimizado(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int p = B[0].size();
    int n = B.size();
    vector<vector<int>> C(m, vector<int>(p, 0));
    vector<vector<int>> BT = transposeMatrix(B);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
    return C;
}

int main() {
    string inputFile, resultFile;
    cout << "Ingrese el nombre del archivo que contiene ambas matrices: ";
    cin >> inputFile;

    auto matrices = LeerMatrices(inputFile);
    vector<vector<int>> A = matrices.first;
    vector<vector<int>> B = matrices.second;
    auto start = high_resolution_clock::now();
    vector<vector<int>> C = Optimizado(A, B);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    GuardarMatriz(C, "resultado.txt");
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
    
    return 0;
}
