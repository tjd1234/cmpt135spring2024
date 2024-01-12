// decisions.cpp

#include <iostream>

using namespace std;

int main()
{
    char d = 'm';

    if (d == 'm' || d == 'M')
    {
        cout << "Monday";
    }
    else if (d == 'w')
    {
        cout << "Wednesday";
    }
    else if (d == 'f')
    {
        cout << "Friday";
    }
    else
    {
        cout << "Invalid day: '" << d << "'";
    }

    cout << '\n';

    switch (d)
    {
    case 'm':
    case 'M':
        cout << "Monday";
        break;
    case 'w':
        cout << "Wednesday";
        break;
    case 'f':
        cout << "Friday";
        break;
    default:
        cout << "Invalid day: '" << d << "'";
        break;
    }
}
