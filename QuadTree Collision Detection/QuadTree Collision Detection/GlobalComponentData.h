#pragma once

#include <Genesis.h>

using namespace Genesis;
using namespace Genesis::entity;

class GlobalComponentData : public ComponentData
{
	public:
		std::shared_ptr<render::GUIBar> GUIBar;
		math::Vector3 MinSpawn;
		math::Vector3 MaxSpawn;

		GlobalComponentData(std::shared_ptr<render::GUIBar> guiBar)
		{
			GUIBar = guiBar;
		}
};