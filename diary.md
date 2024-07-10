2024 may 20 - namespaces cannot be declared inside of classes. they must be in their own namespace or in a global scope. (C++)

strings don't print quotes. need to add manually.

2024 may 22 - pairs and maps and basically all stl containers save for vectors and lists and forward_lists need complete types on definition. See https://stackoverflow.com/questions/38898935/forward-declaration-of-objects-with-stl-containers. For containers that are compatible with incomplete types, one can use Boost: https://www.boost.org/doc/libs/1_51_0/doc/html/container/containers_of_incomplete_types.html. 

C++ implicitly converts from char* and const char* to bool for some reason... which means for variant, if I wanna take std::string and bool, I also need to define same function for const char*, otherwise string literals and char* will convert to bool, and not std::string...

I previously had char*, bool, and double constructors, and it was confused between all three when i passed in an int for implicit conversion. So I needed to define a custom one taking int... i wonder if I need to also define the long long and other numeric types via templates. 

2024 may 25 - be really careful about how C++ implicitly casts between ptr types, i forgot to include a nullptr_t type constructor and it automatically cast it to const char *, which means it crashed my program everytime, combined with the fact that i didn't print any messages for try catch which i put everywhere, i though i had parsed wrong...

2024 June 6 - (back from vacay :D) lvalues and rvalues got split into

glvalues (generalized lvalues) -> lvalues, xvalues

rvalues -> xvalues, prvalues (pure rvalues)

basically, something that was expiring and is an rvalue, could still be a reference. In that case, it is still referring to an lvalue, so it is considered both a generalized lvalue (it refers to a generalized lvalue) and an rvalue (it is an expiring reference)

however, things like non-reference rvalues are pure rvalues, because they don't refer to any rvalue. if we don't take it here and now, the object or thing is free to be disposed of. those are pure rvalues

and if the thing is not an expriing thing, e.g. a defined reference to an object, it is a lvalue.

2024 June 10 - CRC vs Hamming
https://stackoverflow.com/questions/35716176/when-should-hamming-codes-be-used-and-when-is-crc-better


