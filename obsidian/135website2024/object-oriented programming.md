---
aliases: OOP
---
## Overview of Object-oriented Programming
[[Object-oriented programming]], or [[object-oriented programming|OOP]] for short, is a popular style of programming that encourages programmers to combine data and operations into a single value called an object. For example:
- In a **graphical user interface** (**GUI**), a window could be modelled as an object. A window object would store data such as its location, size, content, whether it has a scroll bar, etc. The window object would also store operations on the window, such as moving it, re-sizing it, opening/closing it, etc.
- **In a video game, you might have object that represents game characters**. Character objects could store things like the character's name, whether they are good/bad, where they are in the game, what items they have, and so on. The character objects could also store operations on the character, such as speaking things, fighting with other characters, moving to other locations, etc.
- C++ `string`s are objects. A C++ `string` typically stores an array of characters and the size of the string. It also has operations like getting the size, getting an individual character, adding another string to the end, and so on.

Many real-world programming problems can be modelled as sets of interacting objects.

C++'s approach to object-oriented programming consists of two main concepts:
- **Objects**, which are *values* that exist at *run time*. Objects contain data and operations on that data. Objects can be treated like regular values: they can be passed to functions, returned returned from functions, modified, copied, and so on.
- **Classes**, which exist at *compile time*. A class is like a blue print for creating objects, and the class for an object is considered to be the object's type. A class tells you what data and operations an object contains, including how to create and destroy the object.
## Basic Terms: Classes and Structs
To create a new object in C++, you must first create a **class** for the object. A class describes the data and operations on that data (called [[method|methods]]) that the object will have. The data and operations are called the [[members]] of the class.

In C++, you create a class using either a `struct` or a `class`. `struct`s and `class`-es in C++ are almost the same: both can contain data, and both can contain operations (called [[method|methods]]) that operate on that data. The data and operations are called the [[members]] of the `struct` or `class`.

For example:

```cpp
struct Person 
{
    string name;
    int age;

    string to_string() const   // to_string is a method of Person
    {
        return name + " " + std::to_string(age);  // note std::
    }
};
```

`Person` is a `struct` with 3 members: `name`, `age`, and `to_string`. `name` and `age` are variables, and `to_string` is a [[method]]. The `const` on the header line of `to_string` means that `to_string` will *not* modify the object when it's called.

> **Note** In this case we must write `std::to_string`, with `std::` at the front. Otherwise, it would recursively call the `to_string` method and never end.

We can also write `Person` as an equivalent `class`:

```cpp
class Person 
{
public:
    string name;
    int age;

    string to_string() const {
        return name + " " + std::to_string(age);
    }
};
```

The only difference is that the first line of the `class` is `public:`, which tells the C++ compiler that all the members that follow can be read/written by *any* code with access to a `Person` object. *By default*, the members of a `struct` are public, while, by default, members of a `class` are private. 

If you remove `public:` from the `class`, then all the members will be **private**, which means they *cannot* be accessed by code outside of the `class`/`struct`. They can only be accessed by other members within that `class`/`struct`.

## Example: Dates
In what follows, lets see different ways of representing a date in a C++ program. We start with a non-object-oriented approach, and then work up to a more and more object-oriented version.
### Date as a Struct
Take a look at [[date_struct.cpp]]. It implements a date as a `struct` containing only variables, and provides a few helper functions. It uses a `struct` to store the data, but all the operations on that data are implemented as functions outside of the `struct`.

![[date_struct.cpp]]

### Date with Public Member Variables
[[date_class.cpp]] is similar to [[date_struct.cpp]], but uses some object-oriented features. Many of the functions are moved inside the `struct` so that they can get direct access to the `Date` variables.

![[date_class.cpp]]

`Date` uses a `class` instead of a `struct`. The first line of `Date` is `public:`, which means that all the code in `Date` can be accessed by *any* code in the program.

`Date` uses [[method|methods]] instead of functions: `is_valid()`, `print()`, and `println()` are all methods because they are declared *inside* of `Date`. A method is essentially a function that is part of a class, and a method can directly access any variables or methods in `Date`.

`is_valid()`, `print()`, and `println()` are all [[const method|const methods]], i.e. when they are called they *don't* modify any variables in `Date` (they just read them, never write them). Note that:
- A method is declared `const` by putting the keyword `const` after the header and before the body. 
- Sometimes [[const method|const methods]] are called [[const method|non-mutating methods]]. A method that is *not* `const` is called a [[mutating method]].
  
`Date` has a [[constructor]]. A [[constructor]] is a special [[method]] whose job is to make a new `Date` object and initialize its variables:

```cpp
// constructor: assigns values to member variables
Date(int d, int m, int y)
: day(d), month(m), year(y)  // initializater list
{ }
```
  
The *name* of the [[constructor]] is `Date`, which is the same name as the class. [[constructor|Constructors]] *always* have the same name as their class.

[[constructor|Constructors]] *never* have an explicitly listed return type (not even `void`): they always construct an object of the type of the class.

This [[constructor]] uses an [[initialization list|initializer list]] to assign initial values to the members of `Date`. Initializer lists can only be used with constructors, and you should always use them if you can: they ensure that the variables of the class/struct are initialized *before* they are used, which helps prevent bugs. They also allow you to initialize values that don't work with the [[assignment operator]], `operator=`.

In this particular example the constructor body is empty, but in general you can put whatever code you need into a constructor.

### Date with Private Member Variables
A common pattern in object-oriented programming is to make the member variables of a class *private*, and to provide public [[setter|setter method]]s for reading those variables, and [[getter|getter method]]s for writing them. By using [[setter|setter method]]s and [[getter|getter method]]s the programmer can control exactly how the data of an object can be accessed.

[[date_class_set_get.cpp]] adds setters and getters to `Date`:

```cpp
class Date 
{
    int day;   // 1 to 31
    int month; // 1 to 12
    int year;  // e.g. 2017

public:
    Date(int d, int m, int y)
    : day(d), month(m), year(y)  // initialization list
    { }

    bool is_valid() const 
    {
		// ...
    }

	// ...

    // Getters: methods that return the value of a variable. 
    // Getters should not modify the object, and so they are 
    // declared const.
    int get_day()   const { return day;   }
    int get_month() const { return month; }
    int get_year()  const { return year;  }

    // Setters: methods that change the value of a variable. 
    // Setters are never const because they modify the object.
    void set_day(int d)   { day   = d; }
    void set_month(int m) { month = m; }
    void set_year(int y)  { year  = y; }

}; // class Date
```

In addition to adding getters and setters, we've also made the member variables private: `day`, `month`, and `year` are declared in the `private:` section of the class, and so they can only be directly accessed by code within `Date`.

To allow code outside of `Date` to access `day`, `month`, and `year`, we add setters and getters. For example, for `month`, we add the [[getter|getter method]] `get_month()` that returns the value of `month`, and the [[setter|setter method]] `set_month(int m)` that assigns `m` to `month`.

The way we've written the [[getter|getters]] and [[setter|setters]] gives us *total* access to the member variables, and so it's not much different than if we'd made the variables public. But an advantage of [[getter|getters]] and [[setter|setters]] is that we can make methods to do whatever we like. For instance, we could add error-checking to `set_month`:

```cpp
void set_month(int m) 
{ 
	if (m < 1 || m > 31) 
	{
		cmpt::error("invalid month");
	}
	month = m; 
}
```

Or we could add an extra "helper" [[setter]] to make the `Date` class easier to use:

```cpp
void set_month(const string& m) 
{
	if (m == "JAN") 
	{
		month = 1;
	} else if (m == "FEB") 
	{
		month = 2;
	} 

	// ...

	} else if (m == "DEC") 
	{
		month = 12;
	} else 
	{
		cmpt::error("unknown month");
	}
}
```

### friend Functions
Using the `friend` keyword, you can give functions outside a class permission to access the private members of a class. For example:

```cpp
class Point 
{
    double x;                  // x and y are private
    double y;
public:
    Point(double a, double b)  // constructor
    : x(a), y(b)
    { }

    double get_x() const { return x; }
    double get_y() const { return y; }

    void print() const { cout << x << ", " << y << "\n"; }
    
    //
    // allow set_to_origin to access x and y
    //
    friend void set_to_origin(Point& p);
};

void set_to_origin(Point& p) // friend function
{
    p.x = 0.0;
    p.y = 0.0;
}

void point1() 
{
    Point p(10, -3.4);
    p.print();
    set_to_origin(p);
    p.print();
}
```

The `Point` class declares `set_to_origin` to be a [[friend function]], which means `set_to_origin` is allowed to read/write private variables in its parameter `p`.

> **Rule of Thumb** Generally, *avoid* `friend` functions. The problem is they allow objects to be changed in more ways, and that can make your code harder to understand and harder to use correctly. It's usually better to write a method instead of a `friend`.

### A Read-only Date Class
Another common object-oriented pattern is to *not use [[setter|setters]]*: make the `Date` class *read-only*. This simplifies the `Date` class and makes it easier to use correctly.

Here is an excerpt from [[date_class_readonly.cpp]]:

```cpp
class Date 
{
    int day;   // 1 to 31
    int month; // 1 to 12
    int year;  // e.g. 2017

public:
    // constructor: assigns values to member variables
    Date(int d, int m, int y)
    : day(d), month(m), year(y)  // initialization list
    { }

    // ...

    // Getters: methods that return the value of a variable. Getters 
    // should not modify the object, and so they are declared const.
    int get_day()   const { return day;   }
    int get_month() const { return month; }
    int get_year()  const { return year;  }

    //
    // No setters or other non-const methods ... Dates are read-only.
    //

    // returns a new Date exactly one year after this one
    Date next_year() const {
        return Date{day, month, year + 1};
    }

}; // class Date
```

Every member of this class is either private or const: once you construct a `Date` object, there's no way to change it. If you want a new date, then you must construct another one using the `Date` [[constructor]], or a helper method such as `next_year()`.


> **Aside** A common example of immutable objects occurs in languages such as Python and Java, where their *string* objects have no setters of any kind. Python and Java strings are immutable, i.e. once you create a string in those languages you cannot modify them in way. In contrast, C++ strings are mutable, i.e. you an change them in any way.

## Other Kinds of Constructors
A `class`/`struct` can have more than one [[constructor]]. For example, consider this `Point` class:

```cpp
struct Point 
{
    double x = 0;  // member initialization
    double y = 0;  // i.e. x and y are set to 0 by default

    // default constructor
    Point() // x and y are initialized above
    { }

    Point(double a, double b)
    : x(a), y(b)               // initializer list
    { }

    // copy constructor
    Point(const Point& other)
    : Point(other.x, other.y)  // constructor delegation
    { }

    // ...

}; // struct Point

// ...
```

`Point` has three different [[constructor|constructors]]:
- A [[default constructor]] is a constructor with no input parameters. In this particular example, the body of the default constructor does nothing since the member variables `x` and `y` can be initialized using [[member initialization]].
- A [[constructor]] that takes an `x` and `y` value as input.
- A [[copy constructor]] is a constructor that takes another `Point` as input and makes a copy of it. The [[copy constructor]] in this example uses [[constructor delegation]].

[[default constructor|Default constructors]] and [[copy constructor|copy constructors]] follow some special rules in C++. For example:
- If your class *doesn't* define a [[default constructor]] or [[copy constructor]], then C++ *automatically* creates an *implicit* default constructor that does nothing, and an *implicit* [[copy constructor]] that copies the member variables in the class.
- Many standard functions and containers, such as `vector<T>`, require that the `class`/`struct` `T` has, at least, a [[default constructor]] and a [[copy constructor]].
## Destructors
A [[destructor]] is a special method in a `class`/`struct` that is *automatically* called when its object is de-allocated. A programmer *cannot* call a [[destructor]] manually: [[destructor|destructors]] are always called automatically.

While a class can have as many *constructors* as it needs, a class has exactly *one* [[destructor]]. The name of a [[destructor]] is *always* the name of the class with a `~` at the start. [[destructor|Destructors]] *never* have input parameters. For example, for a class called `Printer`, it's destructor would be called `~Printer()`.

[[destructor|Destructors]] and [[constructor|constructors]] go together: when you create an object you must call a [[constructor]] to allocate it, and when the object is deleted, it's [[destructor]] is called to de-allocate it.

A [[destructor]] contains code you want to run when the object is deleted. Typically, this is "clean up" code, e.g. code that calls `delete`/`delete[]` on variables that were `new`-ed in the [[constructor]]. Together, [[constructor|constructors]] and [[destructor|destructors]] are a good to manage [[free store memory]]: the [[constructor]] calls `new`, and the [[destructor]] always remembers to call `delete`/`delete[]`. This helps prevent [[memory leak]]s and [[dangling pointer|dangling pointers]].

As mentioned at the start, an important fact about [[destructor]]s is that they *can't* be called explicitly by the programmer. This prevents the programmer from calling them at the wrong time, or forgetting to call them at all. 

Here's an example of a class with a [[destructor]]:

```cpp
#include "cmpt_error.h"
#include <iostream>
#include <cmath>

using namespace std;

struct Point 
{
    double x = 0;  // member initialization
    double y = 0;  // i.e. x and y are set to 0 by default

    // default constructor
    Point()                    // x and y are initialized above
    { }

    Point(double a, double b)
    : x(a), y(b)               // initializer list
    { }

    // copy constructor
    Point(const Point& other)
    : Point(other.x, other.y)  // constructor delegation
    { }

    // destructor
    ~Point() 
    {
        cout << "Point destructor called\n";
    }

}; // struct Point
```

The [[destructor]] is called `~Point()`, and all it does is print a message every time a `Point` object is deleted. Such a destructor could be useful for debugging.

## The this Pointer
For every object a program creates, C++ automatically adds a special private pointer called `this` that points to the object itself. It's called the object's [[this pointer]].

You can use `this` to access members of an object. For example, here's how you can use `this` in the `Point` class from above: 

```cpp
struct Point 
{
    double x = 0;  // member initialization
    double y = 0;  // i.e. x and y are set to 0 by default

	// ...

	void print() {
		cout << "(" << this->x << ", "
		            << this->y << ")";
	} 

}; // struct Point
```

The `print` method is accessing `x` and `y` through the `this` pointer using the standard pointer `->` notation. In this particular case there's no need to use `this` (we could just write `x` and `y`), but later we will see situations where `this` is essential.

`this` is the key difference between a [[method]] and function. A [[method]] has access to its `this` pointer, while there is no `this` pointer for functions.

## Practice Questions
1. In your own words, explain the difference between a 
   - `struct` and a `class`
   - function and a [[method]]
   - a [[const method]], and a [[mutating method]]
2. In your own words, describe
   - what *public* and *private* mean when used in a `struct`/`class`
   - what a [[constructor]] is, and how to write one and call one
   - what an [[initialization list]] is, and when and why it is used
   - why using [[const method]]s is a good idea
   - what [[getter|getters]] and [[setter|setters]] are
3. As noted in the comments for [[date_struct.cpp]], `is_valid(const Date& d)` sometimes returns the wrong answer. How would you fix so that it works correctly for more (ideally all!) dates?
4. Implement the following for `Date` in [[date_class_readonly.cpp]]. Implement them as *functions* outside the class (and *not* methods inside the class):
   - `operator==(const Date& a, const Date& b)` returns `true` just when `a`
     and `b` are the same date, and `false` otherwise
   - `operator!=(const Date& a, const Date& b)` returns `true` just when `a`
     and `b` are different dates, and `false` when they're the same
   - `operator<(const Date& a, const Date& b)` returns `true` just when `a`
     occurs before `b`, and `false` otherwise
5. In your own words, describe what a [[destructor]] does. When it is called? Why can't a programmer call a [[destructor]] whenever they want?
6. In your own words, describe the `this` pointer.
