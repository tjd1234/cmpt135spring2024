// recursion_patterns.cpp

#include <iostream>

using namespace std;

// count with a while-loop
void count_down_while(int n)
{
    int i = 0;
    while (i < n)
    {
        cout << n - i << endl;
        i++;
    }
}

// count down with a for-loop
void count_down_for(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << n - i << endl;
    }
}

// count down with recursion
void count_down_recursive(int n)
{
    if (n > 0)
    {
        cout << n << endl;
        count_down_recursive(n - 1);
    }
}

int main()
{
    const int n = 1;

    cout << "count_down(" << n << ")" << endl;
    count_down_while(n);
    cout << endl;

    cout << "count_down_for(" << n << ")" << endl;
    count_down_for(n);
    cout << endl;

    cout << "count_down_recursive(" << n << ")" << endl;
    count_down_recursive(n);
}
