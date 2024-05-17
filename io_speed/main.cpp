#include <fstream>
#include <random>
#include <string>
#include <chrono>
#include <optional>
#include <iostream>

void generate_random_text_file(const std::string& filename, size_t size_in_bytes) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) 
        throw std::runtime_error("Failed to open file for writing.");

    std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<> dis(32, 126);

    for(size_t i = 0; i < size_in_bytes; ++i) {
        char c = static_cast<char>(dis(gen));
        file.put(c);
    }
}

struct BufferReader {
    static constexpr size_t BUFFER_SIZE = 1 << 16;

    BufferReader(std::istream& _stream) : stream(_stream) {
        update_buffer();
    }

    inline operator bool() {
        return good();
    }

    inline std::optional<char> next_byte() {
        if (next_pos.has_value()) {
            char return_val = buffer[*next_pos];
            next_pos = *next_pos + 1;
            if (*next_pos >= cur_read_size)
                update_buffer();
            return return_val;
        } else return std::nullopt;
    }

    bool good() {
        return next_pos.has_value();
    }

private:
    void update_buffer() {
        if (stream) {
            stream.read(buffer, BUFFER_SIZE);
            cur_read_size = stream.gcount();
            next_pos = (cur_read_size > 0) ? std::optional<size_t>(0) : std::nullopt;
        } else {
            next_pos = std::nullopt;
        }
    }

    std::istream& stream;
    size_t cur_read_size;
    char buffer[BUFFER_SIZE];
    std::optional<size_t> next_pos;
};

// Function to benchmark BufferReader
void benchmark_buffer_reader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    BufferReader reader(file);
    auto start = std::chrono::high_resolution_clock::now();
    std::optional<char> c;
    size_t byte_count = 0;
    while (reader) {
        c = reader.next_byte();
        byte_count++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "BufferReader: Read " << byte_count << " bytes in " << duration.count() << " seconds.\n";
}

// Function to benchmark get() method
void benchmark_get_method(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    auto start = std::chrono::high_resolution_clock::now();

    char c;
    size_t byte_count = 0;
    while (file.get(c)) {
        byte_count++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "get() method: Read " << byte_count << " bytes in " << duration.count() << " seconds.\n";
}

int main() {
    const std::string filename = "random_text.txt";
    const size_t size_in_bytes = 100'000'000; // 100 MB

    std::cout << "Generating random text file...\n";
    generate_random_text_file(filename, size_in_bytes);

    std::cout << "Benchmarking BufferReader...\n";
    benchmark_buffer_reader(filename);

    std::cout << "Benchmarking get() method...\n";
    benchmark_get_method(filename);

    return 0;
}