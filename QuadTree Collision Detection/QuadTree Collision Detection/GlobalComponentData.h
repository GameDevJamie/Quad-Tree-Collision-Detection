#pragma once

#include <Genesis.h>

using namespace Genesis;
using namespace Genesis::entity;

class GlobalComponentData : public ComponentData
{
	public:
		std::shared_ptr<render::GUIBar> GUIBar;
		std::unique_ptr<math::QuadTree<TEntityUID>> QuadTree;
		math::Vector3 MinSpawn;
		math::Vector3 MaxSpawn;

		GlobalComponentData(std::shared_ptr<render::GUIBar> guiBar)
		{
			GUIBar = guiBar;
			QuadTree = std::make_unique<math::QuadTree<TEntityUID>>(math::Vector2::kZero, 50.0f * 2.0f, 8, 5);
		}
};