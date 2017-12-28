# dll_loader
A single-header library to take away the pain of loading a dynamically linked library. Crossplatform!
Disclaimer: I don't consider it production-ready, it is not tested very heavily and it lacks some features.

## Installation

Just download the headerfile, add it to your project directory and include it. That's all!

## Usage

Simple example usage to get started:

```cpp
#include "dll_loader.hpp"
#include <iostream>

int main() {
  // Load the library with the name 'testdll'
  auto lib = dll_loader::dynamic_library("testdll");

  // Get a function from the library named 'get_one', 
  // which takes no parameters and returns an integer.
  auto get_one = lib.get_function<int()>("get_one");

  // Get a function from the library named 'get_a_string',
  // Which takes not parameters and returns a const char*.
  auto get_a_string = lib.get_function<const char*()>("get_a_string");

  // We can just call these functions now:
  std::cout << get_one() << std::endl;

  std::cin.get();
}
```

## Support

Please [open an issue](https://github.com/Xoronic/dll_loader/issues/new) for support.

## Contributing

Create a branch, add commits, and [open a pull request](https://github.com/Xoronic/dll_loader/compare/).
