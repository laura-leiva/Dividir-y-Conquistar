#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generarMatrix(int size, int maxValue = 1000) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % (2 * maxValue + 1) - maxValue; // Genera valores entre -maxValue y maxValue
        }
    }
    return matrix;
}

void GuardarMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, const string& filename) {
    ofstream file(filename);
    int sizeA = matrixA.size();
    int sizeB = matrixB.size();
    file << sizeA << endl;
    for (const auto& row : matrixA) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }
    file << endl;
    file << sizeB << endl;
    for (const auto& row : matrixB) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    int maxSize = 250; 
    int minSize = 1;  
    int size = rand() % (maxSize - minSize + 1) + minSize;
    vector<vector<int>> matrixA = generarMatrix(size);
    vector<vector<int>> matrixB = generarMatrix(size);
    GuardarMatrices(matrixA, matrixB, "matrices.txt");
    cout << "Matrices generadas y guardadas en matrices.txt." << endl;
    return 0;
}
