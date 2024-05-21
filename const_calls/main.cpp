
#include <string>
#include <iostream>
#include <utility>


struct DummyStruct {
    int a = 0;
    char b = 'z';
    std::string c = "";

    DummyStruct& gimme() {
        std::cout << "non const version\n";
        return *this;
    }

    const DummyStruct& gimme() const {
        std::cout << "const version\n";
        return *this;
    }
};

int main() {

    DummyStruct obj;

    std::cout << "Testing non-const struct\n";
    auto default_gimme = obj.gimme(); // non const version
    default_gimme.a = 1;
    std::cout << obj.a << '\n'; // 1

    const auto const_gimme = obj.gimme(); // non const version
    // const_gimme.a = 2; // won't work

    auto& ref_gimme = obj.gimme(); // non const version
    ref_gimme.a = 3;
    std::cout << obj.a << '\n'; // 3

    const auto& const_ref_gimme = obj.gimme(); // non const version
    // const_ref_gimme.a = 4; // won't work

    DummyStruct new_struct = obj.gimme(); // non const version
    new_struct.a = 5;
    std::cout << obj.a << '\n'; // 3

    DummyStruct& new_ref_struct = obj.gimme(); // non const version
    new_ref_struct.a = 6;
    std::cout << obj.a << '\n'; // 6

    const DummyStruct& new_const_ref_struct = obj.gimme(); // non const version

    // C++20 <utility>
    std::as_const(obj).gimme(); // const version

    std::cout << "Testing new_const_ref_struct\n";

    new_const_ref_struct.gimme(); // const version

    std::cout << "Testing new const DummyStruct\n";
    const DummyStruct new_const_struct;
    new_const_struct.gimme(); // const version


}
