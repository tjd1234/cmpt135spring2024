// pointers.cpp

#include <iostream>

using namespace std;

void test1()
{
    char c = 'a';
    cout << "  value of c: " << c << endl;
    cout << "address of c: " << (int *)&c << endl;
}

void test2()
{
    int n = 5;
    int *a = &n;
    int *b = &n;
    int *c = &n;
    cout << "  value of n: " << n << endl;
    cout << endl;
    cout << "address of n: " << &n << endl;
    cout << "  value of a: " << a << endl;
    cout << "  value of b: " << b << endl;
    cout << "  value of c: " << c << endl;

    n = 2;
    *a = 3;

    cout << "   value of n: " << n << endl;
    cout << "  value of *a: " << *a << endl;
    cout << "  value of *b: " << *b << endl;
    cout << "  value of *c: " << *c << endl;
}

void test3()
{
    int n = 5;
    int *a = &n;
    int *b = &n;
    int *c = &n;
    int **d = &c;
    cout << "  value of n: " << n << endl;
    cout << " value of *a: " << *a << endl;
    cout << " value of *b: " << *b << endl;
    cout << " value of *c: " << *c << endl;
    cout << "value of **d: " << **d << endl;
}

void test4()
{
    int n = 5;
    int *a = &n;
    int *b = &n;
    int *c = &n;
    int **d = &c;
    int ***e = &d;
    cout << "   value of n: " << n << endl;
    cout << "  value of *a: " << *a << endl;
    cout << "  value of *b: " << *b << endl;
    cout << "  value of *c: " << *c << endl;
    cout << " value of **d: " << **d << endl;
    cout << "value of ***e: " << ***e << endl;
}

void test5() {
    int* p = nullptr;
    cout << "value of p: " << p << endl;
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
}
