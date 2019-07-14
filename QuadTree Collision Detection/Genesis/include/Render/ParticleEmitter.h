/**********************************
	ParticleEmitter.h

	* Particle Emitter Interface. Object is created via the Particle System

	*	A Particle Emitter controls all the particles, updating their positions and current life time
	*	Each emitter will contain a material to render the particles
	*	Use the Material to give each particle a texture, and determine which shader to use to render them
	* Each Particle is just a point and will need a Geometry Shader to construct a Quad for the particle

***********************************/

#pragma once

#include "..\Defines.h"
#include "Drawable.h"
#include "Material.h"

#include "..\Math\Vector3.h"
#include "..\Math\Matrix4x4.h"

#include <vector>

namespace Genesis
{
	namespace render
	{
		class ParticleEmitter : public Drawable
		{
			public:
				virtual ~ParticleEmitter() {}


				//ACCESSORS
				//-------------------------------

				//Get the number of particles that can be emitted per second
				virtual inline TInt32 GetEmissionRate() const = 0;

				//Returns the maximum number of particles the emitter is allowed active
				virtual inline TInt32 GetMaxParticles() const = 0;

				//Returns the current number of particles currently alive
				virtual inline TInt32 GetParticleCount() const = 0;

				//Returns how long each particle can exist for
				virtual inline TFloat32 GetParticleLife() const = 0;

				//Get the colour that each particle will be set too
				virtual inline math::Vector3 GetParticleColour() const = 0;

				//-------------------------------


				//MUTATORS
				//-------------------------------

				//Set the number of particles that can be emitted per second
				virtual inline void SetEmissionRate(const TInt32&) = 0;

				//Set how long each particle can exist for
				virtual inline void SetParticleLife(const TFloat32&) = 0;

				//Set the maximum number of particles the emitter is allowed active
				virtual inline void SetMaxParticles(const TInt32&) = 0;

				//Set the sphere radius of how far the particle's can spawn from the emitter's position (Local Space)
				virtual inline void SetRadius(const TFloat32&) = 0;

				//Set the Colour for each new particle
				virtual inline void SetParticleColour(const math::Vector3&) = 0;

				//-------------------------------
		};
	}
}