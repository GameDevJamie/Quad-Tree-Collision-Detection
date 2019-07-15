#pragma once

#include <Genesis.h>
#include "GlobalComponentData.h"
#include "TravellerComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class SpawnerSystem : public WorldSystem
{
	private:
		std::shared_ptr<GlobalComponentData> mp_GlobalData;
		EntityList m_Entities;

		TInt32 m_NumEntities;			//Number of Traveller Entities that should be active
		TInt32 m_CurrentSpawned;	//Number of Traveller Entities currently Spawned

	public:
		SpawnerSystem() {}
		~SpawnerSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			m_NumEntities = 0;

			ComponentGroup group;
			group.AddFilter<TravellerComponentData>();
			m_Entities = world.GetEntityManager()->GetEntities(group);
			
			m_CurrentSpawned = m_Entities.size();
			
			//Setup GUI Data
			mp_GlobalData = world.GetEntityManager()->GetComponent<GlobalComponentData>();
			mp_GlobalData->GUIBar->AddVarRW("Spawned", EType::INT32, &m_NumEntities, "group='Travellers' min=0 max=1000 keyincr== keydecr=-");
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			ComponentGroup group;
			group.AddFilter<TravellerComponentData>();
			m_Entities = world.GetEntityManager()->GetEntities(group);
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			TInt32 toSpawn = m_NumEntities - m_CurrentSpawned;
			if (toSpawn == 0) return;	//No New Entities need spawning

			if (toSpawn > 0)
			{
				//Spawn Entities
				for (int i = 0; i < toSpawn; ++i)
				{
					//Randomise Position
					math::Vector3 minSpawn = mp_GlobalData->MinSpawn;
					math::Vector3 maxSpawn = mp_GlobalData->MaxSpawn;
					math::Vector3 randomPos = math::Random(minSpawn, maxSpawn);

					SpawnTravellerEntity(world, randomPos);

					m_CurrentSpawned++;
				}
			}
			else
			{
				//Destroy Entities
				auto it = m_Entities.begin();
				while (toSpawn != 0)
				{
					world.GetEntityManager()->DestroyEntity((*it));
					it++;

					m_CurrentSpawned--;
					toSpawn++;
				}
			}
		}

	private:
		void SpawnTravellerEntity(const World& world, const math::Vector3& pos)
		{
			EntityManager* EntityManager = world.GetEntityManager();

			Entity entity = EntityManager->CreateEntity();
			EntityManager->AddComponent<TransformComponentData>(entity, pos);
			EntityManager->AddComponent<StaticMeshComponentData>(entity, world.GetRenderer()->LoadMesh(render::EMeshPrimitiveTypes::SPHERE))->SetCustomMaterial(0, world.GetRenderer()->LoadMaterial("NonCollidedMat"));
			
			auto travellerData = EntityManager->AddComponent<TravellerComponentData>(entity);
			travellerData->PointA = pos;
			
			math::Vector3 minSpawn = mp_GlobalData->MinSpawn;
			math::Vector3 maxSpawn = mp_GlobalData->MaxSpawn;
			travellerData->PointB = math::Random(minSpawn, maxSpawn);

			travellerData->NonCollidedMat = world.GetRenderer()->LoadMaterial("NonCollidedMat");
			travellerData->CollidedMat = world.GetRenderer()->LoadMaterial("CollidedMat");
		}
};