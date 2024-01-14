// duplicate.cpp

//
// Code for the string duplication example.
//

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pair
{
    string input;
    string expected_output;
};

//
// table of sort test cases
//
const vector<Pair> test_cases = {
    {"cat", "catcat"},
    {"bird", "birdbird"},
    {"a house", "a housea house"},
    {"", ""}, // empty string
    {"a", "aa"},
    {"ab", "abab"},
    {"abc", "abcabc"},
    {"abab", "abababab"},
    {"ab ba", "ab baab ba"},
    {"abacaba", "abacabaabacaba"},
};

string quote(const string &s)
{
    return "\"" + s + "\"";
}

//
// Returns a new string consisting of s followed by s.
// E.g. f_correct("cat") returns "catcat"
//
string f_correct(const string &s)
{
    // return s + s;
    string result = s;
    for (char c : s)
    {
        result += c;
    }
    return result;
}

void test_f_correct()
{
    cout << "test_f_correct() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f_correct(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f_correct("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f_correct(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

//
// incorrect versions of f
//
string f1(const string &s)
{
    return s;
}

void test_f1()
{
    cout << "test_f1() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f1(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f1("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f1(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

string f2(const string &s)
{
    return s + s + s;
}

void test_f2()
{
    cout << "test_f2() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f2(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f2("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f2(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

string f3(const string &s)
{
    if (s == "cat")
    {
        return "catcat";
    }
    else if (s == "bird")
    {
        return "birdbird";
    }
    else
    {
        return "a housea house";
    }
}

void test_f3()
{
    cout << "test_f3() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f3(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f3("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f3(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

string f4(const string &s)
{
    if (s == "swordfish")
    {
        return "wrong!";
    }
    return s + s;
}

void test_f4()
{
    cout << "test_f4() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f4(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f4("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f4(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

//
// Incorrect when rand() returns 0. Since RAND_MAX = 2147483647 on my computer,
// this means it will return the the wrong value once in every 2 billion calls.
//
string f5(const string &s)
{
    if (rand() == 0)
    {
        return "wrong!";
    }
    return s + s;
}

void test_f5()
{
    cout << "test_f5() ...\n";
    //
    // do the tests
    //
    int fail_count = 0;
    for (Pair p : test_cases)
    {
        string result = f5(p.input);

        if (result != p.expected_output)
        {
            fail_count++;
            cout << "Test failed: f5("
                 << quote(p.input) << ")\n"
                 << "    actual: " << quote(result) << "\n "
                 << "  expected: " << quote(p.expected_output) << "\n";
        }
    }

    //
    // print the results of the tests
    //
    cout << "finished test_f5(): \n";
    cout << "   # failed: " << fail_count
         << "/" << test_cases.size() << "\n\n";
}

int main()
{
    // initialize random seed with current time
    srand(time(nullptr));
    cout << "RAND_MAX = " << RAND_MAX << "\n\n";

    // test_f_correct();
    // test_f1();
    // test_f2();
    // test_f3();
    // test_f4();
    test_f5();
}
