#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <random>

void str_concat(int num_concat) {
    std::string s = "";
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(97, 122); 

    for (int i = 0; i < num_concat; ++i) {
        s += static_cast<char>(distribution(generator));
    }
}

void char_concat(int num_concat) {
    char* buffer = new char[num_concat+1]; 
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(97, 122);

    for (int i = 0; i < num_concat; ++i) {
        buffer[i] = static_cast<char>(distribution(generator));
    }

    buffer[num_concat] = '\0';
    delete buffer;
}   

void time_it(std::function<void()> f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    std::vector<int> test_sizes = {1000, 10000, 1000000, 10000000, 100'000'000};

    for (int size : test_sizes) {
        std::cout << "Testing str_concat with size " << size << ":\n";
        time_it([size]() { str_concat(size); });

        std::cout << "Testing char_concat with size " << size << ":\n";
        time_it([size]() { char_concat(size); });
    }

    return 0;
}
