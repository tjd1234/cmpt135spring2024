// bad_sorts.cpp

//
// Examples of incorrect sorting functions.
//

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct Pair
{
    vector<int> input;
    vector<int> expected_output;
};

//
// table of sort test cases
//
const vector<Pair> test_cases = {
    {{}, {}},               // empty
    {{1}, {1}},             // single-element
    {{1, 2}, {1, 2}},       // small already-sorted
    {{2, 1}, {1, 2}},       // small not sorted (reversed)
    {{2, 2}, {2, 2}},       // small all same
    {{1, 2, 3}, {1, 2, 3}}, // all permutations of three different
    {{1, 3, 2}, {1, 2, 3}}, //
    {{2, 1, 3}, {1, 2, 3}}, //
    {{2, 3, 1}, {1, 2, 3}}, //
    {{3, 1, 2}, {1, 2, 3}}, //
    {{3, 2, 1}, {1, 2, 3}}, //
    {{1, 1, 2}, {1, 1, 2}}, // all permutations of three with a repeat
    {{1, 2, 1}, {1, 1, 2}}, //
    {{2, 1, 1}, {1, 1, 2}}, //
    {{1, 1, 1}, {1, 1, 1}}, // three all same
};

//
// operator<< overload for vectors to make printing with cout easier
//
ostream &operator<<(ostream &os, const vector<int> &v)
{
    os << "{";
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i < v.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

//
// insertion sort suggested by VS Code Co-Pilot
//
void copilot_insertion_sort(vector<int> &v)
{
    for (int i = 1; i < v.size(); ++i)
    {
        int j = i;
        while (j > 0 && v[j] < v[j - 1])
        {
            swap(v[j], v[j - 1]);
            --j;
        }
    }
}

void test_copilot_insertion_sort()
{
    cout << "test_copilot_insertion_sort() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        // the sort modifies p.input, so save a copy
        vector<int> original_input = p.input;

        copilot_insertion_sort(p.input);

        if (p.input != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: copilot_insertion_sort("
                 << original_input << ")\n"
                 << "  expected: " << p.expected_output << "\n"
                 << "    actual: " << p.input << "\n ";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_copilot_insertion_sort(): \n";
    cout << "   # failed: " << fail_count << "\n";
}

//
// selection sort
//
void copilot_selection_sort(vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; ++i)
    {
        int min_index = i;
        for (int j = i + 1; j < v.size(); ++j)
        {
            if (v[j] < v[min_index])
            {
                min_index = j;
            }
        }
        swap(v[i], v[min_index]);
    }
}

void test_copilot_selection_sort()
{
    cout << "test_copilot_selection_sort() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        // the sort modifies p.input, so save a copy
        vector<int> original_input = p.input;

        copilot_insertion_sort(p.input);

        if (p.input != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: copilot_insertion_sort("
                 << original_input << ")\n"
                 << "  expected: " << p.expected_output << "\n"
                 << "    actual: " << p.input << "\n ";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_copilot_selection_sort(): \n";
    cout << "   # failed: " << fail_count << "\n";
}

int main()
{
    test_copilot_insertion_sort();
    test_copilot_selection_sort();
}
