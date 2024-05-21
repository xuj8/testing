
#include <iostream>
#include <variant>
#include <string>

#define debug(a) {std::cout << #a << " is " << type_names[(a)] << '\n';}

enum class VariableTypes {
    EMPTY,
    STR,
    FLOAT,
    INT,
    BOOL
};

using var_t = std::variant<std::nullptr_t, std::string, float, double, int, bool>;

std::string type_names[] = {
    "null pointer type",
    "string type",
    "float type",
    "double type",
    "int type",
    "bool type"
};

int main() {
    var_t dummy_var;

    debug((dummy_var = nullptr).index());

    debug((dummy_var = 0).index());
    debug((dummy_var = 1).index());

    debug((dummy_var = 0.).index());
    debug((dummy_var = 1.).index());
    debug((dummy_var = 0.0).index());
    debug((dummy_var = 1.0).index());
    debug((dummy_var = 1.1).index());

    debug((dummy_var = (float) 0.).index());
    debug((dummy_var = (float) 1.).index());
    debug((dummy_var = (float) 0.0).index());
    debug((dummy_var = (float) 1.0).index());
    debug((dummy_var = (float) 1.1).index());

    debug((dummy_var = (double) 0.).index());
    debug((dummy_var = (double) 1.).index());
    debug((dummy_var = (double) 0.0).index());
    debug((dummy_var = (double) 1.0).index());
    debug((dummy_var = (double) 1.1).index());

    debug((dummy_var = "123").index());
    
    debug((dummy_var = false).index());
    debug((dummy_var = true).index());
}