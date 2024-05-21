
#include <iostream>
#include <variant>
#include <string>

#define debug(a) {std::cout << #a << " is " << type_names[(a)] << '\n';}

struct NonDefaultConstructible {
    int a;

    NonDefaultConstructible() = delete;
    NonDefaultConstructible(int _a): a{_a} {};
};

using var_t = std::variant<std::string, std::nullptr_t, float, double, int, long long, bool>;
using non_default_t = std::variant<NonDefaultConstructible, std::string>;
using non_default_but_default_first_t = std::variant<std::string, NonDefaultConstructible>;

std::string type_names[] = {
    "string type",
    "null pointer type",
    "float type",
    "double type",
    "int type",
    "long long type",
    "bool type"
};

void test_assignment() {
    var_t dummy_var;

    debug(dummy_var.index()); // by default, index is 0

    debug((dummy_var = nullptr).index()); // nullptr type

    debug((dummy_var = 0).index()); // int type
    debug((dummy_var = 1).index());

    debug((dummy_var = (int) 0).index()); // int type
    debug((dummy_var = (int) 1).index());

    debug((dummy_var = 0LL).index()); // long long type
    debug((dummy_var = 1LL).index());

    debug((dummy_var = 0.).index()); // double types
    debug((dummy_var = 1.).index());
    debug((dummy_var = 0.0).index());
    debug((dummy_var = 1.0).index());
    debug((dummy_var = 1.1).index());

    debug((dummy_var = (float) 0.).index()); // float types
    debug((dummy_var = (float) 1.).index());
    debug((dummy_var = (float) 0.0).index());
    debug((dummy_var = (float) 1.0).index());
    debug((dummy_var = (float) 1.1).index());

    debug((dummy_var = (double) 0.).index()); // double types
    debug((dummy_var = (double) 1.).index());
    debug((dummy_var = (double) 0.0).index());
    debug((dummy_var = (double) 1.0).index());
    debug((dummy_var = (double) 1.1).index());

    debug((dummy_var = "123").index()); // string types
    
    debug((dummy_var = false).index());
    debug((dummy_var = true).index());
}

void test_non_default_constructible() {
    //non_default_t v; // won't work
    non_default_t x = NonDefaultConstructible(1); // ok
    non_default_t y = std::string(); // ok

    non_default_but_default_first_t z; // ok because default constructor exists for first type
    std::cout << "index of variant w/ non default constructible class and now default constructed using its first default constructible type: " << z.index() << '\n'; // 0
}

void print_separator() {
    std::cout << std::string(50, '-') << '\n';
}

int main() {
    test_assignment();
    print_separator();
    test_non_default_constructible();

}