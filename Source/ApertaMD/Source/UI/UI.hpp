#pragma once
#ifndef AMD_UI_UI
#define AMD_UI_UI

#include <deque>
#include <type_traits>
#include <utility>

#include "ErrorHandling/ErrorHandling.hpp"
#include "UI/Layer.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class UI
{
public:
	~UI();

	static inline UI& GetInstance()
	{
		static UI instance;
		return instance;
	}

	Status Initialize();
	Status Update();

	template<typename LayerType, typename ... Arguments>
	Status AddLayer(Arguments&& ... arguments)
	{
		static_assert(std::is_base_of<Layer, LayerType>::value, "LayerType must derive from Layer");

		layers.push_back(new LayerType(std::forward<Arguments>(arguments)...));
		layers.back()->OnCreate();

		return Status::SUCCESS;
	}

	template<typename LayerType>
	LayerType* GetLayer()
	{
		static_assert(std::is_base_of<Layer, LayerType>::value, "LayerType must derive from Layer");

		for (Layer* layer : layers)
		{
			if (auto layerPointer = dynamic_cast<LayerType*>(layer))
			{
				return layerPointer;
			}
		}

		return nullptr;
	}

private:
	std::deque<Layer*> layers;

	UI() = default;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_UI_UI