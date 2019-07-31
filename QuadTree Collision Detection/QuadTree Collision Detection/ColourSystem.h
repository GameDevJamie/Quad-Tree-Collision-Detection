#pragma once

#include <Genesis.h>
#include "GlobalComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class ColourSystem : public WorldSystem
{
	private:
		std::shared_ptr<render::Material> mp_CollidedMat;
		std::shared_ptr<render::Material> mp_NonCollidedMat;

		math::Vector3 mp_CollidedMatColour;
		math::Vector3 mp_NonCollidedMatColour;

	public:
		ColourSystem() {}
		~ColourSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			mp_CollidedMat = world.GetRenderer()->LoadMaterial("CollidedMat");
			mp_NonCollidedMat = world.GetRenderer()->LoadMaterial("NonCollidedMat");

			mp_CollidedMatColour = mp_CollidedMat->GetDiffuseColour();
			mp_NonCollidedMatColour = mp_NonCollidedMat->GetDiffuseColour();

			auto guiBar = world.GetEntityManager()->GetComponent<GlobalComponentData>()->GetGUIBar();
			guiBar->AddVarRW("Non Collided Colour", EType::COLOR3, &mp_NonCollidedMatColour, "group=Colour");
			guiBar->AddVarRW("Collided Colour", EType::COLOR3, &mp_CollidedMatColour, "group=Colour");
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			mp_CollidedMat->SetDiffuseColour(mp_CollidedMatColour);
			mp_NonCollidedMat->SetDiffuseColour(mp_NonCollidedMatColour);
		}
};