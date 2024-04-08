## Move Semantics
**Move semantics** in C++ is a feature that helps avoid making unnecessary copies. For example:
```cpp
vector<int> range(int n) {
	vector<int> result;
	for(int i = 0; i < n; i++) {
		result.push_back(i);
	}
	
	return result;
}
```
C++ return values are, by default, passed by value, which means that a copy of the value being returned is made. So in `range` a copy of `result` is made when it's returned, which is inefficient.

Move semantics solve this problem by allowing the underlying array of `result` to be passed without making a copy. It essentially does this using a special move constructor. So in `range` there is no extra copy of the vector made, saving time and memory.
## Support for Compile-time Meta-programming
It turns out that C++ templates are powerful enough to do almost anything at compile-time. So C++ has gradually been adding features to make it easier to computations at compile-time. 

For example, `constexpr` lets you assign constants and do some simple calculations at compile-time:
```cpp
constexpr int a = 3;
constexpr int b = 5 * a + 1; // b is 16
```
The calculation of `b` is done by the compiler at compile-time, and so takes no time when the program is running. Using templates and other features, it is also possible to write functions that are evaluated at compile-time. This gets complex pretty quickly, but check out examples online if you are curious. It's powerful stuff when used well.
## Smart Pointers
In C++, smart pointers are pre-defined standard classes that uses templates to simplify the management of memory. Instead of calling `new` and `delete`, you make smart pointers that do it for you. For instance:
```cpp
#include <memory>

void demo() {
    std::unique_ptr<int> p = std::make_unique<int>(42);
    
    cout << "Value: " << *p;

    // No need to manually delete the pointer, it's 
    // automatically deleted when it goes out of scope
}
```
`p` is a value of type `unique_ptr<int>`, and it works much like a regular C++ pointer. However, you do not need to call `new`/`delete` on it, and so memory management is automatic and less error-prone than with regular pointers.
## More OOP
C++ has many other object-oriented features that we didn't discuss in this course. For example:
- **Constructor delegation** is technique that lets you call other constructors in the [[initialization list|initializer list]] of a constructor. 
- **Friend functions** are functions (not methods!) that are allowed to access the private parts of an object.
- **Multiple inheritance** is when a class inherits from two, or more, other classes at the same time. This can be useful in some cases, but it presents the problem of what to do when the classes being inherited from happen to have different implementations for a method with the same name.
## Type Inference
The `auto` keyword can be used to infer the types of variables in some situations. For example:
```cpp
auto a = 5;     // a is inferred to be of type int
auto b = -3.92; // b is inferred to be of type double
auto c = "cat"; // c is inferred to be of type string
```
The types are inferred by the compiler and compile-time, so there is never any performance penalty for using `auto`.

C++ type names, especially ones that use templates, can get quite long and hard to read, and so `auto` is useful when it shortens expressions in a way that makes them more readable:
```cpp
vector<vector<int>> table = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

for (auto row : table) {
    for(auto val : row) {
        cout << val << " ";
    }
}
```
## Scoped Enumerations
In C and C++ you can create **enumerations**, which are essentially types with a finite set of name values. For example:
```cpp
enum Semester { Spring, Summer, Fall };

Semester s1 = Fall;
Semester s2 = Spring;
```
`Suit` is an example of an **unscoped enumeration**. `Spring`, `Summer`, and `Fall` are essentially integer constants that have the same scope as `Semester`. That means, for example, that if you were to defined `Semester` globally, then `Spring`, `Summer`, and `Fall` would also become global names. This can lead to confusion, e.g. you cannot also have an enumeration like this:
```cpp
enum Season {Spring, Summer, Fall, Winter}; // oops: Spring etc.
                                            //       already defined
                                            //       in Semester
```
To solve this problem, C++ has added **scoped enumerations** that are declared with the keyword `class` like this:
```cpp
enum class Semester { Spring, Summer, Fall };
enum class Season {Spring, Summer, Fall, Winter};
```

With scoped enumerations it's fine to have values with the same name. To access the values in `Semester` you must write `Semester::Spring`, `Semester::Summer`, and `Semester::Fall`. Similar, for `Season` you must write `Season::spring`, `Season::Summer`, etc.
## Lambda Expressions
A **lambda expression** (or **lambda function**) is essentially a function with no name. Lambda expressions have proven to be quite useful in other languages, and so C++ provides a way to use them. 

For example, lambda expressions can be pass to the `sort` function to change how comparisons work:

```cpp
// arr is an array of n float values
std::sort(arr, x + n,
          [](float a, float b)   // lambda expression
          {
            return (b < a);      // sorts in reverse
          }
);
```

In some cases passing a lambda function can be simpler then writing a regular function with a name. 
## Concepts
**Concepts** are a way to put constraints on the types used in templates. For example:

```cpp
template <typename T>
requires std::integral<T> || std::floating_point<T>

double average(vector<T> const &vec) {
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);  
    return sum / vec.size();
}
```

`average` is a template function that works with any type `T` that satisfied either the `integral` concept or the `floating_point` concept. In other words, `T` is some type that be treated like a number.

Concepts help make code wore explicit and readable. Plus they also have make template error messages shorter and easier to understand.
## Modules
**Modules** are an alternative to `#include` as used in separately-compiled files. The use of `#include` for sharing library code can be hard to read and reason about, and it's a major reason why compiling large programs can be so slow. Modules are a more modern approach used by many other languages.

Here's an example of what modules look like:
```cpp
// helloworld.cpp

export module helloworld; // module declaration
 
import <iostream>;        // import the iostream module
 
export void hello()       // export declaration
{
    std::cout << "Hello world!\n";
}
```
You can use it like this:
```cpp
// main.cpp
import helloworld; // import the helloworld module
 
int main()
{
    hello();
}
```
## C++ Core Guidelines
[The C++ Code Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are a large set of "guidelines for using C++ well". They contain a wealth of programming advice for C++, and the hope is that many of the guidelines could be automated for use in tools that you can run on your C++ code. 

For example, the [guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) guidelines 56 rules for using C++ functions. The first few are:

- [F.1: “Package” meaningful operations as carefully named functions](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-package)
- [F.2: A function should perform a single logical operation](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-logical)
- [F.3: Keep functions short and simple](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-single)
- [F.4: If a function might have to be evaluated at compile time, declare it `constexpr`](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-constexpr)
- [F.5: If a function is very small and time-critical, declare it inline](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-inline)
- [F.6: If your function must not throw, declare it `noexcept`](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-noexcept)
- [F.7: For general use, take `T*` or `T&` arguments rather than smart pointers](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-smart)
- [F.8: Prefer pure functions](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-pure)
- [F.9: Unused parameters should be unnamed](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-unused)
- [F.10: If an operation can be reused, give it a name](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-name)
- [F.11: Use an unnamed lambda if you need a simple function object in one place only](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-lambda)
