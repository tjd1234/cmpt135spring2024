// driver.cpp

//
// Example of an interactive test driver for testing code.
//

#include <iostream>

using namespace std;

string f(const string &s)
{
    // return s + s;
    string result = s;
    for (char c : s)
    {
        result += c;
    }
    return result;
}

string quote(const string &s)
{
    return "\"" + s + "\"";
}

// return a copy of s with trailing and leading spaces removed
string strip(const string &s)
{
    int begin = 0;
    while (begin < s.size() && s[begin] == ' ')
    {
        begin++;
    }
    int end = s.size() - 1;
    while (end >= 0 && s[end] == ' ')
    {
        end--;
    }
    // s.substr(start_index, length)
    return s.substr(begin, end - begin + 1);
}

int main()
{
    for (;;)
    {
        cout << "--> ";
        string input;
        getline(cin, input);
        string result = strip(input);
        cout << "  strip(\"" << input << "\") = \""
             << result << "\"\n";
    }
}