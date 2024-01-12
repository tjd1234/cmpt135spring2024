When your Linux system is up and running, you need a few more pieces of software. Open a Linux terminal command-line on the desktop and type this command:

```
$ sudo apt-get install git g++ make valgrind fish
```

This makes sure these four important programs are installed:

- `git` is used for version control, and makes it easy to upload/download code on websites like [Github](https://githib.com/).
- `g++` is the compiler we're using in this course. It converts C++ source code files into executable programs.
- `make` is a "build tool" that simplifies calling `g++` with the correct
  options.
- `valgrind` is a memory-checker that can tell you if your program has subtle
  errors such as [[memory leak|memory leaks]] or [[dangling pointer|dangling pointers]].
- [Fish](http://fishshell.com/) is a terminal shell program that many programmers prefer over [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) (the default shell program on Ubuntu).

You **don't** need to run this command on CSIL lab computers: those programs should already be installed.
## Helpful C++ Files
Download copies of these files to your computer:

- [hello_world.cpp]: A sample program to test that you've got your environment up and running. See below for how to compile and run it.
- [[generic course makefile|makefile]]: This stores all the compiler options we are using with g++ in this course. Put a copy of [[generic course makefile|makefile]] in every folder you compile C++ files in.
- [[cmpt_error.h]]: Contains the helper function `cmpt::error("...")` that intentionally crashes a program with a (hopefully!) helpful error message. See [[hello_world.cpp]] for an example of how to use it.
- [[cmpt_trace.h]]: Contains the `Trace` helper class that prints a message when a function is called and when it returns. It is especially helpful for understanding recursive functions. See the comments in [[cmpt_trace.h]] for an example of how to use it.

## Basic Command-line Commands for the Terminal
In this course we'd like you to work from a **command-line** terminal window, sometimes called a **shell** window. It lets you type commands to run programs.

[BASH](http://en.wikipedia.org/wiki/Bash_(Unix_shell)) is the most common default shell, and when you run a terminal you will see a prompt like this:

```bash
$
```

The `$` indicates this is a shell prompt. Everything before the `$` is information about what computer you are using and what directory you are in. Everything after the `$` is what you, the user, types.

The shell includes a complete programming language and dozens of commands. Here is a brief summary of basic commands that are often used in the terminal:

| Sample Command | Summary                                              |
| :------------- | :--------------------------------------------------- |
| `pwd`            | prints the present working directory                 |
| `ls`           | lists the files and folders in the current directory |
| `cd a2`        | change to directory a2                               |
| `rm old.cpp`   | delete the file old.cpp                              |
| `cp a1.cpp a1` | copy file a1.cpp to the folder a1                    |
| `man g++`      | display the manual page for the g++ command          |
| `less a1.cpp`  | display contents of a file one page at a time        |
| `cat a1.cpp`   | display contents of a file (unpaged)                 |
| `time ./a1`    | displays running time of program a1                  |

You can find many tutorials and help pages on the web for learning about the Linux command-line. For example, [this tutorial](http://www.ibm.com/developerworks/linux/library/l-lpic1-103-3/index.html) and [this tutorial](http://cht.sh/) both discuss many basic Linux commands, with helpful examples.

It is also common to manipulate files and folders interactively in the desktop
graphical user interface (GUI). Just open the folder you want to change, and
use the typical drag-and-drop actions to move, copy, rename, etc. files and
folders.

## Running C++ Programs in the Command Line Terminal
To create a C++ program in this course, you'll need  a text editor (to edit the source code files), a compiler to make executable programs (`g++`), a build tool to call the compiler with all the right options (`make`), and a [[memory leak]] checker to help catch errors (`valgrind`). Make sure to run the `sudo apt-get` command from above to install these tools.

Next, save a copy of these files from above into the same folder:
- [[hello_world.cpp]], a simple C++ program that asks for your age.
- [[generic course makefile|makefile]], which has the options for how we will call the compiler. **Important**It must be named exactly `makefile`, and must be in the same folder as [[hello_world.cpp]]. 
- [[cmpt_error.h]], helper files that contains the `error` function for stopping your program when an error is recognized.

To check that you're in the correct folder with the right files, use `cat` to print the contents of `hello_world.cpp`:

```cpp
$ cat hello_world.cpp
// hello_world.cpp

#include "cmpt_error.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Hello! How old are you? ";
    int age = 0;

    cin >> age;

    if (age <= 0) {
        cmpt::error("invalid age");
    }

    cout << "That is pretty old!\n";
}
```

Try typing `cat makefile` and `cat cmpt_error.h` as well.

We **compile** (or **build**) our programs using `make`:

```bash
$ make hello
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   hello.cpp   -o hello
```

Notice `g++` is called with many options. These come from [makefile](makefile), so make sure it's in the same folder as `hello_world.cpp`.

Assuming there are no compiling errors, run the resulting program like this:

```bash
$ ./hello_world
```

Notice you must type `./` first before the name.

To run a program with `valgrind`, type this:

```bash
$ valgrind ./hello_world
```

You will see a long message when the program ends. If there are any memory errors, they will be reported here (`hello_world` shouldn't have any errors).

If you want to **time** how long it takes a program to run, you can use the `time`
command like this:

```bash
$ time ./hello_world
Hello! How old are you? 10
That is pretty old!

________________________________________________________
Executed in    3.41 secs   fish           external 
   usr time  1300.00 micros  104.00 micros  1196.00 micros 
   sys time  142.00 micros  142.00 micros    0.00 micros 
```

This example uses the [Fish](http://fishshell.com/) shell, and your output may be formatted differently if you are using a different shell.

## File Redirection Using < and >
The `ls` command lists the files and folders in the current directory, e.g.:

```bash
$ ls
a1.h  a1_sol*  a1_sol.cpp  a1.txt  cmpt_error.h  makefile
```

The output of `ls` is printed to the screen, which is known as **standard
output**. In C++, functions like `printf` and `cin` always prints to standard
output.

You can easily write the output of a command use the `>` **re-direction
operator**:

```bash
$ ls > listing.txt
$ cat listing.txt
a1.h
a1_sol*
a1_sol.cpp
a1.txt
cmpt_error.h
listing.txt
makefile
```

The command `ls > listing.txt` re-directs the standard output of `ls` into the file `listing.txt`.

You can also re-direct standard input. That means you can, for example, use a text file of input as the input to a program that reads from standard input
(i.e. the keyboard).

Suppose the program `./age` asks the user for their name and age. You could run it like this:

```bash
$ ./age
What's your name? Bob
How old are you? 20

Hi Bob, 20 is a great age!
```

The program waits while the user types `Chris` (and then presses return), and also while the user types `21` (and then presses return).

Another way to run this program is to first create a file called, say,
`test_input.txt` with this content:

```
Chris
21
```

Then you can use the `<` re-direction operator to have `./age` get its input
from `test_input.txt`:

```bash
$ ./age < sample_input.txt
What's your name? How old are you? 
Hi Bob, 20 is a great age!
```

This can be very useful for testing --- it saves a lot of typing!

## More Information
The Linux command shell is complete programming environment with its own language. We will only use bits and pieces of it during this course. If you are curious learn more, here is a [free book about using the Linux command shell](https://www.linuxcommand.org/tlcl.php). You can find many other resources online.