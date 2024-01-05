// line_check.cpp

//
// Checks if any lines in a file are longer than a given length.
//
// Feature to Add
//
// When the program finds a long line it prints "line 15 is too long". Modify
// the program so that this message includes the length of the line, e.g. "line
// 15 is too long: 106 characters".
//

#include <iostream>

using namespace std;

int main()
{
    const int max_line_length = 100;

    int line_num = 1;
    int current_line_length = 0;
    int num_long_lines = 0;

    char c;
    while (cin.get(c))
    {
        if (c == '\n')
        {
            if (current_line_length > max_line_length)
            {
                cout << "Line " << line_num << " is too long.\n";
                num_long_lines++;
            }
            line_num++;
            current_line_length = 0;
        }
        else
        {
            current_line_length++;
        }
    } // while

    if (num_long_lines == 0)
    {
        cout << "No lines are too long.\n";
    }
} // main
