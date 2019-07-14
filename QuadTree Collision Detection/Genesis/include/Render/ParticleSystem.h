/**********************************
	ParticleSystem.h

	* Particle System Interface. Object can be created via the Render Engine.

	* Each Particle System contains a number of Particle Emitters, which emit different types of particles
	* For Example, a Fire Particle System may have two emitters. One emitter would emit fire particles, while a second emitter would emit smoke particles

	* Common to just use one Emitter for a particle System.

***********************************/

#pragma once

#include "ParticleEmitter.h"

#include <memory>

namespace Genesis
{
	namespace render
	{
		class ParticleSystem
		{
			public:
				virtual ~ParticleSystem() {}


				//ACCESSORS
				//--------------------------------

				//Return the number of Emitters that this particle system currently uses
				virtual inline TInt32 GetEmitterCount() const = 0;

				virtual ParticleEmitter* GetEmitterByIndex(const TInt32&) const = 0;

				//--------------------------------


				virtual ParticleEmitter* AddEmitter(const TInt32& maxParticles, std::shared_ptr<Material> material = nullptr) = 0;
				virtual bool DestroyEmitterByIndex(const TInt32&) = 0;
				virtual void DestroyAllEmitters() = 0;

				//Update all Particle Emitters attached to Particle System
				virtual bool Update(const TFloat32& deltaTime, const math::Matrix4x4& worldMatrix) = 0;
		};
	}
}