#include "UI.hpp"

#include "UI/Layers/TestLayer.hpp"

AMD_NAMESPACE_BEGIN

UI::~UI()
{
	for (Layer* layer : layers)
	{
		delete layer;
	}

	layers.clear();
}

Status UI::Initialize()
{
	AddLayer<TestLayer>();

	return Status::SUCCESS;
}

Status UI::Update()
{
	for (Layer* layer : layers)
	{
		layer->OnUpdate();
	}

	return Status::SUCCESS;
}

AMD_NAMESPACE_END