// see https://eel.is/c++draft/over.ics.rank

#include <iostream>

#include <vector>
#include <utility>

using obj_t = std::vector<int>;

struct Dummy {

    void set_value(obj_t obj) {
        std::cout << "value version\n";
        value = obj;
    }

    void set_value(obj_t& obj) {
        std::cout << "reference version\n";
        value = obj;
    }

    void set_value(const obj_t& obj) {
        std::cout << "const reference version\n";
        value = obj;
    }

    void set_value(obj_t&& obj) {
        std::cout << "move semantics version\n";
        value = std::move(obj);
    }

private: 
    obj_t value;
};

struct LessUnclearDummy {
    void set_value(const obj_t& obj) {
        std::cout << "const reference version\n";
        value = obj;
    }

    void set_value(obj_t&& obj) {
        std::cout << "move semantics version\n";
        value = std::move(obj);
    }

private: 
    obj_t value;
};

int main() {

    obj_t obj{0,1,2,3,4,5,6};

    Dummy dummy;

    // dummy.set_value(obj); //doesn't work
    // dummy.set_value(std::as_const(obj)); // doesn't work

    LessUnclearDummy less_unclear_dummy;

    // see https://eel.is/c++draft/over.ics.rank#:~:text=if%20not%20that%2C-,(3.2.3),-S1%20and%20S2
    less_unclear_dummy.set_value(obj); // const reference version
    less_unclear_dummy.set_value(std::move(obj)); // move semantics version
    less_unclear_dummy.set_value({1,2,3}); // move semantics version
}