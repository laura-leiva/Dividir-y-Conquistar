#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono;

// Función para leer dos matrices desde un archivo y devolverlas junto con sus columnas.
// Retorna un par de pares. Cada par contiene una matriz y el número de columnas de esa matriz.
pair<pair<vector<vector<int>>, int>, pair<vector<vector<int>>, int>> LeerMatrices(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    int rowsA, colsA, rowsB, colsB;
    file >> rowsA >> colsA;
    vector<vector<int>> A(rowsA, vector<int>(colsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            if (!(file >> A[i][j])) {
                cerr << "Error al leer los datos de la primera matriz en el archivo: " << filename << endl;
                exit(1);
            }
        }
    }
    file >> rowsB >> colsB;
    vector<vector<int>> B(rowsB, vector<int>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            if (!(file >> B[i][j])) {
                cerr << "Error al leer los datos de la segunda matriz en el archivo: " << filename << endl;
                exit(1);
            }
        }
    }
    return make_pair(make_pair(A, colsA), make_pair(B, colsB));
}

// Función para multiplicar matrices de forma tradicional
vector<vector<int>> Traditional(const vector<vector<int>>& A, const vector<vector<int>>& B, int colsA, int colsB) {
    int rowsA = A.size();
    int rowsB = B.size();
    vector<vector<int>> C(rowsA, vector<int>(colsB, 0));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Función para guardar la matriz en un archivo de salida
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

int main() {
    string filename;
    cout << "Ingrese el nombre del archivo que contiene las matrices: ";
    cin >> filename;

    auto matrices = LeerMatrices(filename);
    vector<vector<int>> A = matrices.first.first;
    int colsA = matrices.first.second;
    vector<vector<int>> B = matrices.second.first;
    int colsB = matrices.second.second;
    auto start = high_resolution_clock::now();
    vector<vector<int>> C = Traditional(A, B, colsA, colsB);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    GuardarMatriz(C, "resultado.txt");
    return 0;
}
