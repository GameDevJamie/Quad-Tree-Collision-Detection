#pragma once

#include <Genesis.h>
#include "TravellerComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class CollisionSystem : public WorldSystem
{
	private:
		EntityList m_Entities;

	public:
		CollisionSystem() {}
		~CollisionSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			ComponentGroup group;
			group.AddFilter<StaticMeshComponentData>();
			group.AddFilter<TravellerComponentData>();

			m_Entities = world.GetEntityManager()->GetEntities(group);
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			ComponentGroup group;
			group.AddFilter<StaticMeshComponentData>();
			group.AddFilter<TravellerComponentData>();

			m_Entities = world.GetEntityManager()->GetEntities(group);
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			//ProcessNormalCollisions(world);
		}

	private:
		//Checks for a collision with any entity any where on the map (Inefficient)
		void ProcessNormalCollisions(const World& world)
		{
			EntityManager* EntityManager = world.GetEntityManager();

			for (int i = 0; i < m_Entities.size(); ++i)
			{
				//Entity to check for collisions with another Traveller
				Entity entity1 = m_Entities[i];
				auto transformComp = EntityManager->GetComponent<TransformComponentData>(entity1);
				auto travellerComp = EntityManager->GetComponent<TravellerComponentData>(entity1);
				auto meshComp = EntityManager->GetComponent<StaticMeshComponentData>(entity1);


				bool collided = false;

				for (int j = 1; j < m_Entities.size(); ++j)
				{
					if (j == i) continue;

					Entity entity2 = m_Entities[j];
					auto transformComp2 = EntityManager->GetComponent<TransformComponentData>(entity2);

					//Check if collided (If forget why boxSize is 2.0f instead of 1.0f, look at AABB struct, divides it by 2)
					if (math::BoxToBoxCollision(transformComp->GetTransform().GetPosition(), 2.0f, transformComp2->GetTransform().GetPosition(), 2.0f))
					{
						collided = true;
						break;
					}
				}

				if (collided)
				{
					meshComp->SetCustomMaterial(0, travellerComp->CollidedMat);
				}
				else meshComp->SetCustomMaterial(0, travellerComp->NonCollidedMat);
			}
		}
};