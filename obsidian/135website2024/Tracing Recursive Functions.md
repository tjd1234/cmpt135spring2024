Tracing recursive functions can be tricky, especially when there is more than one recursive call. Here we will go over a couple of practical examples of how to trace recursive functions.
## A Singly-Recursive Function
Suppose we want to trace this function:

```cpp
void f(int n)
{
    if (n > 0)             // line 1
    {
        cout << n << " ";  // line 2
        f(n - 1);          // line 3
                           // line 4
    }
}
```
It prints numbers from `n` to `1`. For example, `f(5)` prints `5 4 3 2 1`.

Let's trace the function call `f(5)` step-by step. We will use the **call stack** to keep track of the function calls. Recall that when a function is called, the function call is *pushed* on top of the call stack (and when it returns it will be *popped* from the top of the call stack). For example, when `f(5)` is called, the call stack looks like this:
```
f(5), done            Output: nothing yet
____________________
bottom of call stack
```
At least two things are pushed when a function is call: the function call itself, including any parameters, and also where the program should continue from when the function returns. In this case, since `f(5)` is the first call there is nothing to do after it returns: the call stack is empty after and the program is done.

After `f(5)` is called, the function prints `5` and then calls `f(4)`. The call stack now looks like this:
```
f(4), line 4 in f(5)
f(5), done             Output: 5
____________________
bottom of call stack
```
`f(4)` is on the top of the call stack because it's the most recently called function. `f(5)` is underneath, which means that `f(4)` was called from within `f(5)`. When `f(4)` returns, the program will continue from line 4 of `f(5)`.

When `f(4)` is called, the function prints `4` and then calls `f(3)`, making the call stack look like this:
```
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4
____________________
bottom of call stack
```
`f(3)` is on the top of the call stack because it's the most recently called unction. `f(4)` and `f(3)` are still active, sitting on the call stack waiting for the function calls above it to return. When `f(3)` returns, the program will continue from line 4 of `f(4)`.

From looking at the call stack we can see that `f(3)` was called from within `f(4)`, and `f(4)` was called from within `f(5)`.

When `f(3)` is called, the function prints `3` and then calls `f(2)`, making the call stack look like this:
```
f(2), line 4 in f(3)
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3
____________________
bottom of call stack
```
The function calls `f(3)`, `f(4)`, and `f(5)` are still active, waiting for the functions above them to return.

When `f(2)` is called, it prints `2` and then calls `f(1)`, making the call stack look like this:
```
f(1), line 4 in f(2)
f(2), line 4 in f(3)
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2
____________________
bottom of call stack
```
Again, `f(1)` is on the top of the call stack because it's the most recently called function. It prints `1` and then calls `f(0)`, making the call stack look this:
```
f(0), line 4 in f(1)
f(1), line 4 in f(2)
f(2), line 4 in f(3)
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Take a moment to examine the call stack. At this point it contains six different function calls, `f(5)` to `f(0)`. The first function that was called, `f(5)`, is on the bottom, the next function that was called, `f(4)`, is on top of that, and so on up to `f(0)`, which is the most recently called function.

Notice that all the output is now printed. From the user point of view the program is done. But the program is not done yet: it still needs to return from all the function calls. Recall that when a function call returns, we say that it is **popped** from the call stack.

When `f(0)` is called, it does not print anything and then returns. 

We can also see one of the issues with recursion: it can use a lot of memory. The function call `f(n)` will need to store `n + 1` function calls on the stack. This takes extra time and memory, usually slowing down the performance of your program.

The call `f(0)` does not print anything: it just returns, because the if-statement skips the print statement and recursive call. So `f(0)` returns without doing anything, and the call stack looks like this:
```
f(1), line 4 in f(2)
f(2), line 4 in f(3)
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Next, we continuing running in `f(1)`, but starting at line 4, which was the line that `f(0)` indicated. Line 4 is the end of the function, so `f(1)` returns without doing anything else:
```
f(2), line 4 in f(3)
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Next, we continue running in `f(2)`, but starting at line 4, the line that `f(1)` indicated. Line 4 is the end of the function, so `f(2)` returns without doing anything else:
```
f(3), line 4 in f(4)
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Next, we continue running in `f(3)`, but starting at line 4, the line that `f(2)` indicated. Line 4 is the end of the function, so `f(3)` returns without doing anything else:
```
f(4), line 4 in f(5)
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Next, we continue running in `f(4)`, but starting at line 4, the line that `f(3)` indicated. Line 4 is the end of the function, so `f(4)` returns without doing anything else:
```
f(5), done             Output: 5 4 3 2 1
____________________
bottom of call stack
```
Finally there is only one function call on the stack, `f(5)`. We continue running in `f(5)`, but starting at line 4, the line that `f(4)` indicated. Line 4 is the end of the function, so `f(5)` returns without doing anything else:

```
    empty stack       Output: 5 4 3 2 1
____________________
bottom of call stack
```
Now the call stack is empty, and the program is done, with the correct output having been printed to the screen.

**Exercise**. Trace `f(5)` again, but first swap line 2 and line 3 so that recursive call comes *before* the `cout` statement.
## A Doubly-Recursive Function with a Recursion Tree
A double-recursive function is a function that has two recursive calls. For example:
```cpp
void g(int n)
{
    if (n > 0)             // line 1
    {
        cout << n << " ";  // line 2
        g(n - 1);          // line 3
        g(n - 1);          // line 4
                           // line 5
    }
}
```
While it is certainly possible to trace `g(n)` as we did in the previous example by writing out the calls to the call stack (C++ does it!), it is much trickier to keep track of all the details.

So instead we will trace `g(3)` using a **recursion tree**. A recursion tree is a kind of a **call graph** that visual which function calls call which functions. You can use call graphs in any program, but they are particularly useful for tracing recursive functions.

[This PDF contains a step-by-step guide to tracing `g(3)` using a recursion  tree](recursionTrace.PDF) (and also [the original PowerPoint file](https://github.com/tjd1234/cmpt135spring2024/blob/main/sample_code/week9/recursionTrace.pptx)). At least once, go through the slides carefully, and check your understanding at each step.
