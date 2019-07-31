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
			mp_GlobalData->GetGUIBar()->AddVarRW("Spawned", EType::INT32, &m_NumEntities, "group='Travellers' min=0 max=1000 keyincr== keydecr=-");
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
			//Spawn by mouse click
			if (input::IsKeyHeld(input::EKeyCode::MOUSE_LBTN))
			{
				auto cameraComp = world.GetEntityManager()->GetComponent<CameraComponentData>();
				auto ray = cameraComp->GetCamera()->GetRay(input::MousePosition());

				auto cameraPos = math::Vector3::kYAxis * 190.0f;

				auto spawnPos = FindFloorPoint(ray, cameraPos);
				spawnPos.y = 0.0f;

				SpawnTravellerEntity(world, spawnPos);

				m_NumEntities++;
				m_CurrentSpawned++;
				return;
			}

			TInt32 toSpawn = m_NumEntities - m_CurrentSpawned;
			if (toSpawn == 0) return;	//No New Entities need spawning

			if (toSpawn > 0)
			{
				//Spawn Entities
				for (int i = 0; i < toSpawn; ++i)
				{
					//Randomise Position
					math::Vector3 randomPos = math::Random(mp_GlobalData->GetMinSpawn(), mp_GlobalData->GetMaxSpawn());

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
			EntityManager->AddComponent<StaticMeshComponentData>(entity, world.GetRenderer()->LoadMesh(render::EMeshPrimitiveTypes::CUBE))->SetCustomMaterial(0, world.GetRenderer()->LoadMaterial("NonCollidedMat"));
			
			auto travellerData = EntityManager->AddComponent<TravellerComponentData>(entity);
			travellerData->PointA = pos;
			travellerData->PointB = math::Random(mp_GlobalData->GetMinSpawn(), mp_GlobalData->GetMaxSpawn());

			travellerData->NonCollidedMat = world.GetRenderer()->LoadMaterial("NonCollidedMat");
			travellerData->CollidedMat = world.GetRenderer()->LoadMaterial("CollidedMat");

			//Point Light to shine when collided
			EntityManager->AddComponent<LightComponentData>(entity, render::ELightType::POINT);
		}

		//Find Point where Ray intersects with Ground (y = 0)
		math::Vector3 FindFloorPoint(const math::Vector3& ray, const math::Vector3& cameraPos)
		{
			if (ray.y > 0.0f) return math::Vector3::kZero;
			TFloat32 distance = BinarySearch(0, 0, 1000, ray, cameraPos);
			return cameraPos + (ray * distance);
		}

		//Get Ray Distance Multiplier
		TFloat32 BinarySearch(int count, const TFloat32& start, const TFloat32& finish, const math::Vector3& ray, const math::Vector3& cameraPos)
		{
			TFloat32 half = start + ((finish - start) / 2.0f);
			if (count >= 100)
			{
				return half;
			}

			math::Vector3 scaledRay = cameraPos + (ray * half);
			if (scaledRay.y > 0.0f) return BinarySearch(count + 1, half, finish, ray, cameraPos);
			else return BinarySearch(count + 1, start, half, ray, cameraPos);
		}
};