namespaces must be declared in global scope or inside another namespace.

I tried to declare a namespace inside a class. Doesn't work.

See this definition

C++11 7.3-p4: Every namespace-definition shall appear in the global scope or in a namespace scope (3.3.6).


## full answer from stackexchange:

Since you asked which parts of the standard mandate namespace location, we hit that up first:

>**C++11 7.3-p4:** Every namespace-definition shall appear in the global scope or in a namespace scope (3.3.6).

Regarding class definitions and the proposition of declaring a namespace within, I bring you to...
>**C++11 9.2-p2:** A class is considered a completely-defined object type (3.9) (or complete type) at the closing } of the class-specifier. Within the class member-specification, the class is regarded as complete within function bodies, default arguments, exception-specifications, and brace-or-equal-initializers for non-static data members (including such things in nested classes). Otherwise it is regarded as incomplete within its own class member-specification.

Ergo, a class definition is finite once the closing curly is reached. It cannot be opened back up and extended (derivation is something different, but it is NOT extending *the class just defined*).

But lurking at the very beginning of the standard definition of a namespace is the ability to extend it; to expand it for lack of a better term:

>**C++ 7.3-p1:** A namespace is an optionally-named declarative region. The name of a namespace can be used to access entities declared in that namespace; that is, the members of the namespace. **Unlike other declarative regions, the definition of a namespace can be split over several parts of one or more translation units.** (emphasis added).

Therefore, a namespace within a class would violate the definition in 7.3-p4. Assuming that was not present, it would be *possible* to declare a namespace anywhere, including in a class, but since the definition of a class is formalized once it is closed, you would be left with only the ability to do the following if you maintained compliance with 7.3-p1:

    class Foo
    {
       namespace bar
       {
           ..stuff..
       }
    
       .. more stuff ..
    
       namespace bar
       {
           ..still more stuff..
       }
    };

The usefulness of this *feature* was likely debated for about 3-full-seconds before 7.3-p4 was established to settle it.
