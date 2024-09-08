#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 

using namespace std;

vector<vector<int>> generateMatrix(int rows, int cols, int maxValue = 500) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % maxValue;
        }
    }
    return matrix;
}
void saveMatricesToFile(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, const string& filename) {
    ofstream file(filename);
    int rowsA = matrixA.size();
    int colsA = matrixA[0].size();
    file << rowsA << " " << colsA << endl;
    for (const auto& row : matrixA) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }
    
    file << endl; 

    int rowsB = matrixB.size();
    int colsB = matrixB[0].size();
    file << rowsB << " " << colsB << endl;
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
    int m = rand() % (maxSize - minSize + 1) + minSize;
    int n = rand() % (maxSize - minSize + 1) + minSize;
    int p = rand() % (maxSize - minSize + 1) + minSize;
    vector<vector<int>> matrixA = generateMatrix(m, n);
    vector<vector<int>> matrixB = generateMatrix(n, p);
    saveMatricesToFile(matrixA, matrixB, "matrices.txt");
    return 0;
}
