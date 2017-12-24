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