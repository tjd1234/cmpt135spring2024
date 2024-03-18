---
aliases: [destructors]
---

#terminology

## Definition
A special method that is *automatically* called when an object is deleted. For the greater majority of applications, the programmer should never explicitly call a destructor. 

> In some cases it may be useful to call a destructor explicitly, and so C++ allows for the possibility. The most common case is when your program uses [placement new](https://en.cppreference.com/w/cpp/language/new), a variation of the `new` operator that we are discussing in these notes.

Destructors "clean up" resources used by an object. They often work in coordination with [[constructor]]s: the [[constructor]] allocates the resources, and the [[destructor]] de-allocates the resources. For instance, a destructor might call `new` to allocate an array on the free store, and the destructor would call `delete[]` on that array to de-allocate it. This pattern of using a [[constructor]] and destructor to manage resources is called [[resource acquisition is initialization|resource acquisition is initialization (RAII)]].

Every object has exactly one destructor The name of the destructor is the same as the name of the class, with a `~` at the start. Destructors never take any input parameters.

If a class does not define a destructor, then C++ may create an implicit destructor for it (that does nothing).

## Example
```cpp
class Printer {
public:
	// default constructor
	Printer() {
		// ... code to turn on printer ...
	}
	
	// destructor
	~Printer() {
		// ... code to turn off printer ...
	}

	// ...
};
```

