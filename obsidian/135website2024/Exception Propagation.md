
(See [[Introduction to Exceptions]] for more about exceptions.)

Consider this class, and the three functions that follow it:

```cpp
class Test {
    string name;
public:
    Test(const string& s)
    : name(s)
    { 
        cout << "Test(): " << name << " constructed ...\n";
    }

    ~Test() {
        cout << "... ~Test(): destructor for " << name << " called\n";
    }
};

void c() {
    cout << "c() called ...\n";
    Test c1("c1");
    cmpt::error("aaahhhhhh!!!");
    Test c2("c2");
    cout << "... c() ended normally\n";
}

void b() {
    cout << "b() called ...\n";
    Test b1{"b1"};
    c();
    Test b2{"b2"};
    cout << "... b() ended normally\n";
}

void a() {
    cout << "a() called ...\n";
    Test a1{"a1"};
    b();
    Test a2{"a2"};
    cout << "... a() ended normally\n";
}

int main() {
    try {
        a();
    } catch (...) {
        cout << "caught an exception!\n";
    }
}
```

Calling `a()` prints this:

```cpp
a() called ...
Test(): a1 constructed ...
b() called ...
Test(): b1 constructed ...
c() called ...
Test(): c1 constructed ...
... ~Test(): destructor for c1 called
... ~Test(): destructor for b1 called
... ~Test(): destructor for a1 called
caught an exception!
```

The call to `error` inside `c()` throws an exception that is *not* caught inside `c()`. The exception **propagates** to `b()` (because it was `b()` that called `c()`), giving `b()` the chance to catch it. But it doesn't catch the exception, and so the exception propagates to `a()`, giving it a chance to catch the exception. But it doesn't, and so the error keeps propagating up through all the functions that were called, eventually hitting `main`. Finally, in `main`, the exception is caught by the `try`/`catch`. If `main` didn't have a `try`/`catch` block, then the program would crash.

Every time you call a function C++ records function calls on the [[stack memory|call stack]]. Just before `error` is called in `c()`, the C++ [[stack memory|call stack]] looks like this:

```
|      |
| c    | <--- top (most recently called function)
| b    |
| a    |
| main | <--- bottom
--------
call stack
```

When the most recently called function ends, it is "popped" off the top of the [[stack memory|call stack]], and the program continues executing at the next line in `b()` (in addition to the function name, the location of the statement to execute next is also stored). But if `c()` ends due to an exception being thrown, C++ searches down the [[stack memory|call stack]], starting at `c()`, to find if there is a `try`/`catch` block that handles the exception. As it searches, it pops off the functions, being sure to call the destructors of all local objects in that function.

This process of going down the [[stack memory|call stack]] and calling destructors is called **stack unwinding**. 

Importantly, throwing an exception is **not** the same as returning a value. Returning a value and throwing an exception work very differently.