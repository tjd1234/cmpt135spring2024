// count_chars_start.cpp

//
// A "starter" file for the word count program. It shows how to read characters
// from cin.
//
// For example:
//
//   ❯ ./line_check_start
//   this is a test
//   this is a test
//
// This "echos" whatever user types, after they press return.
//
// To exit the program, type Ctrl-D (on Linux).
//
// You can pass a file to the program using the < operator, e.g.:
//
//    ❯ ./line_check_start < poem.txt
//    Computers that are smart?
//    I want no part.
//
//    Computers that are quantum?
//    I want'em!
//
// The < causes to the program to read from the file poem.txt instead of from
// the keyboard. This is useful trick to remember!
//

#include <iostream>

using namespace std;

int max_length_line = 100;

// int main()
int main(int argc, char *argv[])
{
    // cout << "argc: " << argc << endl; // number of arguments
    // cout << argv[0] << endl;          // program call
    if (argc == 1)
    {
        max_length_line = 100;
    }
    else if (argc == 2)
    {
        max_length_line = atoi(argv[1]);
    }
    else
    {
        cout << "Usage: " << argv[0] << " [max_length_line]" << endl;
        return 1;
    }

    cout << max_length_line << endl;

    int line_num = 1;
    int current_line_length = 0;
    char c;
    while (cin.get(c))
    {
        switch (c)
        {
        case '\n':
            if (current_line_length > max_length_line)
            {
                cout << "Line " << line_num << " is too long\n";
            }
            current_line_length = 0;
            line_num++;
            break;
        default:
            current_line_length++;
        }
        // if (c == '\n')
        // {
        //     if (current_line_length > max_length_line)
        //     {
        //         cout << "Line " << line_num << " is too long\n";
        //     }
        //     current_line_length = 0;
        //     line_num++;
        // }
        // else
        // {
        //     current_line_length++;
        // }
    } // while

} // main
