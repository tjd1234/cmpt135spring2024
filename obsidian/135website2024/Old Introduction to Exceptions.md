Recognizing and handling errors is an important topic in real-world programming. There are a number of general approaches to error handling, and here we will consider one of them: *exceptions*.

## Throwing Exceptions
In C++, an [[exception]] is an object that represents an error, i.e. something exceptional. We do two main things with exceptions:
1. **Throw them**. When an error occurs your code can *throw* an exception. i.e. cause an exception to occur. As explained below, exceptions follow their own flow-of-control rules.
2. **Catch them**. Your program has the option of *catching* and handling any exception that has been thrown. Uncaught exceptions will cause your program to crash.

`throw` creates a new exception. For example:

```cpp
void error(const string& message)
{
    throw std::runtime_error(message);
    cout << "This line is never executed!\n";
}
```

When `error` is called we say it **throws** (or **raises**) a `runtime_error` [[exception]].
`runtime_error` is a standard pre-defined C++ class whose objects are exceptions. The expression `std::runtime_error(message)` creates a new `runtime_error` object, and the flow of control immediately jumps out of the function, skipping any statements that come afterwards. 

Importantly, a function that throws an exception does **not** return.

Suppose we call `error` like this:

```cpp
void error_test1() {
    cout << "About to call error ...\n";
    error("testing 1, 2, 3");
    cout << "... error called!\n";
}
```

This happens when it runs:

```cpp
About to call error ...
terminate called after throwing an instance of 'std::runtime_error'
  what():  testing 1, 2, 3
```

Notice that the `cout` statement in `error` is *not* called, and the `cout` statement in `error_test1` is also *not* called. That's because `throw` breaks the normal sequence of flow in C++, immediately jumping out of the function.

Such jumping can sometimes cause serious problems. For instance:

```cpp
void error_test2() {
    int* arr = new int[10];

    error("testing 1, 2, 3");
    
    delete[] arr;  // oops: memory leak!
}
```

An exception has been thrown before `delete[]` is called, which causes a [[memory leak]]! In practice, it can be difficult to know when exceptions might be thrown, and so this can be a source of subtle errors.

## Catching Exceptions
An uncaught exception will crash your program. Since crashing is never desirable in real-life programs, we need some way to handle exceptions. C++ lets you **catch** exceptions using `try`/`catch` blocks. For example:

```cpp
void error_test3() {
    int* arr = new int[10];

    try {
        error("testing 1, 2, 3");
        delete[] arr;  // not called if there is an exception 
                       // thrown in the previous line
    } catch (const std::runtime_error& e) {
        cout << "Caught a runtime exception thrown by error: " 
             << e.what() << "\n";
        delete[] arr;  // clean up memory
    }
    cout << "error_test3 finished\n";
}
```

In this example, if any statement inside the `try` block throws an exception of type `runtime_error`, the flow of control immediately jumps to the `catch` block and runs its body. The `cout` statement at the end is outside both the `try` part and the `catch` part, and so it will always be executed.

We could have written it like this:

```cpp
void error_test4() {
    int* arr = new int[10];

    try {
        error("testing 1, 2, 3");
    } catch (const std::runtime_error& e) {
        cout << "Caught a runtime exception thrown by error: " 
             << e.what() << "\n";
    }
    
    delete[] arr;  // clean up memory
}
```

Now there is only one call to `delete` which will be called whether or not a `runtime_error` is thrown in the body of `try`.

This `catch` statement only catches exceptions of type `runtime_error`. Determining all possible exceptions a block of code might throw can be extremely difficult, even impossible.

If you want to catch *all* exceptions of any type, use `catch (...)`:

```cpp
void error_test5() {
    int* arr = new int[10];

    try {
        error("testing 1, 2, 3");
    } catch (...) {  // ... catches all exceptions
        cout << "Caught some exception thrown by error\n";
    }
    
    delete[] arr;  // clean up memory
}
```

`catch (...)` catches *all* exceptions that might thrown in the `try` block, even ones we don't know about ahead of time. 

A `try` block can have multiple `catch` clauses, one for each different type of exception it wants to handle. For example:

```cpp
void error_test6() {
    int* arr = new int[10];

    try {
        error("testing 1, 2, 3");
    } catch (const std::runtime_error& e) {
        cout << "Caught a runtime exception thrown by error: " 
             << e.what() << "\n";
    } catch (...) {
        cout << "Caught some unknown exception thrown by error\n";
    }
    
    delete[] arr;  // clean up memory
}
```

It is still possible for this code could to throw, but not catch, an exception. The problem is with `new`: if there is not enough memory to create the array, then `new` throws `bad_alloc`. So to be completely sure we catch all exceptions, we should put the call to `new` inside the `try`:

```cpp
void error_test7() {
    int* arr = nullptr;

    try {
        arr = new int[10];        
        error("testing 1, 2, 3");
    } catch (const std::runtime_error& e) {
        cout << "Caught a runtime exception thrown by error: " 
             << e.what() << "\n";
    } catch (const std::bad_alloc& e) {
        cout << "bad allocation: " << e.what() << "\n";
    } catch (...) {
        cout << "Caught some other exception\n";
    } 
    
    delete[] arr;  // clean up memory
}
```

Now `delete[]` is the only statement outside of the `try` block. What if *it* throws an exception? Fortunately, it never will: the rules of C++ explicitly promise that `delete` and `delete[]` will *never* throw an exception.

[[smart pointer|Smart pointers]] are another way that C++ can handle issues such as this, but we won't cover them here.

## Exceptions and Destructors
In the above examples, we were able to clean up memory because we had access to `arr`. But consider this class:

```cpp
class Thing {
    int* arr;
public:
    Thing() 
    : arr(new int[10])
    { }

    ~Thing() {
        delete[] arr;
        cout << "... Thing destructor called\n";
    }
};
```

The `arr` pointer in `Thing` is private, and so the only way to de-allocate it is to call its destructor.

So what happens in code like this?

```cpp
void error_test8() {
    Thing x;

    error("testing 1, 2, 3");

    cout << "goodbye!\n";
    // Uh oh: Is the array x.arr deleted? Or is there a memory leak
    // when an exception is thrown?
}

int main() {
    try {
        error_test8();
    } catch (...) {
        cout << "caught an exception\n";
    }
    
    cout << "all done\n";
}
```

Happily, this code does *not* have a [[memory leak]]. If an exception is thrown, C++ *guarantees* that `x`'s destructor is properly called, and the array is de-allocated. 

Since it is possible for the `Thing` constructor to throw an [[exception]] (e.g. `bad_alloc` due to running out of memory), it's safer to do this:

```cpp
void error_test9() {
    try {
        Thing x;
        error("testing 1, 2, 3");
    } catch (...) {
        cout << "Caught some exception\n";
    } 
    // x's destructor is guaranteed to be called
}
```

If *any* exception is thrown by *any* statement in the `try` block, it will be caught by `catch (...)`, and so the destructor for `x` is guaranteed to always be properly called. This guarantee is extremely useful in practice.

> **Aside** C++ and C have a standard function called `exit(n)` that, when called, immediately terminates the program and returns error code `n` to the operating system. The problem with `exit` is that it *doesn't* call destructors, and so it doesn't properly clean up any resources that were in use when it was called. For example, if you call `exit` while your program has 10 files open and is connected to a printer, those connections are just suddenly severed and not shut down properly. This can cause problems for other programs that want to access them.

## RAII: Resource Acquisition is Initialization
Using constructors and destructors to manage memory (or other resources) is called [[resource acquisition is initialization]], or [[resource acquisition is initialization|RAII]] for short. The idea is simple and useful:

- put calls to `new` in constructors
- put calls to `delete`/`delete[]` in destructors; indeed, any code that
  *must* be run, even if an exception occurs, can be put in the [[destructor]]

> **Aside** Some languages, such as Java and Python, have try/catch blocks with a third block typically called a **finally** block. In these languages, you put code that must run, even if an exception occurs, inside the **finally** block. C++ has no **finally** block, and uses [[resource acquisition is initialization|RAII]] instead.

## More Information
- [[Parsing with Exceptions]] is a long example of how to use exceptions in a function.
- [[Exception Propagation]] shows how exceptions work with the [[stack memory|call stack]].

## Practice Questions
1. What is an exception? When are they used?
2. What does it mean to *throw* an exception? What does it mean to *catch* an exception?
3. *True* or *false*: when a function throws an exception, we can say it has returned the exception.
4. In a try/catch block, how do you catch *any* exception?
5. *True* or *false*: `new` could throw an exception.
6. *True* or *false*: `delete` could throw an exception.
7. In your own words, explain the difference in how a function ends when you call the standard `exit(n)` function versus throwing an exception. Which technique is better?
8. In your own words, explain the idea of [[resource acquisition is initialization]].
9. *True* or *false*: it's usually okay for a [[constructor]] to throw an exception.
10. *True* or *false*: it's usually okay for a [[destructor]] to throw an exception.
11. In your own words, and using an example, explain the idea of exception propagation on the [[stack memory|call stack]].
12. In your own words, and using an example, explain the idea of stack unwinding.