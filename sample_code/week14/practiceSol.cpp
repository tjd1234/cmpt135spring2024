// practiceSol.cpp

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

Write a non-recursive function named longestString that returns a longest string
in a given vector of strings. If there is a tie, return the rightmost string. If
the vector is empty throw a runtime_error exception. 

For example, longestString({"four", "five", "nine", "ten"}) should return
"nine".

*/

string longestString(const vector<string> &v)
{
    if (v.size() == 0)
    {
        throw runtime_error("empty vector");
    }
    string longest = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i].size() >= longest.size())
        {
            longest = v[i];
        }
    }
    return longest;
}

void test_longestString()
{
    cout << "Calling test_longestString()...\n";
    vector<string> fruit = {"apple", "banana", "orange", "kiwi", "grape"};
    assert(longestString(fruit) == "orange");

    fruit = {"apple", "banana", "orange", "kiwi", "grape", "mangos"};
    assert(longestString(fruit) == "mangos");

    fruit = {"apple", "strawberry", "banana", "orange", "kiwi", "grape", "mango"};
    assert(longestString(fruit) == "strawberry");

    cout << "... test_longestString() passed\n";
}

/*

Write a non-recursive function named longestStringRecursive that returns a
longest string in a given vector of strings. If there is a tie, return the
rightmost string. If the vector is empty throw a runtime_error exception. 

For example, longestStringRecursive({"four", "five", "nine", "ten"}) should
return "nine".

*/
string longestStringRecursive(const vector<string> &v, int begin)
{

    if (begin == v.size() - 1) // size 1 sub-vector
    {
        return v[begin];
    }
    string longest = longestStringRecursive(v, begin + 1);
    if (v[begin].size() > longest.size())
    {
        return v[begin];
    }
    return longest;
}

string longestStringRecursive(const vector<string> &v)
{
    if (v.size() == 0)
    {
        throw runtime_error("empty vector");
    }
    return longestStringRecursive(v, 0);
}

void test_longestStringRecursive()
{
    cout << "Calling test_longestStringRecursive()...\n";
    vector<string> fruit = {"apple", "banana", "orange", "kiwi", "grape"};
    assert(longestStringRecursive(fruit) == "orange");

    fruit = {"apple", "banana", "orange", "kiwi", "grape", "mangos"};
    assert(longestStringRecursive(fruit) == "mangos");

    fruit = {"apple", "strawberry", "banana", "orange", "kiwi", "grape", "mango"};
    assert(longestStringRecursive(fruit) == "strawberry");

    cout << "... test_longestStringRecursive() passed\n";
}

/*

Write a boolean function called hasDupPointer(int* arr, int n) that returns true
if two or more elements in the n-element array of int pointers point to the same
int (with the same address). Otherwise, return false. 

*/

bool hasDupPointer(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                return true;
            }
        }
    }
    return false;
}

void test_hasDupPointer()
{
    cout << "Calling test_hasDupPointer()...\n";
    int a = 1, b = 2, c = 3, d = 4;
    int *arr1[] = {&a, &b, &c, &d};
    assert(!hasDupPointer(arr1, 4));

    int *arr2[] = {&a, &b, &c, &a};
    assert(hasDupPointer(arr2, 4));

    int *arr3[] = {&a, &b, &c, &d, &a};
    assert(hasDupPointer(arr3, 5));

    cout << "... test_hasDupPointer() passed\n";
}

int main()
{
    test_longestString();
    test_longestStringRecursive();
    test_hasDupPointer();
}
