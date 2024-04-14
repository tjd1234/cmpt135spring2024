// recursion_trace.cpp

#include <iostream>

using namespace std;

/*


*/

//
// Singly-recursive function that prints numbers from n to 1.
//
// E.g. f(5) prints 5 4 3 2 1
//
void f(int n)
{
    if (n > 0)            // line 1
    {
        cout << n << " "; // line 2
        f(n - 1);         // line 3
                          // line 4
    }
}

//
// Doubly recursive function that prints numbers in a strange pattern.
//
// E.g. g(3) prints 3 2 1 1 2 1 1
//
void g(int n)
{
    if (n > 0)             // line 1
    {
        cout << n << " ";  // line 2
        g(n - 1);          // line 3
        g(n - 1);          // line 4
                           // line 5
    }
}

int main()
{
    // f(5);
    g(3);
}
