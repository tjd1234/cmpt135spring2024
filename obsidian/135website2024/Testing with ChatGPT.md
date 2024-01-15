ChatGPT is a popular large language model (LLM) that can generate all kinds of interesting human-sounding text given a starting "prompt". One of the things it is pretty good at is generating C++ code for testing. If you give it  a function to test and a description of how you want to test it, then it can often (although not always!) create code to test that function.

For example, suppose we want to do unit testing on this function:
```c++
//
// Returns a copy of s with all leading and trailing spaces removed.
// E.g. strip(" apple  ") returns "apple".
//
string strip(const string& s) 
{
    int i = 0;
    while (i < s.size() && s[i] == ' ') 
    {
        i++;
    }
    int j = s.size() - 1;
    while (j >= 0 && s[j] == ' ') 
    {
        j--;
    }
    return s.substr(i, j - i + 1);
}
```

To do unit testing we need to create (*input*, *expected_output*) pairs, and then run the function on each output and check that what it returns matches *expected_output*.

It's not hard to create (*input*, *expected_output*) pairs by hand, e.g.:
- (`""`, `""`), empty string test
- (`"   "`, `""`), all spaces test
- (`"cat"`, `"cat"`), no spaces test
- (`"   cat"`, `"cat"`), just leading spaces
- (`"cat   "`, `"cat"`), just trailing spaces
- (`"  cat   "`, `"cat"`), leading and trailing spaces

However, it can get tedious writing these cases. Plus, writing even a short description of each test case makes it more time-consuming. In a time-crunch many programmers might give up on this kind of manual test-case creation.

## ChatGPT Can Generate Test Cases
ChatGPT is pretty good at generating test cases. For example, here is a prompt given to ChatGPT:

```
Write test code for this C++ function:

//
// Returns a copy of s with all leading and trailing spaces removed.
// E.g. strip(" apple  ") returns "apple".
//
string strip(const string& s) 
{
    int i = 0;
    while (i < s.size() && s[i] == ' ') 
    {
        i++;
    }
    int j = s.size() - 1;
    while (j >= 0 && s[j] == ' ') 
    {
        j--;
    }
    return s.substr(i, j - i + 1);
}
  
Use table-style testing where each test starts with a string description followed by an input and an expected output. Include a variety of test cases: small inputs, big input, extreme inputs, random inputs, etc. Use code to check that all the inputs are correct. If a test fails, print a neatly indented error message showing the expected and actual results in a way that's easy for the programmer to understand. Also number the test cases, and at the end print a summary of how many tests passed and how many failed.
```

Note that we give this *entire* text prompt to ChatGPT. It then prints this code (it also prints some descriptive text, but that's been cut here):

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to be tested
string strip(const string &s)
{
    int i = 0;
    while (i < s.size() && s[i] == ' ')
    {
        i++;
    }
    int j = s.size() - 1;
    while (j >= 0 && s[j] == ' ')
    {
        j--;
    }
    return s.substr(i, j - i + 1);
}

// Struct to hold test cases
struct TestCase
{
    string description;
    string input;
    string expectedOutput;
};

// Test function
void testStripFunction()
{
    // Table of test cases
    vector<TestCase> testCases = {
        {"Leading spaces", "   Hello", "Hello"},
        {"Trailing spaces", "Hello   ", "Hello"},
        {"Leading and trailing spaces", "   Hello   ", "Hello"},
        {"No spaces", "Hello", "Hello"},
        {"Only spaces", "     ", ""},
        {"Empty string", "", ""},
        {"Mixed spaces", "  Hello World  ", "Hello World"},
        {"Long string with spaces", 
         "  This is a test string with spaces at both ends  ", 
         "This is a test string with spaces at both ends"},
        {"String with no leading or trailing spaces", 
         "No extra spaces", "No extra spaces"},
        {"String with tabs and spaces", "\t   Hello\t ", "\t   Hello\t"}};

    int passedTests = 0, failedTests = 0;
    for (size_t i = 0; i < testCases.size(); ++i)
    {
        const auto &testCase = testCases[i];
        string result = strip(testCase.input);
        if (result != testCase.expectedOutput)
        {
            cout << "\nTest " << i + 1 << " failed: " 
                 << testCase.description << "\n";
            cout << "    Expected: \"" << testCase.expectedOutput 
                 << "\"\n";
            cout << "    Actual:   \"" << result << "\"\n";
            failedTests++;
        }
        else
        {
            cout << "Test " << i + 1 << " passed: " 
                 << testCase.description << endl;
            passedTests++;
        }
    }

    cout << "\nTest Summary: " << passedTests << " passed, " 
         << failedTests << " failed.\n";
}

int main()
{
    testStripFunction();
    return 0;
}
```

The code has been manually re-formatted somewhat to make it easier to read and fit neatly on the screen.

The output compiles and runs! By reading the code we can see that it makes sense, plus it is easy to manually add/remove new tests cases, or to change how tests are reported.

## Changing Code by Chatting

After ChatGPT gives you a result, you can *chat* about that result. For example, suppose you want the description of the test to come last in the `struct` instead of first. Then you could give ChatGPT a prompt like this:

```
Can you please change the struct so that the description comes last instead of first?
```

When I try this, ChatGPT re-writes the entire program to work so that descriptions comes last. It modifies the `struct`, and also all the test cases so that the description is last. This saves the programmer a lot of tedious work!

Similarly, we were able to get it to improve the quality of its output by telling it how to change the output. After running the code, we could prompt it things like this:

```
Please print the number of passed/failed cases at the end of the test run.
```

For some more complex or unusual requests it might not do it correctly, but for relatively simple and straightforward changes it did fairly well.
## Things to Watch Out For
ChatGPT is not perfect, and it needs a human to review it's work. For example, sometimes it gets test cases wrong. In the examples above, it occasionally added extra backslash characters, or got confused about the difference between `\t` and an actual tab character. These problems were usually easy to find and fix, but they do require manual checking by the programmer.

Also, if you run the same prompt more than once you *don't necessarily* get the same output. It might give you slightly different code an examples each time. This could sometimes result in errors and, so again, human checking is needed.

ChatGPT seems to know most basic C++ functions quite well. However, it does seem to have trouble with more unusual or less common functions. So check more carefully when you are working with code that you think is original or novel.

## Practice Questions
1. Write a function called `quote(const string& s)` that returns a copy of `s` with "-marks around it. Or, if `s` has at least two characters and already beings and ends with a ", then return a copy of  `s` unchanged. 
   
   Now using techniques like the one above, ask ChatGPT to create code for testing it. Try with the given prompt, and also try to chat with it and make improvements to the program it returns (e.g. does a prompt like "make the output neater" work?).
   
2. There are other large language models (LLMs) besides ChatGPT. Try re-doing the question above (or the example in the notes) in another LLM, such as CoPilot. Keep note of how it compares: Does the output seem better? Does it give results more quickly? Is the interface easier to use? And so on.