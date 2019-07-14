#pragma once

#include <Genesis.h>

using namespace Genesis;
using namespace Genesis::entity;

class TravellerComponentData : public ComponentData
{
	public:
		math::Vector3 PointA;
		math::Vector3 PointB;

		TFloat32 Alpha;

		//Materials to change to based on if collided or not
		std::shared_ptr<render::Material> NonCollidedMat;
		std::shared_ptr<render::Material> CollidedMat;

		TravellerComponentData()
		{
			PointA = math::Vector3::kZero;
			PointB = math::Vector3::kZero;
			Alpha = 0.0f;

			NonCollidedMat = nullptr;
			CollidedMat = nullptr;
		}
		~TravellerComponentData() {}
};