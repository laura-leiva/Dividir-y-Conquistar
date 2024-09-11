#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono> 

// Función para mezclar dos mitades de un arreglo ordenado
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  
    int n2 = right - mid;     
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    int i = 0; 
    int j = 0;
    int k = left; 
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Función recursiva que implementa mergesort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    mergeSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start; // Tiempo en microsegundos

    std::ofstream outfile("resultado.txt");
    for (const int& num : arr) {
        outfile << num << " ";
    }
    outfile.close();
    std::cout << "Tiempo de ejecución de mergeSort: " << duration.count() << " microsegundos." << std::endl;

    return 0;
}
