## Introduction
How do you know if a program works correctly?

There are two main approaches:
- **Inspection**: This means carefully reviewing a program to see if there are any errors or missing details. 
- **Testing**: Running the program on test input and checking it gives the correct output.

For example, `quote(s)` returns a copy of a string in ""-marks:

```cpp
string quote(const string& s) 
{
	return "\"" + s + "\"";
}
```

This function is relatively simple and it's not too hard to see by inspection that it's correct. But let's see how we could test it.

To test `quote`, we need some input values and the corresponding correct output values. For example:

- `quote("cat")` returns `"\"cat\""`
- `quote("hot soup")` returns `"\"hot soup\""`
- `quote("")` returns `"\"\""`

Occasionally, it may be possible to prove a program is correct. A proof can be thought of as a detailed and systematic inspection. In practice, it is rarely used since the proofs are usually more complex than the code.

## If-style tests
One way to *automatically* test `quote` is with a series of if-statements like this:

```cpp
void test_quote_if_style() 
{
	if (quote("cat") != "\"cat\"") 
	{
	    cout << "test failed";
	}
	
	if (quote("hot soup") != "\"hot soup\"") 
	{
	    cout << "test failed";
	}
	
	if (quote("") != "\"\"") 
	{
	    cout << "test failed"; 
	}
}
```
This kind of testing is simple and flexible. We print a short error message, but you could print a much more detailed message, or save the results in a file, or count the number of passed/failed tests, or anything else you like.

> **Note** Occasionally, it may be possible to **prove** a program is correct. A proof can be thought of as a detailed and systematic inspection. In practice, it is rarely used since the proofs are usually more complex than the code.
## Assert-style Tests
Here's another style of simple testing:

```cpp
#include <cassert>     // assert is from here

void test_quote_assert_style() 
{
    assert(quote("\"cat\"") == "\"cat\"");
    assert(quote("hot soup") == "\"hot soup\"");
    assert(quote("") == "\"\"");
    cout << "all quote tests passed\n";
}
```

`assert(bool_expr)` is a standard C++ *macro* that works as follows:
- If `bool_expr` evaluates to `true`, then *nothing* happens and the program continues. We say the assertion *succeeded*.
- if `bool_expr` evaluates to `false`, then the program immediately crashes with a message that includes the line number of the failed assert. In this case we say the assertion *failed*.

Since a failed assert crashes the program, the "all quote tests passed" message at the end of the function is printed just when every assert succeeds.

Assert-style testing is shorter than if-style tests, and it provides the line number of the failed assert. In many cases, this is the quickest and easiest form of testing.

> **Note** `assert` is a [[macro]], *not* a function. In C++, the difference is that when you call a function it first evaluates its arguments, and then passes those values to the function body. A macro, on the other hand, passes its arguments to the function *unevaluated*. The reason `assert` is a macro is so that it can get access to the line number where the assertion is, which is useful when debugging. Functions have no way of getting line numbers from source code.
>
> In general, you should avoid macros in C++ since they don't follow the same rules as functions (e.g. they can't do type-checking on the arguments) and can have subtle bugs.

## Table-style Testing
Another way to test `quote` is like this:

```cpp
struct Test 
{
	string input;
	string expected_output;
};

void test_quote_table_style() 
{
	vector<Testcase> all_tests = 
	{
		Testcase{"cat", "\"cat\""},
		Testcase{"hot soup", "\"hot soup\""},
		Testcase{"", "\"\""},
	};

	for(Testcase tc : all_tests) 
	{
		string actual = quote(tc.input);
		if (actual != expected) 
		{
			cout << "test failed\n";
		}
	}
}
```

The idea of table-style testing is to put all the input/output pairs into a "table", e.g. a vector or an array, and then call the function being tested on those pairs. Table-style testing makes it easy to add and remove test cases, and to write customized error messages.

Table-style testing is a little more work to set-up than the other kinds of testing we've seen, but it in practice it is often worth the effort.

## Property Testing
Sometimes it is useful to test that  program has a particular property. For example, `quote(s)` has these properties (among others):
- `quote(s).size() == s.size() + 2`
- `quote(s)[0] == '"' && quote(s)[n-1] == '"'`
- `quote("") == "\"\""`

For each property you could then generate some random strings to make sure they hold. For example:

```cpp
for(int i = 0; i < 100; i++) {
	string s = random_string();   // you must write random_string()
	if (quote(s).size() != s.size() + 2) {
	   cout << "failure\m";
	}
}
```
In this example, just because we `quote(s)` passes all the test does *not* mean it is correct. It just gives us more confidence that the property `quote(s).size() == s.size() + 2` holds. And if that property holds, it gives us more confidence that the entire function is correct. 

A nice feature of property testing is that, once you have a property, you don't need to create any (input, output) pairs. The inputs can be generated at random, and then checked by calling the function itself.

However, you do need to:

- **Come up with good properties to test**. In practice, many programmers find it interesting and useful to think of function properties. But it can be hard to know how which properties, and how many, are enough to ensure the overall correctness of a function.
- **Write functions like `random_string()` to generate random data**. The more property testing than you do the easier this gets because can create a library of such functions and re-use them.

## Testing with Large Language Models
Finally, take a look at [[Testing with ChatGPT]] for an interesting example of how to test code nearly automatically using a large language model (LLM) such as ChatGPT.

## Testing Terminology

[[Unit testing]] is testing done on a single function (or some other small "unit" of code) independent of the program it is part of. [[System testing]] is when you test an entire program. One of the difficulties with [[system testing]] is that it can't be done until the system is finished, or at least in a usable state. 

In practice, it is common for programmers to do [[unit testing]] at the same time as they write their program. You can mix writing code with testing: write some code, test it, write some more code, test it, and so on. By the time you've written the function, you have also tested it, giving more confidence in its correctness. Mixing testing and writing code is known as [[test-driven development]].

There are two basic ways of coming up with test cases. If you create a test case for a function by considering just its header and purpose (and ignoring its implementation), that's called [[blackbox testing]]. For example, consider this function:

```cpp
// returns a copy of s with leading and trailing
// space characters removed
string trim(const string& s) 
{
	// ...
}
```

Without seeing the body of the function, we can write some useful tests cases:

- `trim("  hello ")` returns `"hello"`
- `trim("nail")` returns `"nail"`
- `trim("   ")` returns `""`
- `trim("")` returns `""`

An advantage of this approach is that it can help you better understand how the function works, making it a little easier to implement. The test cases are concrete examples you can work from as you write the function.

[[Whitebox testing]] is when you create test cases by considering a functions header, purpose, *and* implementation. This way you can pick test cases that cause every line of the function to be executed at least once. For example:

```cpp
// returns a message describing temperature t
string describe_temp(double t) 
{
	if (t < 0.0) cout << "very cold";
	else if (t == 0.0) cout << "water freezes";
	else if (t < 10.0) cout << "not too cold";
	else if (t == 100.0) cout << "water boils";
	else cout << "hot"; 
}
```
Using [[whitebox testing]], we come up with test cases that execute each branch of the if-statement:
- `describe_temp(-1.0)` returns `"very cold"`
- `describe_temp(0.0)` returns `"water freezes"`
- `describe_temp(5.0)` returns `"not too cold"`
- `describe_temp(100.0)` returns `"water boils"`
- `describe_temp(11.0)` returns `"hot"`

In general, [[blackbox testing]] tends to be preferable to [[whitebox testing]] because blackbox test cases will still work even if you change the implementation of the function. [[Whitebox testing]] cases might no longer be useful if the implementation changes.

Another useful distinction is [[automated testing]] versus [[manual testing]]. In [[manual testing]] you test your function by hand, and visually verify that the output is correct. While this is fine for a few test cases, or visual output (like graphics), in practice it quickly becomes tedious and programmers start to cut corners, make mistakes, or just don't do it at all.

In contrast, [[automated testing]] is when you write test code to automatically call the function being tested and to automatically check that its output is correct.

In general, [[automated testing]] is much preferred to [[manual testing]]. It is more work, but overall it can save time by decreasing the amount of time you spend debugging.

## How Many Test Cases is Enough?
Good question!

Generally, you want to **do the least amount of testing necessary to make you confident that your function works correctly in all important cases**.

For some functions, it might be possible to do [[exhaustive testing]] (aka [[exhaustive testing|brute force testing]]), i.e. test *all* possible inputs and outputs, e.g.:

```cpp
// if a and b are different, then true is returned; 
// otherwise, false is returned
bool exclusive_or(bool a, bool b);
```

`exclusive_or` only has 4 possible different inputs, so we can easily test them all.

But more typically, functions have many more input values than could ever be practically tested. For example:

```cpp
// if a and b are different, then true is returned; 
// otherwise, false is returned
int sum(const vector<int>& v);
```

Assuming an `int` is 32 bits, and that, say, `v` could have as many as 2 billion elements, then there are $32 \cdot 2 \;\textrm{billion} = 64$ billion *bits* of input to `sum`, which means there are $2^{64}$ billion possible input vectors. This is an astronomical number --- there's no way to test that many different cases!

This example shows that **testing doesn't catch all bugs**. Just because a function passes all test cases you give it *doesn't* mean it is correct --- it's always possible that a case you didn't test for has a bug.

## Bugs that Testing has a Hard Time Catching
An important aspect of testing is that we can only test a function when we *know what it is supposed to do*. For example, consider this function:

```cpp
int f(int n) 
{
	return n + 1;
}
```

Is `f` correct? It's impossible to know, since we don't know what `f` is *supposed* to do. If `f` is *supposed* to return `n+1`, then it's correct. But if it is *supposed* to return `n+5`, then it has a bug. We can't test `f` because we don't know what the correct output is.

Here's another unusual function:

```cpp
// meant to always return 3, but has a bug
int three() 
{
  if (rand() == 0) 
  {
    return 2;
  } else 
  {
    return 3;
  }
}
```

`three()` *almost always* returns 3, as expected.

But every once in a long while, it returns 2 --- which is incorrect. For 32 bit `int`s, you'd expect about 1 out of every $2^{31}$ calls to `three()` to return the wrong result

> **Note** $2^{31} = 2147483648$, i.e. about 2.1 billion. So there is a 1 in 2.1 billion chance that `three()` returns the wrong value.

There is no particular test case that would cause 2 to be returned: `three` takes no input, and the error occurs randomly!

There are really only two ways to notice this error:
1. Read the implementation and see that it has this error.
2. Do a *lot* of testing, e.g. billions and billions of calls.

While this is a contrived example, unpredictable and hard to catch errors like this do occur practice. For example, sometimes a problem in hardware can cause unpredictable behaviour in programs that are logically correct.

[[concurrent program|Concurrent programs]] can have bugs that don't appear in non-current programs. The different threads of control can interact in subtle and unexpected ways. The exact conditions under which a bug in a [[concurrent program]] occurs can often be extremely difficult to re-create, and can sometimes even seem like random errors. As you can imagine, bugs like this are hard to catch and fix. Bugs due to concurrency are often referred to in general as [[race condition]]s.

## Practice Questions
1. Name three different styles of testing, and give examples of how they work.
2. In your own words, explain the difference between [[unit testing]] and [[system testing]]. What's one of the problems with [[system testing]]?
3. In your own words, explain [[blackbox testing]] and [[whitebox testing]]. How are they similar? How do they differ?
4. Why is [[manual testing]] usually a bad idea?
5. What is [[exhaustive testing]]? Give an example of a function when you can use it, and a function when you can't.
6. How much testing should you do for a function?
7. In your own words, explain why a function might not be correct even through it passes all its tests.
8. Give an example of a function with a bug that testing would have a hard time catching. Instead of testing, how might the bug be caught?
9. What is a [[concurrent program]]? What is a [[race condition]]?
