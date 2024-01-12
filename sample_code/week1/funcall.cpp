// funcall.cpp

//
// Tests with function calls.
//

#include <iostream>

using namespace std;

void a()
{
    cout << "a() called\n";
}

void b(int i)
{
    cout << "b(" << i << ") called\n";
}

int c(string s)
{
    int n = s.size();
    cout << "c(\"" << s << "\") called, n=" << n << "\n";
    return n;
}

void main1()
{
    cout << "main2() called\n";
    a();
    b(42);
    cout << c("hi!") << "\n";
}

//
// Functions d, e, and f all have their own local copy of a variable i. While
// the name is the same, they each refer to different values.
//

void f()
{
    int i = 7;
    cout << "f() called, i=" << i << "\n";
}

void e()
{
    int i = 4;
    cout << "e() called, i=" << i << "\n";
    f();
}

void d()
{
    int i = 2;
    e();
    cout << "d() called, i=" << i << "\n";
}

void main2()
{
    int i = 0;
    cout << "main2() called, i=" << i << "\n";
    f();
}

int main()
{
    // main1();
    main2();
}