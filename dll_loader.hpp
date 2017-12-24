#pragma once

#include <functional>
#include <stdexcept>

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace dll_loader {
#if defined(_WIN32)
	using library_ptr = HINSTANCE;
#endif
	class dynamic_library;
}


class dll_loader::dynamic_library {
	library_ptr m_lib{ nullptr };
public:
	dynamic_library(const char* path);
	~dynamic_library();

public:
	template<typename function_type>
	std::function<function_type> get_function(const char* name);
};


// WINDOWS IMPLEMENTATION
#if defined(_WIN32)

namespace dll_loader {
	static std::string last_windows_error()
{
	auto errorMessageID = GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	char* messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	auto message = std::string(messageBuffer, size);
	LocalFree(messageBuffer);

	return message;
}

	inline dynamic_library::dynamic_library(const char* path) {
		m_lib = LoadLibraryA(path);
		if (m_lib == nullptr) {
			throw std::runtime_error("Library loading failed: " + last_windows_error());
		}
	}


	template<typename function_type>
	inline std::function<function_type> dynamic_library::get_function(const char* name)
	{
		auto function_address = (function_type*)GetProcAddress(m_lib, name);

		if (function_address != nullptr)
		{
			return std::function<function_type>(function_address);
		}
		throw std::runtime_error("Retrieving the functionpointer failed: " + last_windows_error());
	}

	inline dynamic_library::~dynamic_library() {
		FreeLibrary(m_lib);
	}
}

// END OF WINDOWS IMPLEMENTATION

#else
#error This platform is not supported.

#endif