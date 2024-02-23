(For more information about exceptions, see [[Introduction to Exceptions]],)

## Example: Parsing
This function takes a string of the form `"a + b"` as input, and returns the sum of `a` and `b` as an `int`:

```cpp
// Takes a string of the form "a + b", where a and b are ints, 
// and returns their sum. For example, "4 + 10" returns 14.
int eval(const string& s) {
    // find the position of the '+'
    int plus_loc = s.find('+');
    if (plus_loc == string::npos) cmpt::error("eval: + not found");

    // get a and b as their own strings
    string a = s.substr(0, plus_loc);
    string b = s.substr(plus_loc + 1);

    // convert a and b to ints using the standard function stoi
    // (string to int)
    int result = stoi(a) + stoi(b);

    return result;
}
```

> **Aside** `eval` is an example of a [[parser]].

It appears to work fine if you pass it well-formed strings, e.g.:

```cpp
cout << eval("2 + 3");          // 5
cout << eval("25+-3");          // 22  
cout << eval(" 8   +  10   ");  // 18
```

Notice that extra spaces are no problem. The standard `stoi` function ignores spaces at the beginning or end of a string.

But if you pass it a badly-formed string, it crashes, e.g.:

```cpp
cout << eval(" two + 3");

terminate called after throwing an instance of 'std::invalid_argument'
  what():  stoi
```

This error says that the program stopped unexpectedly due to an `invalid_argument` exception thrown by the `stoi` function. The problem is
that `stoi` can't convert "two" to an `int`.

Here's another example:

```cpp
cout << eval(" 2 + 39043090300473");

terminate called after throwing an instance of 'std::out_of_range'
  what():  stoi
```

The error is different here. The message says that `stoi` threw an exception
because the number is bigger than the biggest possible `int`.

Using `try`/`catch` we can catch these exceptions and print friendlier error messages:

```cpp
void print_safe(const string& s) {
    try {
        int result = eval(s);
        cout << "result = " << result << "\n";
    } catch (std::invalid_argument& e) {
        cout << "error: one, or both, of the operands of \"" 
             << s << "\"\n"
             << "       is not a valid int\n";
    } catch (std::out_of_range& e) {
        cout << "error: one, or both, of the operands of \"" 
             << s << "\"\n"
             << "       are outside the range of an int\n";    
    } catch (...) {
        cout << "error: an unknown error has occurred\n"
             << "       with input \"" << s << "\"\n";
    }
}

void test_safe() {
    print_safe("11  +33");
    print_safe("two + 3");
    print_safe("2 + 39043090300473");
    print_safe("cow");
}
```

An important idea here is that `eval` was initially written *without* worrying about exceptions. Catching the exceptions came later. This lets the programmer separate the code that solves the problem from the code that handles its errors. Error handling code can get messy, and if this had been mixed-in with the main code for `eval`, it would likely have been much less readable.

Notice that the exception thrown by `cmpt::error("eval: + not found")` is *not* handled properly in `print_safe`. The try/catch block in `print_safe` *doesn't* explicitly catch the `runtime_error` exception, and so it gets treated as an unknown error.

There is at least one other issue with the code in `eval`: how should examples like `eval("2.9 + 2")` be handled? It turns out that `stoi` *truncates* the 2.9, i.e. 2.9 becomes 2. Some programmers might say that's an error because we said that the `eval` function works with `int`s, and so it should throw an error when given a non-`int`. Other programmers might say that converting it to an `int` is fine because, after all, that's what C++ normally does when converting floating point numbers to `int`s. So, in this case, it's up to you, the programmer, to decide if `eval("2.9 + 2")` ought to be an error. If you do decide it is an error, then you need a new version of `stoi` that throws an exception in that case.
