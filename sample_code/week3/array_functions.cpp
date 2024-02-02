// array_functions.cpp

#include <cassert>
#include <iostream>

using namespace std;

//
// Returns a pointer to a new array of size n >= 0 on the free store, with all
// its elements initialized to fill
//
int *make_array(int n, int fill)
{
    //
    // First check that n is 0 or bigger.
    //
    assert(n >= 0);

    //
    // Allocate the array on the free store.
    //
    int *arr = new int[n];

    //
    // Set each element of the array to fill.
    //
    for (int i = 0; i < n; i++)
    {
        arr[i] = fill;
    }

    //
    // Return a copy of the pointer to the first element of the array.
    //
    return arr;
}

//
// Returns a pointer to a new array of n >= 0 elements on the free store, each
// initialized to 0.
//
// Note that this function is named "make_array", the same as the previous
// function. We say that the two functions are overloaded.
//
// C++ allows functions to have the same name when they have different
// parameters. That way C++ can always be sure which function you mean when you
// call it.
//
int *make_array(int n)
{
    return make_array(n, 0); // calls the previous make_array function
}

void make_array_test()
{
    cout << "Calling make_array_test ...\n";
    int *arr = make_array(1, 0);
    assert(arr[0] == 0);
    delete[] arr;

    arr = make_array(2, 1);
    assert(arr[0] == 1);
    assert(arr[1] == 1);
    delete[] arr;

    arr = make_array(3, 2);
    assert(arr[0] == 2);
    assert(arr[1] == 2);
    assert(arr[2] == 2);
    delete[] arr;

    cout << "... make_array_test done\n";
}

//
// Returns a pointer to a new array on the free store that's a copy of the array
// other. n is the size of other.
//
int *copy_array(int *other, int n)
{
    assert(n >= 0);
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = other[i];
    }
    return arr;
}

// Returns true if a and b have the same values in the same order, and false
// otherwise.
bool same_array(int *a, int m, int *b, int n)
{
    assert(m >= 0);
    assert(n >= 0);
    if (m != n)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

// a function that quotes a string
string quote(const string& s)
{
    return "\"" + s + "\"";
}

void copy_array_test()
{
    cout << "Calling copy_array_test ...\n";
    const int size = 4;
    int *arr1 = make_array(size, 9);
    int *arr2 = copy_array(arr1, size);

    assert(same_array(arr1, size, arr2, size));
    arr2[0] = -1;
    assert(!same_array(arr1, size, arr2, size));
    arr1[0] = -1;
    assert(same_array(arr1, size, arr2, size));

    delete[] arr1;
    delete[] arr2;

    cout << "... copy_array_test done\n";
}

//
// This function takes an array of ints as inputs and returns a pointer to a new
// array on the free store that is a copy of the input array, but with all the
// elements < 0 removed. For example, the input {-2, 6, 2, -1, 0, 4} returns a
// pointer to {6, 2, 0, 4}.
//
// The passed-in array is not change. The size of the new array is returned in
// the reference parameter n.
//
int *remove_negatives(int *arr, int size, int &result_size)
{
    // count the number of non-negative elements; this will be the size of the
    // new array
    result_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= 0)
        {
            result_size++;
        }
    }
    // at this point result_size has the correct size of the returned array

    // allocate a new array of the right size
    int *result = new int[result_size];

    // copy the non-negative elements into the new array
    int next_empty = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= 0)
        {
            result[next_empty] = arr[i];
            next_empty++;
        }
    }

    return result;
}

void remove_negatives_test()
{
    cout << "Calling remove_negatives_test ...\n";
    int arr[] = {-2, 6, 2, -1, 0, 4};
    int size = 6;
    int result_size = 0;
    int *result = remove_negatives(arr, size, result_size);
    assert(result_size == 4);
    assert(result[0] == 6);
    assert(result[1] == 2);
    assert(result[2] == 0);
    assert(result[3] == 4);

    delete[] result;
    cout << "... remove_negatives_test done\n";
}

int main()
{
    make_array_test();
    copy_array_test();
    remove_negatives_test();
}
