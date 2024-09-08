#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono> // Para medir el tiempo
#include <algorithm> // Para std::sort

int main() {
    std::string inputFilename;
    std::cout << "Ingrese el nombre del archivo de entrada: ";
    std::getline(std::cin, inputFilename);
    std::ifstream infile(inputFilename);
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
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(arr.begin(), arr.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start; 
    std::ofstream outfile("resultado.txt");
    for (const int& num : arr) {
        outfile << num << " ";
    }
    outfile.close();
    std::cout << "Tiempo de ejecución de std::sort: " << duration.count() << " microsegundos." << std::endl;
    return 0;
}
