# Exceptions

Exceptions are a technique for signaling and handling recognizing errors. **Exception handling** involves these things:

- Exception objects, which are objects designed to represent errors.
- `throw` statements that raise an exception. When a `throw` statement is executed, the program stops running the current function and start looking for a `catch` block that can handle the exception.
- `try`/`catch` blocks that change the flow of control of a program when an exception occurs and give programmer more control over what to with exceptions. For an example, and exception that is handled in a `catch` block need not crash your program.

## Throwing Exceptions

You can *throw* any type of value. Here is an example of throwing a `string`:

```c++
void example1()
{
    cout << "Hello!\n";

    throw "Oh no, an error has occurred!";

    cout << "Goodbye!\n";
}
```

When run this code it print's *Hello!* and then crashes with an error message:

```output
Hello!
terminate called after throwing an instance of 'char const*'
fish: './exceptions' terminated by signal SIGABRT (Abort)
```

Importantly, *Goodbye!* is not printed, because a `throw` statement immediately jumps out of the function.

The error message above is not very helpful: it just says a `char const*` (i.e. string) was thrown, and doesn't print the string. It's usually better to throw an **exception object**:

```cpp
void example2()
{
    cout << "Hello!\n";

    throw runtime_error("Oh no, an error has occurred!");

    cout << "Goodbye!\n";
}
```

When run it prints:

```output
Hello!
terminate called after throwing an instance of 'std::runtime_error'
  what():  Oh no, an error has occurred!
fish: './exceptions' terminated by signal SIGABRT (Abort)
```

Now the error message is printed, which is more helpful.

`runtime_error` is a standard C++ exception that you can use when you want to throw an exception. There are other standard C++ exceptions that you could throw in particular situations, and you can even create your own (e.g. to store special error information, or have a more specific names). We'll use just `runtime_error` in these notes.

## Catching Exceptions

When you `throw` an exception it's always possible that it could stop the entire program. In cases where we don't want the program to stop due to an exception we can **catch** exceptions using a `try`/`catch` block.

Consider this code:

```cpp
void example2()
{
    cout << "Hello!\n";

    throw runtime_error("Oh no, an error has occurred!");

    cout << "Goodbye!\n";
}

int main()
{
    example2();
}
```

It throws a `runtime_error` that crashes the program:

```output
Hello!
terminate called after throwing an instance of 'std::runtime_error'
  what():  Oh no, an error has occurred!
fish: './exceptions' terminated by signal SIGABRT (Abort)
```

Now lets **catch** the exception using a `try`/`catch` block:

```cpp
void example2()
{
    cout << "Hello!\n";

    throw runtime_error("Oh no, an error has occurred!");

    cout << "Goodbye!\n";
}

int main()
{
    try
    {
        example2();
    }
    catch (runtime_error e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}
```

Catching the exception lets us print a nicer or more descriptive error message. Notice that `e.what()` returns the message string in the exception object.

Sometimes you might want to catch multiple types of exceptions and do different things for each. You can do this with multiple `catch` blocks:

```cpp
try
{
    example2();
}
catch (const runtime_error& e)
{
    cout << "Error: " << e.what() << "\n";
}
catch (const bad_alloc& e)
{
    cout << "Allocation error: " << e.what() << "\n";
}
```

`bad_alloc` is a standard exception that is thrown by when `new` when you run out of free store memory.

If you want to catch *all* exceptions, you can do this:

```cpp
try
{
    example2();
}
catch (...) // catch all exceptions
{
    cout << "An error occurred!\n";
}
```

While this catches any exception, you don't know anything about the exception that was thrown. It could be *any* value: an exception object, a `string`, an `int`, etc.

## Example: Inverting a double

The `invert(x)` function returns `1 / x`. When `x` is 0, the function throws a `runtime_error`:

```cpp
// returns 1/x, and throws a runtime_error if x is 0
double invert(double x)
{
    if (x == 0)
    {
        throw runtime_error("Cannot invert 0");
    }

    return 1 / x;
}
```

Here's how we can use `invert`, catching the exception if it's thrown and printing a nice message:

```cpp
void invert_test()
{
    for (;;) // loop forever
    {
        cout << "Enter a number: ";
        double x;
        cin >> x;

        try
        {
            double result = invert(x);
            cout << "The inverse of " << x << " is " << result << "\n\n";
        }
        catch (const runtime_error &e)
        {
            cout << "Error: can't invert 0\n\n";
        }
    }
}
```

For example:

```output
Enter a number: 5
The inverse of 5 is 0.2

Enter a number: 0
Error: can't invert 0
```

## Exceptions and Destructors

Consider this function:

```cpp
void example3()
{
    int *arr = new int[10];

    throw runtime_error("Oh no, an error has occurred!");

    delete[] arr;
}

int main()
{
    try
    {
        example3();
    }
    catch (runtime_error e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    cout << "This program keeps going ...\n";
}
```

This code has a memory leak. `example3` allocates an array with `new`, but then never de-allocates it because an exception is thrown. The throw breaks the regular
flow of control of a program, and the `delete[]` is never run.

So how can we avoid this sort of problem? One good way is to put the array in a class and use the constructor to allocate the array, and the destructor to de-allocate. When an exception is thrown, it is guaranteed that the destructor of any objects defined in the function will be run. In this case, that means the array will be de-allocated and there is no memory leak:

```cpp
struct my_array
{
    int *arr;
    my_array(int size)
    {
        arr = new int[size];
    }

    ~my_array()
    {
        delete[] arr;
    }
};

void example4()
{
    my_array arr(10);

    throw runtime_error("Oh no, an error has occurred!");

    cout << "This code is never run ...\n";
}
```

In `example4` there is no memory leak. When the exception is thrown, the destructor for `arr` is automatically called, and so the array is correctly de-allocated.

## RAII: Resource Acquisition is Initialization

Using constructors and destructors to manage memory (or other resources) is called [[resource acquisition is initialization]], or [[resource acquisition is initialization|RAII]] for short. The idea is simple and useful:

- put calls to `new` in constructors
- put calls to `delete`/`delete[]` in destructors; indeed, any code that *must* be run, even if an exception occurs, can be put in the [[destructor]]

> **Aside** Some languages, such as Java and Python, have try/catch blocks with a third block typically called a **finally** block. In these languages, you put code that must run, even if an exception occurs, inside the **finally** block. C++ has no **finally** block, and uses [[resource acquisition is initialization|RAII]] instead.

## Exceptions in Constructors and Destructors
[Using exceptions inside constructors and destructors present some issues](https://isocpp.org/wiki/faq/exceptions#ctor-exceptions). Remember these two rules:

1. It's **usually okay** for a constructor to throw an exception.
2. It is **almost always bad** for a [[destructor]] to throw an exception that escapes the destructor. Basically, [[destructor|destructors]] should *never* throw exceptions.

For more details, see [this discussion](https://isocpp.org/wiki/faq/exceptions#ctor-exceptions).

## Throwing an Exception vs Exiting

Another way to stop a C++ program is use the standard library function `exit`:

```cpp
void example5()
{
    my_array arr(10);

    exit(-1);  // stop the program and return error code -1
}

int main()
{
    example5();

    cout << "This program keeps going ...\n";
}
```

While `exit` is similar to throwing an exception, there are at least two
important differences:

- `exit` cannot be "caught". The program immediately ends.
- `exit` does *not* call the destructor. Thus, resources used by an object might not be properly de-allocated. Not calling the `int_array` destructor is not a problem here because the program immediately ends. However, if some other resource was not properly destructed, such as a file or network connect, then there could be significant problems.

In general, in C++ you should always use exceptions to signal errors, and not `exit`. The exceptions are more flexible, and properly call destructors.

## Other Approaches to Error Handling

Error-handling is a big and complex topic, and exceptions are not the only way of dealing with errors. Two other common methods are:

- **Error flags**, e.g. when an error occurs the function sets a special global error variable. It is up to the programmer to check the error variable after every function call.
- **Returning error codes**. For example, [the Go language](<https://en.wikipedia.org/wiki/Go_(programming_language)>) allows functions to return multiple values, and one of those values can be an error code.

## A Philosophical Note

Some errors are more serious than others. For example:

1. The computer runs out of memory and `new` throws a `bad_alloc` exception.
2. A not so serious error: you open a file named `data.txt` but it doesn't exist in the current directory.

Clearly the first error is more serious than the second. If your program runs out of memory then it probably can't continue, and all you can do is print a message and stop.

But not finding a file is not as serious: it doesn't seem to be the kind of error that should stop the entire program.

Throwing an exception always has the possibility of stopping the program. So throwing an exception for the out-of-memory error is reasonable.

But throwing an error and potentially stopping the program for a wrong file name seems excessive. Instead, your code could ask you to enter a different file name, or find an alternative file. You could even design your program to avoid file-not-found errors completely, e.g. you could always restrict the user to choosing from a list of available files.

> **Rule of Thumb** Whenever you throw an exception, ask yourself if the error
> is serious that it is worth potentially stopping the program. If it's not,
> then consider a different way to deal with the error.

## Practice Questions

1. What is an exception?
2. Why is it usually better to throw exception objects rather than strings?
3. What is the difference between `throw` and `return`?
4. You can create your own exception objects. Why might you want to do this?
5. What happens if a program throws an exception but never catches it?
6. Give an example of:
   - a `try`/`catch` block that catches multiple types of exceptions
   - a `try`/`catch` block that catches all exceptions

7. In the example function `invert_test`, suppose the `result` variable was removed and the print statement was changed to this:
   
   ```cpp
   cout << "The inverse of " << x << " is " << invert(x) << "\n\n";
   ```

    Explain why this change does *not* produce the same output as the original code.

8. What are two reasons why you should use exceptions to signal errors, rather than the standard `exit` function?
9. Besides exceptions, what are two other common ways of handling errors in programming?
10. Give an example of:
    - an error that is probably serious enough to throw an exception
    - an error that is probably not serious enough to throw an exception
## More Information
- [[Parsing with Exceptions]] is a longer example of how to use exceptions in a function.
- [[Exception Propagation]] shows how exceptions work with the [[stack memory|call stack]].
