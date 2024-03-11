// fib.cpp

#include <iostream>
#include <vector>

using namespace std;

// Returns the nth Fibonacci number (assuming n > 0). Uses recursion.
// Simple, but sloooooow because of all the repeated calls to fib.
int fib(int n)
{
    if (n == 1) // base case
    {
        return 1;
    }
    else if (n == 2) // base case
    {
        return 1;
    }
    else // recursive case
    {
        return fib(n - 1) + fib(n - 2);
    }
}

// Returns the nth Fibonacci number (assuming n > 0). Doesn't use recursion.
// Much faster, but more complicated.
int fib2(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        int a = 1;
        int b = 1;
        int c = 0;
        for (int i = 2; i < n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}

// Calculates how many times the fib function is called for a given n.
long num_calls(int n)
{
    if (n == 1 || n == 2)
    {
        return 0;
    }

    return 2 + num_calls(n - 1) + num_calls(n - 2);
}

int main()
{
    for (int n = 1; n <= 50; ++n)
    {
        // flush makes the output appear immediately
        // cout << "non-recursive fib(" << n << ") = " << flush
        //      << fib2(n) << "\n";
        
        // cout << "    recursive fib(" << n << ") = " << flush
        //      << fib(n) << "\n";
        
        cout << " num_calls(" << n << ") = " << flush
             << num_calls(n) << "\n";
    }
}






/*
❯ time ./fib
    recursive fib(1) = 1
    recursive fib(2) = 1
    recursive fib(3) = 2
    recursive fib(4) = 3
    recursive fib(5) = 5
    recursive fib(6) = 8
    recursive fib(7) = 13
    recursive fib(8) = 21
    recursive fib(9) = 34
    recursive fib(10) = 55
    recursive fib(11) = 89
    recursive fib(12) = 144
    recursive fib(13) = 233
    recursive fib(14) = 377
    recursive fib(15) = 610
    recursive fib(16) = 987
    recursive fib(17) = 1597
    recursive fib(18) = 2584
    recursive fib(19) = 4181
    recursive fib(20) = 6765
    recursive fib(21) = 10946
    recursive fib(22) = 17711
    recursive fib(23) = 28657
    recursive fib(24) = 46368
    recursive fib(25) = 75025
    recursive fib(26) = 121393
    recursive fib(27) = 196418
    recursive fib(28) = 317811
    recursive fib(29) = 514229
    recursive fib(30) = 832040
    recursive fib(31) = 1346269
    recursive fib(32) = 2178309
    recursive fib(33) = 3524578
    recursive fib(34) = 5702887
    recursive fib(35) = 9227465
    recursive fib(36) = 14930352
    recursive fib(37) = 24157817
    recursive fib(38) = 39088169
    recursive fib(39) = 63245986
    recursive fib(40) = 102334155
    recursive fib(41) = 165580141
    recursive fib(42) = 267914296
    recursive fib(43) = 433494437
    recursive fib(44) = 701408733
    recursive fib(45) = 1134903170
    recursive fib(46) = 1836311903
    recursive fib(47) = -1323752223
    recursive fib(48) = 512559680
    recursive fib(49) = -811192543
    recursive fib(50) = -298632863

________________________________________________________
Executed in  120.09 secs   fish           external
   usr time  120.08 secs  166.00 micros  120.08 secs
   sys time    0.00 secs  315.00 micros    0.00 secs
*/

/*

❯ time ./fib
non-recursive fib(1) = 1
non-recursive fib(2) = 1
non-recursive fib(3) = 2
non-recursive fib(4) = 3
non-recursive fib(5) = 5
non-recursive fib(6) = 8
non-recursive fib(7) = 13
non-recursive fib(8) = 21
non-recursive fib(9) = 34
non-recursive fib(10) = 55
non-recursive fib(11) = 89
non-recursive fib(12) = 144
non-recursive fib(13) = 233
non-recursive fib(14) = 377
non-recursive fib(15) = 610
non-recursive fib(16) = 987
non-recursive fib(17) = 1597
non-recursive fib(18) = 2584
non-recursive fib(19) = 4181
non-recursive fib(20) = 6765
non-recursive fib(21) = 10946
non-recursive fib(22) = 17711
non-recursive fib(23) = 28657
non-recursive fib(24) = 46368
non-recursive fib(25) = 75025
non-recursive fib(26) = 121393
non-recursive fib(27) = 196418
non-recursive fib(28) = 317811
non-recursive fib(29) = 514229
non-recursive fib(30) = 832040
non-recursive fib(31) = 1346269
non-recursive fib(32) = 2178309
non-recursive fib(33) = 3524578
non-recursive fib(34) = 5702887
non-recursive fib(35) = 9227465
non-recursive fib(36) = 14930352
non-recursive fib(37) = 24157817
non-recursive fib(38) = 39088169
non-recursive fib(39) = 63245986
non-recursive fib(40) = 102334155
non-recursive fib(41) = 165580141
non-recursive fib(42) = 267914296
non-recursive fib(43) = 433494437
non-recursive fib(44) = 701408733
non-recursive fib(45) = 1134903170
non-recursive fib(46) = 1836311903
non-recursive fib(47) = -1323752223
non-recursive fib(48) = 512559680
non-recursive fib(49) = -811192543
non-recursive fib(50) = -298632863

________________________________________________________
Executed in    9.47 millis    fish           external
   usr time    4.05 millis  130.00 micros    3.92 millis
   sys time    0.15 millis  152.00 micros    0.00 millis

*/

/*

❯ time ./fib
 num_calls(1) = 0
 num_calls(2) = 0
 num_calls(3) = 2
 num_calls(4) = 4
 num_calls(5) = 8
 num_calls(6) = 14
 num_calls(7) = 24
 num_calls(8) = 40
 num_calls(9) = 66
 num_calls(10) = 108
 num_calls(11) = 176
 num_calls(12) = 286
 num_calls(13) = 464
 num_calls(14) = 752
 num_calls(15) = 1218
 num_calls(16) = 1972
 num_calls(17) = 3192
 num_calls(18) = 5166
 num_calls(19) = 8360
 num_calls(20) = 13528
 num_calls(21) = 21890
 num_calls(22) = 35420
 num_calls(23) = 57312
 num_calls(24) = 92734
 num_calls(25) = 150048
 num_calls(26) = 242784
 num_calls(27) = 392834
 num_calls(28) = 635620
 num_calls(29) = 1028456
 num_calls(30) = 1664078
 num_calls(31) = 2692536
 num_calls(32) = 4356616
 num_calls(33) = 7049154
 num_calls(34) = 11405772
 num_calls(35) = 18454928
 num_calls(36) = 29860702
 num_calls(37) = 48315632
 num_calls(38) = 78176336
 num_calls(39) = 126491970
 num_calls(40) = 204668308
 num_calls(41) = 331160280
 num_calls(42) = 535828590
 num_calls(43) = 866988872
 num_calls(44) = 1402817464
 num_calls(45) = 2269806338
 num_calls(46) = 3672623804
 num_calls(47) = 5942430144
 num_calls(48) = 9615053950
 num_calls(49) = 15557484096
 num_calls(50) = 25172538048

________________________________________________________
Executed in  117.33 secs   fish           external 
   usr time  117.32 secs  139.00 micros  117.32 secs 
   sys time    0.01 secs  285.00 micros    0.01 secs 

*/
