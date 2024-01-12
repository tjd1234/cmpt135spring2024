// basic_types.cpp

#include <iostream>
#include <string>
#include <climits>

using namespace std;

typedef unsigned int uint;

int main()
{
    // int a;  // unknown initial value
    int b = 5;
    int b2(5); // alternative initialization syntax
    int b3{5}; // alternative initialization syntax
    int c = 5.5;
    // int c2{5.5}; // error: narrowing conversion
    auto d = 5; // auto: let the compiler figure out the type
    // cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "b2 = " << b2 << "\n";
    cout << "b3 = " << b3 << "\n";
    cout << "c = " << c << "\n"; // prints 5
    // cout << "c2 = " << c2 << "\n";
    cout << "d = " << d << "\n";
    cout << "min int = " << INT_MIN << "\n";
    cout << "max int = " << INT_MAX << "\n";
    cout << "\n";

    // double e; // unknown initial value
    double f = 5;
    double g = 5.5;
    double g2(5.5); // alternative initialization syntax
    double g3{5.5}; // alternative initialization syntax
    auto h = 5.5;   // auto: let the compiler figure out the type
    // cout << "e = " << e << "\n";
    cout << "f = " << f << "\n";
    cout << "g = " << g << "\n";
    cout << "g2 = " << g2 << "\n";
    cout << "g3 = " << g3 << "\n";
    cout << "h = " << h << "\n";
    cout << "\n";

    // char i; // unknown initial value
    char j = 'a';
    char k = 97;  // ASCII value of 'a'
    auto l = 'a'; // auto: let the compiler figure out the type
    // cout << "i = " << i << "\n";
    cout << "j = " << j << "\n";               // prints 'a'
    cout << "k = " << k << "\n";               // prints 'a'
    cout << "int(j) = " << int(j) << "\n";     // prints 97
    cout << "int(k) = " << int(k) << "\n";     // prints 97
    cout << "int('a') = " << int('a') << "\n"; // prints 97
    cout << "char(97) = " << char(97) << "\n"; // prints 'a'
    cout << "l = " << l << "\n";
    cout << "\n";

    // unsigned int m; // unknown initial value
    unsigned int n = 5;
    unsigned int p = -5; // oops: can't represent negative numbers
    auto q = 5u;         // auto: let the compiler figure out the type
    // cout << "m = " << m << "\n";
    cout << "n = " << n << "\n";
    cout << "p = " << p << "\n"; // prints 4294967291
    cout << "q = " << q << "\n";
    cout << "unsigned int min = " << 0 << "\n";
    cout << "unsigned int max = " << UINT_MAX << "\n";
    cout << "\n";

    string r; // "" initial value
    string s = "Hello World!";
    string t("Hello World!");        // alternative initialization syntax
    string u{"Hello World!"};        // alternative initialization syntax
    string v('!', 5);                // alternative initialization syntax
    cout << "r = \"" << r << "\"\n"; // prints ""
    cout << "s = \"" << s << "\"\n";
    cout << "t = \"" << t << "\"\n";
    cout << "u = \"" << u << "\"\n";
    cout << "v = \"" << v << "\"\n"; // prints "!!!!!"
}
