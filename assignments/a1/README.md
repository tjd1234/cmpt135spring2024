# Assignment 1: Basic C++ Features

Lets get re-acquainted with basic C++ programming. We'll do that by implementing
some useful command-line utilities.

## Getting Started

For this assignment, please put all your `.cpp` files into a folder named `a1`.
Make sure to compile your programs using the [makefile](makefile) in the folder
--- that's the how the markers will compile your program, and you will lose
marks if it does not compile with [makefile](makefile)!

## Question 1

Compile the file [line_check.cpp](line_check.cpp) using the [makefile](makefile)
like this:

```
> make line_check
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   line_check.cpp   -o line_check
```

When you run it on [sample_lines.txt](sample_lines.txt) you should see this:

```
❯ ./line_check < sample_lines.txt
Line 4 is too long.
Line 6 is too long.
```

Modify [line_check.cpp](line_check.cpp) so that, in addition to printing which
lines are too long, it prints how long those lines are:

```
❯ ./line_check_a1 < sample_lines.txt
Line 4 is too long: 101 characters
Line 6 is too long: 110 characters
```

Put your program for this question in [line_check_a1.cpp](line_check_a1.cpp),
and make sure it compiles with the [makefile](makefile).

## Question 2

Modify your program from Question 1 to allow a maximum line length to be passed
as a command-line parameter:

```
❯ ./line_check_a2 100 < sample_lines.txt
Line 4 is too long: 101 characters
Line 6 is too long: 110 characters

❯ ./line_check_a2 200 < sample_lines.txt
No lines are too long.
```

The parameter is optional. If no parameter is given, then use a line length of
100:

```
❯ ./line_check_a2 < sample_lines.txt
Line 4 is too long: 101 characters
Line 6 is too long: 110 characters
```

If more than one parameter is passed, then print an error message and exit:

```
❯ ./line_check_a2 100 200 < sample_lines.txt
Too many arguments.
Usage: ./line_check_a2 [max_line_length]
```

Similarly, if the passed-in parameter is not an integer that's 0 or bigger, then
print an error message and exit:

```
❯ ./line_check_a2 -100 < sample_lines.txt
Invalid argument: -100
Usage: ./line_check_a2 [max_line_length]
```

Put your program for this question in [line_check_a2.cpp](line_check_a2.cpp),
and make sure it compiles with the [makefile](makefile).

## Question 3

Linux has a built-in program called `sort` that sorts the *lines* of a text
file. For example:

```
❯ cat names.txt    # cat prints the contents of a file
Rick
Morty
Summer
Uncle Slow
Evil Morty
Jerry
Beth

❯ sort names.txt
Beth
Evil Morty
Jerry
Morty
Rick
Summer
Uncle Slow
```

Your task is to implement a program named `mysort` that sorts lines of text of a
given file in alphabetical order. When `mysort` is called without any options,
it should print the same thing as built-in `sort`:

```
❯ ./mysort names.txt
Beth
Evil Morty
Jerry
Morty
Rick
Summer
Uncle Slow
```

**Important**
- Unlike the line checking programs above, `mysort` does *not* use the `<`
  re-direction operator when reading a file name. The file name is instead
  passed to the program as a command-line parameter.
- `mysort` does *not* modify the passed-in file; it always prints its output to
  `cout`.

`./mysort` also has two command-line options:

- `-r`: reverse the order of the sort, i.e. the lines are printed in reverse
  alphabetical order
- `s`: print lines in order starting with the shortest and going to the longest;
  lines of the same length are in alphabetical order

The general syntax of `mysort` is:

```
./mysort filename [-r|-s]
```

This means that you *must* pass exactly one file to `./mysort`, and then,
optionally, you can put either (but not both!) the `-r` or `-s` option after the
filename. For example:

```
❯ ./mysort names.txt -r
Uncle Slow
Summer
Rick
Morty
Jerry
Evil Morty
Beth

❯ ./mysort names.txt -s
Beth
Rick
Jerry
Morty
Summer
Evil Morty
Uncle Slow
```

`-r` and `-s` are *the only options allowed*, and *at most one* of them can be
given for a call to `mysort`. If you don't call `mysort` with exactly one file
and at most one of `-r` or `-s`, then print an error message (at least as
descriptive as in the examples) and return. For example:

```
❯ ./mysort names.txt -sr
Error: unknown option "-sr"
Usage: ./mysort input_file.txt [-r|-s]
  -r: sort in reverse order
  -s: sort in increasing order of string length

❯ ./mysort_sol names.txt -s -s
Error: invalid number of arguments
Usage: ./mysort_sol input_file.txt [-r|-s]
  -r: sort in reverse order
  -s: sort in increasing order of string length

❯ ./mysort
Error: invalid number of arguments
Usage: ./mysort input_file.txt [-r|-s]
  -r: sort in reverse order
  -s: sort in increasing order of string length

❯ ./mysort_sol blurb
Error: unable to open file "blurb"
Usage: ./mysort input_file.txt [-r|-s]
  -r: sort in reverse order
  -s: sort in increasing order of string length
```

For this assignment, to test if a file has been successfully opened it is enough
to check whether `input_file.fail()` returns `true` or `false` (where
`input_file` is a C++ `ifstream` object).

Put your program for this question in [mysort.cpp](mysort.cpp), and make sure it
compiles with the [makefile](makefile).

Please use the C++ sort functions in `std` to sort the lines. Those sort
functions are both very fast and almost certainly correct. It would be hard to
write your own sorting function that is better.

Hints:
- If `s` and `t` are C++ `string` variables, then `s < t` is `true` just when
  `s` comes before `t` alphabetically.
- If you first sort the lines alphabetically (e.g. using `std::sort`), then you
  can use `std::stable_sort` to sort the lines by length while keeping lines of
  the same length in alphabetical order.
- The `diff` command tests if two files are the same. For example, the command
  `diff out.txt sorted_data.txt` prints all the differences of the files
  `out.txt` and `sorted_data.txt` (and prints nothing if they are identical).
  This can be handy for testing the output of your program.

## Submitting Your Work

Please put all your `.cpp` files for the questions above into a folder named
`a1`, and then compress this to a zip file named `a1.zip`.

Do not submit any unnecessary files or folders. 


## How Your Code Will be Compiled by the Marker

The marker will compile and run your code on Ubuntu Linux using the given
[makefile](makefile):

```console
> make line_check_a1 
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   line_check_a1.cpp   -o line_check_a1

> ./line_check_a1 
...
```

If you've chosen to compile your program using a different method, then before
you submit your programs please make sure to test that they compile with this
[makefile](makefile).

## Marking Scheme

### Question 1
- *Completeness*, 2 marks
- *Correctness*, 2 marks
- *Efficiency*, 1 mark
- *Usability*, 1 mark: output should be at least as clear and detailed as in the
  examples
- *Source code readability*, 2 marks

### Question 2
- *Completeness*, 3 marks: no options, a correct line length, error cases
- *Correctness*, 3 marks
- *Efficiency*, 1 mark
- *Usability*, 1 mark: output should be at least as clear and detailed as in the
  examples
- *Source code readability*, 2 marks

### Question 3
- *Completeness*, 4 marks: no options, `-r` option, `-s` option, error cases
- *Correctness*, 4 marks
- *Efficiency*, 2 marks: your sort should be at least as efficient as the `sort`
  functions in `std`
- *Usability*, 1 mark: output should be at least as clear and detailed as in the
  examples
- *Source code readability*, 2 marks

## General Marking Scheme

### Completeness

Are all the required features fully implemented? Are any missing? Extra features
are usually okay as long as they do not interfere with the required features.

### Correctness

Are their any flaws in the program? Does everything work as specified?

### Efficiency

Does the program run efficiently, and avoid doing unnecessary work and using
unnecessary memory? Have the appropriate data structures and algorithms been
used?

### Usability

Is the program easy to use for its intended users? Is the output (including
error messages!) easy to read (e.g. good spelling, good grammar, nice
formatting)? This also includes things like using the requested file and class
names, submitting a program that compiles using a given makefile, etc.

### Source Code Readability

While readability is somewhat subjective, here are some guidelines:

- All names of variables, functions, structs, classes, etc. are sensible,
  self-descriptive, and consistent.

- Indentation and spacing is perfectly consistent and matches the structure of
  the program. All blank lines, indents, and extra spaces have a reason.

- All lines are 100 characters in length, or less.

- Comments are used when appropriate, e.g. to describe code that is tricky or
  very important. There are no unnecessary comments, and no commented-out code.

- Appropriate features of C++ are used in an appropriate way. For example, do
  **not** use a feature of C (like C-style strings) when there is a better
  feature of C++ (e.g. the standard `string` class). Don't use features you
  don't understand. Markers may ask you to explain any part of your code.

- Overall, the source code is easy to read and understand. 

### Other Deductions

- **-1 or more marks** if your program fails to compile with the given
  [makefile](makefile). If the marker can quickly and easily fix your program,
  the deduction may be small. But if there are significant errors and they can't
  compile it, it won't be marked and your assignment will get 0. Please note
  that following the exact rules for compiling is an important part of writing
  C++ programs, and it's *your* job to make sure your program compiles using the
  [makefile](makefile).

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

- Up to **-3 marks** if you do *not* include your full name, email, and SFU ID
  in the header of your file.
- **A score of 0** if one or more of the following are true:
  - You *don't* include the "Statement of Originality", or it is modified in any
    way.
  - You use code from some other source (e.g. the web, the textbook, ChatGPT, a
    friend, a teacher, a TA...) *without* citing the source.
  - You submit a "wrong" non-working file, and then *after the due date* submit
    the "right" file. If you can provide evidence that you finished the
    assignment on time, then it may be marked.

There may be other deductions, depending  uponthe circumstances.
