#pragma once

#include <Genesis.h>
#include "TravellerComponentData.h"
#include "GlobalComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class QuadTreeBuilderSystem : public WorldSystem
{
	private:
		Entity m_TerrainEntity;
		EntityList m_Entities;

		TInt32 m_MaxLayers;	//Max Number of Layers the Quad Tree can contain

		bool m_Draw;	//TRUE = Render the Quad Tree

	public:
		QuadTreeBuilderSystem() {}
		~QuadTreeBuilderSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			m_TerrainEntity = world.GetEntityManager()->CreateEntity();
			world.GetEntityManager()->AddComponent<TransformComponentData>(m_TerrainEntity);
			world.GetEntityManager()->AddComponent<TerrainGridComponentData>(m_TerrainEntity, world.GetRenderer()->CreateTerrainGrid(0, 0, 1))->GetTerrain()->GetMaterial()->SetDiffuseColour(math::Vector3::kBlack);

			m_Draw = true;

			auto globalData = world.GetEntityManager()->GetComponent<GlobalComponentData>();
			globalData->GUIBar->AddVarRW("Max Layers", EType::INT32, &m_MaxLayers, "group='Quad Tree Data'");
			globalData->GUIBar->AddVarRW("Draw Tree", EType::BOOL, &m_Draw, "group='Quad Tree Data'");

			ComponentGroup group;
			group.AddFilter<TravellerComponentData>();

			m_Entities = world.GetEntityManager()->GetEntities(group);
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
			auto qTree = world.GetEntityManager()->GetComponent<GlobalComponentData>()->QuadTree.get();

			//Clear QuadTree
			qTree->Reset();

			//Update QuadTree
			for(auto it = m_Entities.begin(); it < m_Entities.end(); it++)
			{
				Entity entity = (*it);

				auto pos = world.GetEntityManager()->GetComponent<TransformComponentData>(entity)->GetTransform().GetPosition();
				qTree->Insert(math::SQuadTreeNode<TEntityUID>(entity.UID, math::Vector2(pos.x, pos.z)));
			}

			if (m_Draw)
			{
				auto terrainComp = world.GetEntityManager()->GetComponent<TerrainGridComponentData>(m_TerrainEntity);
				
				terrainComp->GetTerrain()->IsVisible(true);
				terrainComp->GetTerrain()->UpdateGrid(qTree);
			}
			else
			{
				auto terrainComp = world.GetEntityManager()->GetComponent<TerrainGridComponentData>(m_TerrainEntity);
				terrainComp->GetTerrain()->IsVisible(false);
			}
		}
};