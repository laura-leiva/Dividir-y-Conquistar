#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono> // Para medir el tiempo

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

int main() {
    // Medir el tiempo total de ejecución
    auto start = std::chrono::high_resolution_clock::now();

    std::string filename;
    std::cout << "Ingrese el nombre del archivo: ";
    std::getline(std::cin, filename);
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    int count;
    infile >> count;
    infile.ignore();
    std::vector<int> arr(count);
    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    for (int i = 0; i < count; ++i) {
        if (!(iss >> arr[i])) {
            std::cerr << "Error al leer los números." << std::endl;
            return 1;
        }
    }
    infile.close();

    // Medir el tiempo de ejecución del algoritmo de ordenación
    auto sortStart = std::chrono::high_resolution_clock::now();
    selectionSort(arr);
    auto sortEnd = std::chrono::high_resolution_clock::now();

    // Guardar el array ordenado en resultado.txt
    std::ofstream outfile("resultado.txt");
    if (!outfile) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }
    for (const int& num : arr) {
        outfile << num << " ";
    }
    outfile.close();

    // Calcular y mostrar el tiempo de ejecución del algoritmo de ordenación en microsegundos
    auto sortDuration = std::chrono::duration_cast<std::chrono::microseconds>(sortEnd - sortStart);
    std::cout << "Tiempo de ejecución de selectionSort: " << sortDuration.count() << " microsegundos." << std::endl;

    return 0;
}
