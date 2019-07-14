#pragma once

#include "ComponentData.h"
#include "..\Math\Transform.h"

#include <memory>
#include <vector>

namespace Genesis
{
	namespace entity
	{
		class TransformComponentData : public ComponentData
		{
			private:
				std::unique_ptr<math::Transform> mp_Transform;

		public:
			//CONSTRUCTOR/DESTRUCTOR
			//------------------------------

			TransformComponentData
			(
				const math::Vector3 position = math::Vector3::kZero,
				const math::Quaternion rotation = math::Quaternion::kIdentity,
				const math::Vector3 scale = math::Vector3::kOne
			)
			{
				mp_Transform = std::make_unique<math::Transform>(position, rotation, scale);
			}

			virtual ~TransformComponentData() { mp_Transform.reset(nullptr); }

			//------------------------------


			//ACCESSORS
			//------------------------------

			math::Transform& GetTransform() { return (*mp_Transform); }

			//------------------------------
		};
	}
}