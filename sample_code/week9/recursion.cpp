// recursion.cpp

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// What happens when you call this function?
// It crashes the program with an "Address boundary error".
//
void f()
{
    f();
}

//
// What happens when you call this function?
//
// This prints "hello" thousands of times and then crashes the program with an
// "Address boundary error".
//
// Recall that every time a function is called some memory is pushed onto the
// C++ call stack. Each call to a() uses up some memory, and since the function
// never returns, the stack only grows bigger and bigger until the stack runs
// out of memory, causing stack overflow error.
//
// But there is a subtlety here! It is possible that its runs forever. If the
// compiler performs an optimization called "tail-call elimination", then it
// could re-write a() into a loop that runs forever.
//
// g++ will do tail-call elimination if you give it the optimization flag -O2.
// We can do this by adding it to CPPFLAGS in the makefile:
//
//     CPPFLAGS = -O2 -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g
//
// After re-compiling the program, calling a() now runs forever, or at least
// until "hello" is printed so many times that your computer runs out of memory.
// If you comment out the cout statement, then the program will keep running
// until you stop it.
//
// This is weird behaviour! Compilers optimizations are meant to make your
// program run faster *without* changing. But in this case that's not true: the
// tail-call elimination optimization changes the behaviour of the program.
//
// So be careful! Compiler optimizations can make your program run faster, but
// they can also change the behaviour of your program in subtle ways.
//
void a()
{
    cout << "hello\n";
    a();
}

//
// What does this variation of function a do?
//
// It prints "n hello" thousands of times and then crashes the program due to a
// stack overflow (assuming no tail call elimination). The value n get bigger
// for each cout statement.
//
void b(int n)
{
    cout << n << ": hello!\n";
    b(n + 1); // n + 1 here, not n
}

//
// Function b is interesting, but a crashes isn't very useful. How could we stop
// the function after print, say, 10 lines?
//
// We could add an if-statement to check the value of n. When n
//
void c(int n)
{
    if (n >= 10)
    {
        return; // all done: do nothing
    }
    else
    {
        cout << n << ": hello!\n";
        c(n + 1);
    }
}

//
// Function c is useful, but the 10 is hard-coded in the body of the function.
// It would be even more useful if we could pass-in as a parameter the number of
// times we want the line printed.
//
// Function d does just. The number n that is passed in is how many times we
// want cout called. To make this work we will count *down* from n instead of
// counting up like we did in function c.
//
// Intuitively, d implements the following recursive rule. To print the line n
// times, print the line once, and then print the line n-1 more times. The 1
// print plus the n-1 more prints adds up to n prints in total.
//
// Importantly, there is a special case that the rule doesn't work for. If n is
// 0 (or less), then we don't want to print the line at all. This special case
// is called a **base case**, and every useful recursive function has at least
// one base case. The base case tells the function when to stop. Without a base,
// the function will run forever (or until the stack overflows).
//
void d(int n)
{
    if (n <= 0) // base case
    {
        return; // all done: do nothing
    }
    else
    {
        cout << n << ": hello!\n";
        d(n - 1); // subtract 1 instead of add 1
    }
}

//
// We can make function d more readable by giving it a more descriptive name,
// and also by re-writing the if-statement. This does exactly the same thing as
// d, but is shorter, simpler, and a bit more readable.
//
void say_hello(int n)
{
    if (n > 0)
    {
        cout << n << ": hello!\n";
        say_hello(n - 1);
    }
}

//
// Now lets look just at the numbers that are being printed and re-write
// say_hello to just print numbers.
//
// count_down(int n) prints the numbers from n down to 1.
//
void count_down(int n)
{
    if (n > 0)
    {
        cout << n << "\n";
        count_down(n - 1);
    }
}

//
// count_down prints the numbers from n down to 1. What if instead we want to
// print the numbers from 1 up to n?
//
// The change needed to make the numbers from 1 up to n is surprisingly simple:
// just swap the order of the cout and the recursive call.
//
void count_up(int n)
{
    if (n > 0)
    {
        count_up(n - 1);
        cout << n << "\n";
    }
}

//
// count_down and count_up are important functions because they show a very
// common pattern for a recursive function. If you want a recursive function to
// do something n times, then the function will likely follow the same basic
// pattern as count_down or count_up.
//

int main()
{
    // f();
    // a();
    // b(0);
    // c(0);
    // d(5);
    // say_hello(5);
    // count_down(5);
    // count_up(5);
    count_up_down(5);
}
