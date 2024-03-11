// sumvec.cpp

#include <iostream>
#include <vector>

using namespace std;

//
// Recursion on vectors
//

//
// Pre-condition:
//    0 <= begin <= v.size()
// Post-condition:
//    returns v[begin] + v[begin + 1] + ... + v[v.size() - 1]
//
int sum(const vector<int> &v, int begin)
{
    if (begin == v.size())
    {
        return 0;
    }
    else
    {
        return v[begin] + sum(v, begin + 1);
    }
}

//
// Pre-condition:
//    none
// Post-condition:
//    returns the sum of the elements of v
//
int sum(const vector<int> &v)
{
    return sum(v, 0);
}

int main()
{
    vector<int> v = {2, 1, 7};
    cout << "sum(v) = " << sum(v) << "\n"; // 10
}
