// exceptions.cpp

#include <iostream>

using namespace std;

void example1()
{
    cout << "Hello!\n";

    throw "Oh no, an error has occurred!";

    cout << "Goodbye!\n";
}

void example2()
{
    cout << "Hello!\n";

    throw runtime_error("Oh no, an error has occurred!");

    cout << "Goodbye!\n";
}

void example3()
{
    int *arr = new int[10];

    throw runtime_error("Oh no, an error has occurred!");

    delete[] arr;
}

struct my_array
{
    int *arr;
    my_array(int size)
    {
        arr = new int[size];
    }

    ~my_array()
    {
        delete[] arr;
    }
};

void example4()
{
    my_array arr(10);

    throw runtime_error("Oh no, an error has occurred!");
}

void example5()
{
    my_array arr(10);

    exit(-1); // stop the program and return error code -1
}

// returns 1/x, and throws a runtime_error if x is 0
double invert(double x)
{
    if (x == 0)
    {
        throw runtime_error("Cannot invert 0");
    }

    return 1 / x;
}

void invert_test()
{
    for (;;) // loop forever
    {
        cout << "Enter a number: ";
        double x;
        cin >> x;

        try
        {
            double result = invert(x);
            cout << "The inverse of " << x << " is " << result << "\n\n";
        }
        catch (const runtime_error &e)
        {
            cout << "Error: can't invert 0\n\n";
        }
    }
}

int main()
{
    invert_test();
}
