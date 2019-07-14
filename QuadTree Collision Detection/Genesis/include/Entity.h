#pragma once

#include "Components\ComponentData.h"
#include "Math\Transform.h"
#include "Defines.h"

namespace Genesis
{
	namespace entity
	{
		struct Entity
		{
			public:
				TEntityUID UID;

				Entity() { UID = 0; }
				Entity(const TEntityUID& uid) { UID = uid; }
		};
	}
}