// double_list.cpp

#include "cmpt_error.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

struct double_list
{
    double *arr;  // pointer to the underlying array
    int capacity; // length of underlying array
    int size;     // # of elements from user's perspective
};

// Returns a new double_list of size 0 and capacity 10.
double_list make_empty_double_list()
{
    double_list result;
    result.capacity = 10;
    result.arr = new double[result.capacity];
    result.size = 0;
    return result;
}

// prints lst to cout
void print(double_list lst)
{
    cout << "\n";
    cout << "lst.capacity = " << lst.capacity << ", "
         << "lst.size = " << lst.size << "\n";
    for (int i = 0; i < lst.size; i++)
    {
        cout << "   lst.arr[" << i << "] = " << lst.arr[i] << "\n";
    }
}

// De-allocate the underlying array of lst.
void deallocate(double_list lst)
{
    delete[] lst.arr;
}

// Appends the number x to the right end of the array, increasing it's size by
// 1. If necessary, it will also double the capacity.
//
// IMPORTANT: lst must be passed by reference since lst.size (and maybe also
// lst.capacity) is changed.
//
// IMPORTANT: The line delete[] lst.arr fails if lst.capacity is 0. To prevent
// this, the make_double_empty_list must always sets the capacity to a value
// greater than 0.
void append_right(double_list &lst, double x)
{
    // double the capacity of array, if necessary
    if (lst.size >= lst.capacity)
    {
        lst.capacity = 2 * lst.capacity;            // make a new array
        double *arr_new = new double[lst.capacity]; // twice the size

        for (int i = 0; i < lst.size; i++)
        {                            // copy elements
            arr_new[i] = lst.arr[i]; // into new one
        }

        delete[] lst.arr;  // de-allocate the old array
        lst.arr = arr_new; // point to the new array
    }
    lst.arr[lst.size] = x;
    lst.size++;
}

// returns the sum of all elements in lst
double sum(double_list lst)
{
    double result = 0;
    for (int i = 0; i < lst.size; i++)
    {
        result += lst.arr[i];
    }
    return result;
}

// set all elements of lst to fill_value
void fill(double_list lst, int fill_value)
{
    for (int i = 0; i < lst.size; i++)
    {
        lst.arr[i] = fill_value;
    }
}

// std::sort is C++'s standard sorting function from the <algorithm> include.
// The input to std::sort is a pointer to the first element of the underlying
// array, and a pointer to one past the last element.
void sort_ascending(double_list lst)
{
    std::sort(lst.arr, lst.arr + lst.size);
}

int main()
{
    double_list lst = make_empty_double_list();

    // add some numbers
    append_right(lst, 6);
    append_right(lst, -1);
    append_right(lst, 2);

    // print their sum
    cout << "sum = " << sum(lst) << "\n";

    // sort from smallest to biggest
    print(lst);
    sort_ascending(lst);
    print(lst);

    // fill with 5's
    fill(lst, 5);
    print(lst);

    // add 100 more numbers
    for (int i = 0; i < 100; i++)
    {
        append_right(lst, i);
    }
    print(lst);

    // de-allocate the underlying array to avoid a memory leak
    deallocate(lst);
}
