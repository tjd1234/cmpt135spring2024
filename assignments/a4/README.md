## Assignment 4: Recursion

![Sierpinski Triangle](250px-Sierpinski_triangle.svg.png "Sierpinski triangle")

> I don't understand recursion.
>
> -- Anonymous student
>
> To understand recursion, you must first understand recursion.
>
> -- Anonymous teacher 1
>
> No, that's just an infinite loop. To understand recursion you must first
> understand something that is just like recursion, but smaller. 
> 
> -- Anonymous teacher 2
>
> I understand recursion even less now.
>
> -- Anonymous student


A good way to learn recursion is to practice writing recursive functions. In the
comments of [a4.h](a4.h) are a series of questions, each of which asks you to
write two functions: an **answer function** that answers the question, and a
**test function** that checks the correctness of your answer function. Write
both functions for each question.

Put your answer and test functions in [a4.cpp](a4.cpp), and use
[a4_main.cpp](a4_main.cpp) to call the test functions. When you're done, you'll
submit only [a4.cpp](a4.cpp).

You will need to compile [a4.cpp](a4.cpp) and [a4_main.cpp](a4_main.cpp)
separately, and then link their `.o` files into an executable for running the
tests. A special-purpose [makefile](makefile) is provided to simplify the
compiling and linking. Read the comments at the top of [the makefile](makefile)
to see how to use it.

### Pre-conditions and Post-conditions

The functions are specified using *pre-conditions*, *post-conditions*, and
*constraints*. For example:

```cpp
//
// Pre-condition:
//    n >= 0
// Post-condition:
//    Returns the sum of the first n integers, i.e. 1 + 2 + 3 + ... + n.
//    If n is 0, then 0 is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write
//    helper functions if necessary.
// Note:
//    You don't need to handle sums that overflow int.
//
int sum(int n);
```

The **pre-condition** states what must be true *before* the function is called,
and the **post-condition** states what must be true *after* the function returns
correctly (assuming that the pre-condition was true before the function was
called).

**Constraints** lists anything else that is required for the function to be
considered correct.

If a function's pre-condition is *false* when the function is called, then that
means it's being called with bad input, and so you have a bug somewhere earlier
in your code.

> **Hint** Put an `assert` at the start of a function to check if its
> pre-condition is true.


## Testing

For each question write a corresponding **test function** that *automatically*
tests the answer function. For example, the test function for `sum` could be
this:

```cpp
#include <cassert>

// ...

void sum_test() 
{
  cout << "sum_test() called ... ";
  assert(sum(0) == 0);
  assert(sum(1) == 1);
  assert(sum(2) == 1 + 2);
  assert(sum(3) == 1 + 2 + 3);
  assert(sum(4) == 1 + 2 + 3 + 4);
  cout << "sum_test() done: all tests passed\n";
}
```

In some cases, you might prefer to use an if-statement rather than `assert`.
For instance, `assert(sum(2) == 1 + 2)` could be written like this:

```cpp
if (sum(2) != 1 + 2) 
{
  cmpt::error("test failed");
}
```

However you write your tests, make sure they thoroughly test your function and
are checked *automatically*.

> **Hint** Write some test cases *first* before writing any code. Not only will
> this give you test cases to check your code with, but it will also help you
> understand the problem better. Writing test cases first is key part of
> [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development),
> a popular programming style.

## General Implementation Constraints

- **No loops are permitted** in any of the code you write for this assignment
  (not even in the test functions or helper functions). If your code for a
  question uses a loop then you will get 0 for that question.

- You **can** write helper functions if you like. You write them yourself and
  they can't use loops.

- **Do not** use any global variables, static local variables, or other such
  tricks when implementing your functions. Just use functions, parameters, and
  return values in the style shown in the notes and in lectures.

- Use **exactly** the function names and parameters given in [a4.h](a4.h).
  **Don't change them in any way**.

- **Do not** #include any files other than those that are already in
  [a4.h](a4.h).


## Submitting Your Work

On Canvas, please submit *just* the file[a4.cpp](a4.cpp) with your answers in
it. Don't submit anything else.

The marker will use [the assignment makefile](makefile) to compile your
[a4.cpp](a4.cpp) and link it with their own `main()` function for testing. A
copy of [a4.h](a4.h), and [cmpt_error.h](cmpt_error.h) will be in the same
folder as your program when it runs.


## Basic Requirements

Before we give your program any marks, it must compile on Ubuntu Linux using the
[makefile](makefile) in this assignment. Just type `make`:

```bash
❯ make
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g  -c -o a4.o a4.cpp
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g  -c -o a4_main.o a4_main.cpp
g++ -o a4_main_test a4.o a4_main.o

> ./a4_main_test
...
```

[makefile](makefile) is customized for this assignment: it's *not* the usual
course makefile. Notice also that the name of the executable it builds is
`a4_main_test`. See the comments at the top of [makefile](makefile) for other
ways to use it.


## Marking Scheme

### Overall source code readability: 5 marks

- All code is sensibly and consistently indented, and all lines are 100
  characters in length, or less.
- Whitespace is used to group related pieces of a code to make it easier for
  humans to read. All whitespace has a purpose.
- Variable and function names are self-descriptive.
- Appropriate features of C++ are used, as discussed in class and in the notes.
  **Note** If you use a feature that we haven't discussed in class, **you must
  explain it in a comment**, even if you think it's obvious.
- Comments are used when needed to explain chunks of code whose purpose is not
  obvious from the code itself. There should be *no* commented-out code from
  previous versions.

### Source code correctness: 20 marks

- **1 mark** for correctly and efficiently implementing each solver function.
- **1 mark** for thoroughly testing each requested recursive function with its
  own test function.

### Deductions

- **-1 mark** (at least) if your file does not have the correct name, or you
  submit it in the incorrect format.
- up to **-3 marks** if you do not include your full name, email, and SFU ID in
  the header of your file.
- **A score of 0** if one or more of the following are true:
  - You *don't* include the "Statement of Originality", or it is modified in any
    way.
  - You use code from some other source (e.g. the web, the textbook, ChatGPT, a
    friend, a teacher, a TA...) *without* citing the source.
  - You submit a "wrong" non-working file, and then *after the due date* submit
    the "right" file. If you can provide evidence that you finished the
    assignment on time, then it may be marked.
- **-5 marks** for any *memory leaks*, or other errors, reported by `valgrind`.
  `valgrind` is run like this:

  ```console
  > valgrind ./some_prog
    
  // ... lots of output ... 
  ```

  A program is considered to have **no memory leaks** if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and
    `possibly lost` are all 0.
  - `ERROR SUMMARY` reports 0 errors.
  
  If `valgrind` reports any errors for a run of your program, your assignment
  will get a deduction as described below.

  **Note** It *may* be okay if **still reachable** reports a non-zero number of
  bytes. It usually means that some memory was not de-allocated when your
  program finished. That could be because you forgot to de-allocate the memory,
  or, it *might* be that the compiler optimized-away de-allocation statements in
  cases where it knows the program will immediately end (the operating system
  will clean up any memory a finished program hasn't de-allocated). **Rule of
  thumb**: assume that **still reachable** means you have forgotten a delete
  statement somewhere. Carefully check that you haven't left out any delete
  statements before concluding that it is due to a compiler optimization.
  
There may be other deductions, depending upon the circumstances.
