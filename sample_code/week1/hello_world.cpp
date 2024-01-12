// hello_world.cpp

//
// To run this program, first put put a copy of the course makefile into the
// same directory as this file. It's named makefile and it's in the sample code
// for the course.
//
// You may also need to install the make command. On Ubuntu Linux this command
// should install it (and other useful tools):
//
//    > sudo apt-get install git g++ make valgrind
//
// When make ane the makefile are ready, run this command to compile the file:
//
//    ❯ make hello_world g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors
//    -Wno-sign-compare -Wnon-virtual-dtor -g   hello_world.cpp   -o hello_world
//
// Then run it like this:
//
//    ❯ ./hello_world Hello World!
//

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!\n";
    return 0;
}
