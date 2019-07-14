#pragma once

#include "ComponentData.h"
#include "..\Render\ParticleSystem.h"
#include <memory>

namespace Genesis
{
	namespace entity
	{
		class ParticleSystemComponentData : public ComponentData
		{
			private:
				std::shared_ptr<render::ParticleSystem> mp_ParticleSystem;

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				ParticleSystemComponentData(std::shared_ptr<render::ParticleSystem>);

				virtual ~ParticleSystemComponentData();

				//------------------------------


				//ACCESSORS
				//------------------------------

				render::ParticleSystem* GetParticleSystem();

				//------------------------------
		};
	}
}