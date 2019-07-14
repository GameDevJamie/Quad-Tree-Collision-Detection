#pragma once

/**********************************
	WorldSystem.h

	* The "System" in Entity Component Systems

	* World Systems are what define how the World works
	* Each System controls the data in Entity Components
	* All new Systems should inherit from this class

***********************************/

#include "Defines.h"

namespace Genesis
{
	namespace entity
	{
		class World;

		class WorldSystem
		{
			public:
					//Called when the System is created/Initialised
					virtual void Start(const World&) = 0;

					//Called when there has been a change to the world (New Entity/Component created/destroyed)
					virtual void OnWorldChange(const World&) = 0;

					//Called when the System is Updated (Per Frame)
					virtual void Update(const World&, TFloat32 deltaTime) = 0;
		};
	}
}