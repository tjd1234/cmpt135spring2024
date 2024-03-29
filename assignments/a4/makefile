##############################################################################
#
# Makefile for assignment 4 of CMPT 135 Spring 2024, SFU Surrey.
#
# Commands for this makefile that can be typed at the command line:
#
#   make
#      Build the executable program a4_main_test.
#
#   make -j
#      Build a4_main_test possibly a little more quickly. The "-j" option
#      tells make to try to use multiple CPUs when compiling two, or more,
#      files.
#
#   make clean
#      Removes a4_main_test, and all the .o object files.
#
#   make a4
#      Compiles a4.cpp, creating a4.o.
#
#   make a4_main
#      Compiles a4_main.cpp, creating a4_main.o.
#
##############################################################################

# Set the C++ compiler options:
#   -std=c++17 compiles using the C++17 standard (or at least as 
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors 
#   -Wfatal-errors stops the compiler after the first error
#   -Wno-sign-compare turns off warnings for comparing signed and 
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

a4_main_test: a4.o a4_main.o
	g++ -o a4_main_test a4.o a4_main.o

a4:
	g++ -c $(CPPFLAGS) a4.cpp

a4_main:
	g++ -c $(CPPFLAGS) a4_main.cpp

clean:
	rm -f a4_main_test a4.o a4_main.o
