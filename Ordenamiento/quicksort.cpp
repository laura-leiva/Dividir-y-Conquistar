#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono> 

void swap(std::vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::string filename;
    std::cout << "Ingrese el nombre del archivo: ";
    std::getline(std::cin, filename);
    std::ifstream infile(filename);
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
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start; // Tiempo en microsegundos
    std::ofstream outfile("resultado.txt");
    for (const int& num : arr) {
        outfile << num << " ";
    }
    outfile.close();

    std::cout << "Tiempo de ejecución de quickSort: " << duration.count() << " microsegundos." << std::endl;

    return 0;
}
