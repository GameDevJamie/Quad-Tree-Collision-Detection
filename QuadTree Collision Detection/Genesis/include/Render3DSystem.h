#pragma once

#include "World.h"
#include "Defines.h"

namespace Genesis
{
	namespace entity
	{
		class Render3DSystem : public WorldSystem
		{
			public:
				//CONSTRUCTOR / DESTRUCTOR
				//----------------------------

				Render3DSystem();
				virtual ~Render3DSystem();

				//----------------------------


				//FUNCTIONS TO OVERRIDE
				//-----------------------------------

				//Called when the System is created/Initialised
				virtual void Start(const World&);

				//Called when there has been a change to the world (New Entity/Component created/destroyed)
				virtual void OnWorldChange(const World&);

				//Called when the System is Updated
				virtual void Update(const World&, TFloat32 deltaTime);

				//-----------------------------------

			private:
				struct SGroup
				{
					ComponentGroup group;
					EntityList entities;
				};

				SGroup m_CameraGroup;
				SGroup m_MeshGroup;
				SGroup m_TerrainGroup;
		};
	}
}