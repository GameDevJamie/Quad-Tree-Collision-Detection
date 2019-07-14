#pragma once

#include <Genesis.h>
#include "GlobalComponentData.h"
#include "TravellerComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class MovementSystem : public WorldSystem
{
	private:
		std::shared_ptr<GlobalComponentData> mp_GlobalData;
		EntityList m_Entities;
		TFloat32 m_MoveSpeed;

		bool m_Paused;

	public:
		MovementSystem() {}
		~MovementSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			m_MoveSpeed = 5.0f;
			m_Paused = false;

			ComponentGroup group;
			group.AddFilter<TransformComponentData>();
			group.AddFilter<TravellerComponentData>();

			m_Entities = world.GetEntityManager()->GetEntities(group);

			//Setup GUI Data for Movement
			mp_GlobalData = world.GetEntityManager()->GetComponent<GlobalComponentData>();
			mp_GlobalData->GUIBar->AddVarRW("Move Speed", EType::FLOAT, &m_MoveSpeed, "group='Travellers' min=1 max=20");
			mp_GlobalData->GUIBar->AddVarRW("Pause", EType::BOOL, &m_Paused, "group='Travellers'");
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			ComponentGroup group;
			group.AddFilter<TransformComponentData>();
			group.AddFilter<TravellerComponentData>();

			m_Entities = world.GetEntityManager()->GetEntities(group);
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			if (m_Paused) return;

			for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
			{
				Entity entity = (*it);
				auto transComp = world.GetEntityManager()->GetComponent<TransformComponentData>(entity);
				auto travellerData = world.GetEntityManager()->GetComponent<TravellerComponentData>(entity);

				travellerData->Alpha += (deltaTime * (m_MoveSpeed / 10.0f));
				math::Vector3 newPos = math::Lerp(travellerData->PointA, travellerData->PointB, travellerData->Alpha);

				transComp->GetTransform().SetPosition(newPos);

				if (travellerData->Alpha >= 1.0f)
				{
					//Select a new random position for the Traveller to move to
					travellerData->PointA = travellerData->PointB;
					transComp->GetTransform().SetPosition(travellerData->PointA);

					math::Vector3 minSpawn = mp_GlobalData->MinSpawn;
					math::Vector3 maxSpawn = mp_GlobalData->MaxSpawn;
					travellerData->PointB = math::Random(minSpawn, maxSpawn);

					travellerData->Alpha = 0.0f;
				}
			}
		}
};