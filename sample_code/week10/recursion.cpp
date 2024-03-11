// recursion.cpp

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// 523556

// void f(int n)
// {
//     if (n <= 5)
//     {
//         cout << n << ": hello!\n";
//         f(n + 1);
//     }
// }

// print nothing
// 1 2 1 2 1
// 1 2 1 3 1 2 1
// 1 2 1 3 2 1 2 1 1
void g(int n)
{
    if (n > 0)
    {
        cout << n << ": hello!\n";
        g(n - 1); 
    }
}

long int f(long int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return f(n-1) + f(n-2);
}

int main()
{
    for(int i = 0; i < 50; i++) {
        cout << "f(" << i << ") = "<< f(i) << endl;
    }
}
