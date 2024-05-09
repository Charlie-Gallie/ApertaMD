#pragma once
#ifndef AMD_WINDOW_WINDOW
#define AMD_WINDOW_WINDOW

#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Window
{
public:
	static inline Window& GetInstance()
	{
		static Window instance;
		return instance;
	}



private:
	Window() = default;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_WINDOW_WINDOW