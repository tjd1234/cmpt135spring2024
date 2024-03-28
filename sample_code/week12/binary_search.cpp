// binary_search.cpp

#include <cassert>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

//
// Pre-condition:
//   v.size() >= 0
// Post-condition:
//   returns true if v is sorted in ascending order,
//   and false otherwise
//
bool is_sorted(const vector<string> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
        {
            return false;
        }
    }
    return true;
}

int binary_search(const vector<string> &v, const string &x)
{
    int begin = 0;
    int end = v.size();
    while (begin < end)
    {
        int mid = (begin + end) / 2;
        if (v[mid] == x)
        {
            return mid;
        }
        else if (v[mid] < x)
        {
            begin = mid + 1;
        }
        else // v[mid] > x
        {
            end = mid;
        }
    }
    return -1;
}

//
// Pre-condition:
//   v is ascending sorted order
//   v[0] <= v[1] <= ... <= v[v.size() - 1]
// Post-condition:
//   returns an index i such that v[i] == x; if x is
//   not in v, -1 is returned
//
int binary_search(const vector<string> &v, const string &x)
{
    int begin = 0;
    int end = v.size();
    while (begin < end)
    {
        int mid = (begin + end) / 2;
        if (v[mid] < x)
        {
            begin = mid + 1;
        }
        else if (x < v[mid])
        {
            end = mid;
        }
        else // v[mid] == x
        {
            return mid;
        }
    }
    return -1;
}

void binary_search_test()
{
    cout << "Calling binary_search_test() ... \n";
    vector<string> v;
    assert(binary_search(v, "a") == -1);

    v = {"moo"};
    assert(binary_search(v, "a") == -1);
    assert(binary_search(v, "moo") == 0);
    assert(binary_search(v, "z") == -1);

    v = {"bat", "moo"};
    assert(binary_search(v, "a") == -1);
    assert(binary_search(v, "bat") == 0);
    assert(binary_search(v, "cat") == -1);
    assert(binary_search(v, "moo") == 1);
    assert(binary_search(v, "z") == -1);

    v = {"bat", "moo", "zoo"};
    assert(binary_search(v, "a") == -1);
    assert(binary_search(v, "bat") == 0);
    assert(binary_search(v, "cat") == -1);
    assert(binary_search(v, "moo") == 1);
    assert(binary_search(v, "sip") == -1);
    assert(binary_search(v, "zoo") == 2);
    assert(binary_search(v, "zookeeper") == -1);

    cout << "... binary_search_test() done.\n";
}

//
// Pre-condition:
//   none
// Post-condition:
//   returns an index i such that v[i] == x; if x is
//   not in v, -1 is returned
//
int linear_search(const vector<string> &v, const string &x)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == x)
        {
            return i;
        }
    }
    return -1;
}

void linear_search_test()
{
    cout << "Calling linear_search_test() ... \n";
    vector<string> v;
    assert(linear_search(v, "a") == -1);

    v = {"moo"};
    assert(linear_search(v, "a") == -1);
    assert(linear_search(v, "moo") == 0);
    assert(linear_search(v, "z") == -1);

    v = {"bat", "moo"};
    assert(linear_search(v, "a") == -1);
    assert(linear_search(v, "bat") == 0);
    assert(linear_search(v, "cat") == -1);
    assert(linear_search(v, "moo") == 1);
    assert(linear_search(v, "z") == -1);

    v = {"bat", "moo", "zoo"};
    assert(linear_search(v, "a") == -1);
    assert(linear_search(v, "bat") == 0);
    assert(linear_search(v, "cat") == -1);
    assert(linear_search(v, "moo") == 1);
    assert(linear_search(v, "sip") == -1);
    assert(linear_search(v, "zoo") == 2);
    assert(linear_search(v, "zookeeper") == -1);

    cout << "... linear_search_test() done.\n";
}

string quote(const string &s)
{
    return "\"" + s + "\"";
}

vector<string> load_dictionary(const string &filename)
{
    ifstream infile(filename);
    vector<string> dict;
    string w;
    while (infile >> w)
    {
        dict.push_back(w);
    }
    const int n = dict.size();
    cout << n << " words loaded from " << filename << "\n";
    cout << "From " << quote(dict[0]) << " to " << quote(dict[n / 2]) << " to " << quote(dict[n - 1]) << "\n";
    return dict;
}

//
// Checking words with binary search ...
// Binary search: 0.017649s
//
// Checking words with linear search ...
// Linear search: 33.204s
//
// So binary search is about 1800 times faster than linear search.
//
void test_all()
{
    cout << "Calling linear and binary search on all words ...\n";
    vector<string> dictionary = load_dictionary("ospd.txt");
    clock_t start;
    clock_t end;

    // binary search
    cout << "\nChecking words with binary search ..." << endl;
    start = clock();
    for(const string& w : dictionary)
    {
        binary_search(dictionary, w);
    }
    end = clock();
    double binary_dur_in_sec = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Binary search: " << binary_dur_in_sec << "s" << endl;

    // linear search
    cout << "\nChecking words with linear search ..." << endl;
    start = clock();
    for(const string& w : dictionary)
    {
        linear_search(dictionary, w);
    }
    end = clock();
    double linear_dur_in_sec = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Linear search: " << linear_dur_in_sec << "s" << endl;
}

void interactive_test()
{
    vector<string> dictionary = load_dictionary("ospd.txt");

    // interactive command line
    clock_t start;
    clock_t end;
    cout << fixed << setprecision(6);
    for (;;)
    {
        // get word
        cout << "--> ";
        string word;
        cin >> word;

        // binary search
        start = clock();
        int binary_index = binary_search(dictionary, word);
        end = clock();
        double binary_dur_in_sec = (end - start) / (double)CLOCKS_PER_SEC;

        cout << "binary search: " << binary_dur_in_sec << "s at index " << binary_index << "\n";

        // linear search
        start = clock();
        int linear_index = linear_search(dictionary, word);
        end = clock();
        double linear_dur_in_sec = (end - start) / (double)CLOCKS_PER_SEC;

        cout << "linear search: " << linear_dur_in_sec << "s at index " << linear_index << "\n";
        cout << endl;
    } // for
} // interactive_test

int main()
{
    binary_search_test();
    linear_search_test();
    test_all();
    // interactive_test();
}
