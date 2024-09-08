#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int size = std::rand() % 1000000 + 1;
    std::vector<int> numbers(size);
    for (int& num : numbers) {
        num = std::rand() % 10001;
    }
    std::ofstream outfile("lista.txt");
    outfile << size << std::endl;
    for (const int& num : numbers) {
        outfile << num << " ";
    }
    outfile.close();
    return 0;
}
