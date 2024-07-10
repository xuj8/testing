#include <string>
#include <iostream>
#include <limits>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...); // Extra space for '\0'
    if( size_s < 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::string result(size_s+1, '\0');
    std::snprintf(&result[0], size_s+1, format.c_str(), args ...);
    result.resize(size_s);
    return result;
}

int main() {
    while(true) {
        double d;
        std::cin >> d;
        
        std::cout << string_format("%.*g\n", (int) std::numeric_limits<double>::max_digits10, d);
    }

}