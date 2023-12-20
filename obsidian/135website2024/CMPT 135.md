This site has the lecture notes for **CMPT 135 in Spring 2024 at SFU Surrey**. [Canvas](https://canvas.sfu.ca) is where you'll find course marks, due dates, assignment marking schemes, discussions, announcements, etc. 

## Useful Links
CMPT 135 uses modern C++ in Linux/Unix, and you should try to set up Linux on your own computer:

- If you're using **Windows**, I recommend you follow these instructions: [[Using VS Code to Run C++]].
- If you have a **Mac**, you can use the Terminal that comes with it and install the necessary software for this course (`g++`, `make`, and `valgrind`) using package managers like [MacPorts](https://ports.macports.org/) or [Homebrew](https://brew.sh/). Macs don't directly support Linux, but instead support a version of Unix that is probably close-enough for this course. You could also try [installing a virtual machine on Mac](https://www.macworld.com/article/668848/best-virtual-machine-software-for-mac.html) that runs Ubuntu.

Please make the effort to get C++ running on your own computer. It might take a bit of work the first time, but it's worth it. 

If the for some reason none of the choices above work for you, then:
- Try [[Setting up a Linux a virtual machine]].
- Try running C++ on the website [repl.it][https://replit.com/].
- Use the computers in CSIL.

**Ncurses** is a library that gives you more control over the cursor on the screen, and it might be used in some examples or assignments. Here are some instructions for [[setting up ncurses on Ubuntu Linux]].

## Lecture Notes 
**The timing of each topic is approximate, and may change as we go**. The examples used in some weeks may also change.

### Week 1
- Course overview
- [[C++ Review|Reviewing C++]]
- [Sample code](https://github.com/tjd1234/cmpt135spring2024/tree/main/sample_code)
- [Sample code for week 1](https://github.com/tjd1234/cmpt135spring2023/tree/main/lectures/week1) (including the [word count example](https://github.com/tjd1234/cmpt135spring2023/tree/main/lectures/week1/wordcount) and [checking long lines](https://github.com/tjd1234/cmpt135spring2023/blob/main/lectures/week1/wordcount/line_check.cpp))

### Week 2
- [[Calling a function]]
- [[Testing code]]

### Week 3
- [[Pointers and memory management]]

### Week 4
- [[Common Pointer Problems]]
- Example: [[function-oriented dynamic array]]
- [[Object-oriented programming]]

### Week 5
- [[Object-oriented programming]]
- [[Implementing a dynamic array with objects]]
- [[double_list_plus.cpp|A dynamic array with some C++-specific features]]

### Week 6
- [[Introduction to inheritance|Inheritance]]

### Week 7
- [[Separate compilation]], and [[splitting int_vec]] into a `.h` and `.cpp` file.
- [[namespaces|Namespaces]]
- [[Introduction to Exceptions|Exceptions]]

--------------------------

**Reading week (Feb 19 - 23)**: no lectures or labs

--------------------------

### Week 8
- Midterm practice
- Midterm!
- [[Recursion]]

### Week 9
- Midterm review
- [[Recursion]]

### Week 10
- [[Calculating large powers]]
- [[The max function]]
- [[linear search|Algorithms and linear search]]

### Week 11
- [[Basic sorting]]
- [[basic sorting#Binary Search|Binary search]]
- [[O-notation]]

### Week  12
- [[Easy and Hard Problems]]
- [[Using Templates]]

### Week  13
- final exam review
