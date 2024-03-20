// insertion_sort.cpp

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//
// insertion_sort(v) works by maintaining a sorted part of the vector at the
// front of v. Everything before the current position i is in sorted order. The
// algorithm works by moving v[i] backwards through the sort part of the vector
// until it finds the correct location for it. Elements are shifted up as it
// goes.
//

void insertion_sort(vector<string> &v)
{
    for (int i = 1; i < v.size(); ++i)
    {
        // key is the value we are going to insert
        // into the sorted part of v
        string key = v[i];

        // j points to one position before the
        // (possible) insertion point of the key;
        // thus, key will eventually be inserted at
        // v[j + 1]
        int j = i - 1;

        //
        // This loop determines where to insert the key
        // into the sorted part of v. It does this by
        // searching backwards through the sorted part
        // for the first value that is less than, or equal
        // to, key.
        //
        // This loop combines searching with element
        // shifting. Every time an element bigger than the
        // key is found, it is moved up one position.
        //
        // It's possible that there is no value in the
        // sorted part that is smaller than key, in which
        // case key gets inserted at the very start of v.
        // This is a special case that is handled by j >= 0
        // in the loop condition.
        //
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        // After loop ends this is true:
        // (j < 0 || v[j] <= key)

        v[j + 1] = key; // j points to the location
                        // *before* the one where key
                        // will be inserted
    }                   // for

} // insertion_sort

void test_insertion_sort()
{
    cout << "Calling test_insertion_sort ...\n";
    vector<string> v;
    insertion_sort(v);
    assert(v == vector<string>());

    v = {"cat"};
    vector<string> result = {"cat"};
    insertion_sort(v);
    assert(v == result);

    v = {"cat", "dog"};
    result = {"cat", "dog"};
    insertion_sort(v);
    assert(v == result);

    v = {"dog", "cat"};
    result = {"cat", "dog"};
    insertion_sort(v);
    assert(v == result);

    v = {"cat", "dog", "elephant"};
    result = {"cat", "dog", "elephant"};
    insertion_sort(v);
    assert(v == result);

    v = {"dog", "cat", "elephant", "owl", "bat", "bird"};
    result = {"bat", "bird", "cat", "dog", "elephant", "owl"};
    insertion_sort(v);
    assert(v == result);

    cout << " ... test_insertion_sort done: all tests passed\n";
}

void interactive_test()
{
    // read in the words from cin
    vector<string> words;
    string w;
    while (cin >> w)
    {
        words.push_back(w);
    }

    // re-arrange them into sorted order
    insertion_sort(words);
    // std::sort(begin(words), end(words)); // standard C++ sort for comparison

    // write them to cout
    for (string w : words)
    {
        cout << w << "\n";
    }
}

int main()
{
    // test_insertion_sort();
    interactive_test();
}

//
// Takes ~27s on my desktop computer to sort ospd_shuffled.txt using
// insertion_sort.
//
