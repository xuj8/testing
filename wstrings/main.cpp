#include <iostream>
#include <string>
using namespace std;

std::string from_u8(const std::u8string& u8_str) {
    return std::string(u8_str.begin(), u8_str.end());
}

std::string utf8_text = from_u8(u8"Hello, 世界");
std::u8string u8_str_text = u8"Hello, 世界";


int main() {
	std::cout << utf8_text << "\n";
	for(auto c: utf8_text) std::cout << c;
	std::cout << "\n";
	for(auto c: utf8_text) std::cout << c << "\n";

    std::cout << utf8_text.size() << '\n';
    std::cout << utf8_text.length() << '\n';

    std::cout << "-------\n";
    std::cout << u8_str_text.size() << '\n';
    std::cout << u8_str_text.length() << '\n';
    size_t char_cnt = 0;
    for(char8_t c: u8_str_text) char_cnt++;
    std::cout << char_cnt << '\n';
    // std::cout << u8_str_text << "\n";
	// for(char8_t c: u8_str_text) std::wcout << c;
	// std::cout << "\n";
	// for(char8_t c: u8_str_text) std::wcout << c << "\n";
	return 0;
}

