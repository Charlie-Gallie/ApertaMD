#pragma once
#ifndef AMD_UI_LAYER
#define AMD_UI_LAYER

#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Layer
{
public:
	virtual Status OnCreate() { return Status::SUCCESS; }
	virtual Status OnUpdate() { return Status::SUCCESS; }
	virtual Status OnDestroy() { return Status::SUCCESS; }

protected:
	Layer() = default;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_UI_LAYER