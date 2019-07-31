#pragma once

#include <Genesis.h>
#include "GlobalComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class FloorSystem : public WorldSystem
{
	private:
		std::shared_ptr<GlobalComponentData> mp_GlobalData;
		Entity m_FloorEntity;

		TFloat32 m_CurrentFloorSize;

	public:
		FloorSystem() {}
		~FloorSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			m_CurrentFloorSize = 100.0f;

			EntityManager* EntityManager = world.GetEntityManager();

			mp_GlobalData = world.GetEntityManager()->GetComponent<GlobalComponentData>();
			mp_GlobalData->GetGUIBar()->AddVarRW("Floor Size", EType::FLOAT, &m_CurrentFloorSize, "group='Other' min=10 max=100");

			mp_GlobalData->SetSize(m_CurrentFloorSize);

			//Create Floor Entity
			m_FloorEntity = EntityManager->CreateEntity();
			EntityManager->AddComponent<TransformComponentData>(m_FloorEntity, math::Vector3(0.0f, -0.1f, 0.0f), math::Quaternion::Euler(90.0f, 0.0f, 0.0f), math::Vector3::kOne * m_CurrentFloorSize);
			EntityManager->AddComponent<StaticMeshComponentData>(m_FloorEntity, world.GetRenderer()->LoadMesh(render::EMeshPrimitiveTypes::SQUARE))->SetCustomMaterial(0, world.GetRenderer()->LoadMaterial("FloorMat"));
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			//Update Floor Size
			world.GetEntityManager()->GetComponent<TransformComponentData>(m_FloorEntity)->GetTransform().SetScale(math::Vector3::kOne * m_CurrentFloorSize);

			//Update Quad Tree Size
			mp_GlobalData->SetSize(m_CurrentFloorSize);
		}
};