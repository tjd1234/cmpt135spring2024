// all_even.cpp

#include <iostream>
#include <vector>

using namespace std;

//
// Pre-condition:
//     begin >= 0
//     all ints in v are >= 0
// Post-condition:
//     Returns true if v[begin], v[begin+1], ... v[n-1] are all even,
//     where n is the size of v; false otherwise.
//
bool all_even(const vector<int> &v, int begin)
{
    if (begin == v.size())
    {
        return true;
    }
    else // v.size() > 0
    {
        return (v[begin] % 2 == 0)  // v[begin] is even
             && all_even(v, begin + 1);

        // if (v[begin] % 2 != 0)
        // {
        //     return false;
        // }
        // else // v[begin] is even
        // {
        //     return all_even(v, begin + 1);
        // }
    }
}

//
// Pre-condition:
//     all ints in v are >= 0
// Post-condition:
//     Returns true if all elements of v are even; false otherwise.
//
bool all_even(const vector<int> &v)
{
    return all_even(v, 0);
}

int main()
{
    vector<int> v = {2, 8, 6, 8};
    cout << "all_even(v) = " << all_even(v) << "\n"; // 1

    vector<int> w = {2, 8, 7, 8};
    cout << "all_even(w) = " << all_even(w) << "\n"; // 0
}
