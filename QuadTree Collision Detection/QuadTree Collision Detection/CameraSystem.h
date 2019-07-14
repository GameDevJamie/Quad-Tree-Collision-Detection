#pragma once

#include <Genesis.h>
#include "GlobalComponentData.h"

using namespace Genesis;
using namespace Genesis::entity;

class CameraSystem : public WorldSystem
{
	private:
		TFloat32 m_MoveSpeed;	//Movement Speed of camera
		bool m_BirdEyeMode;		//TRUE = Camera is in Top Down View and cannot move
		bool m_ResetPosition;

		EntityList m_Entities;

	public:
		CameraSystem() {}
		~CameraSystem() {}

		//Called when the System is created/Initialised
		virtual void Start(const World& world)
		{
			m_MoveSpeed = 10.0f;
			m_BirdEyeMode = 1;
			m_ResetPosition = false;

			//Get Active Camera Entity
			ComponentGroup group;
			group.AddFilter<TransformComponentData>();
			group.AddFilter<CameraComponentData>();
			m_Entities = world.GetEntityManager()->GetEntities(group);

			//Add Camera data to GUI Bar
			auto globalData = world.GetEntityManager()->GetComponent<GlobalComponentData>();
			globalData->GUIBar->AddVarRW("Camera Speed", EType::FLOAT, &m_MoveSpeed, "group='Camera'");
			globalData->GUIBar->AddVarRW("Bird Eye Mode", EType::BOOL, &m_BirdEyeMode, "group='Camera'");
		}

		//Called when there has been a change to the world (New Entity/Component created/destroyed)
		virtual void OnWorldChange(const World& world)
		{
			
		}

		//Called when the System is Updated (Per Frame)
		virtual void Update(const World& world, TFloat32 deltaTime)
		{
			if (m_BirdEyeMode)
			{
				//Reset Position if needed
				if (m_ResetPosition)
				{
					ResetCamera(world);
					m_ResetPosition = false;
				}

				return;
			}

			m_ResetPosition = true;

			//Move Camera
			Entity entity = m_Entities[0];
			auto transformComp = world.GetEntityManager()->GetComponent<TransformComponentData>(entity);

			//FORWARD/BACK
			if (input::IsKeyHeld(input::EKeyCode::KEY_W)) transformComp->GetTransform().Translate(m_MoveSpeed * deltaTime, math::EAxis::Z, math::ESpace::LOCAL);
			else if (input::IsKeyHeld(input::EKeyCode::KEY_S)) transformComp->GetTransform().Translate(-m_MoveSpeed * deltaTime, math::EAxis::Z, math::ESpace::LOCAL);

			//LEFT/RIGHT
			if (input::IsKeyHeld(input::EKeyCode::KEY_A)) transformComp->GetTransform().Translate(-m_MoveSpeed * deltaTime, math::EAxis::X, math::ESpace::LOCAL);
			else if (input::IsKeyHeld(input::EKeyCode::KEY_D)) transformComp->GetTransform().Translate(m_MoveSpeed * deltaTime, math::EAxis::X, math::ESpace::LOCAL);
		}

	private:
		void ResetCamera(const World& world)
		{
			Entity cameraEntity = m_Entities[0];

			auto transComp = world.GetEntityManager()->GetComponent<TransformComponentData>(cameraEntity);
			transComp->GetTransform().SetPosition(math::Vector3::kYAxis * 100.0f);
			transComp->GetTransform().SetRotation(math::Quaternion::Euler(90.0f, 0.0f, 0.0f));
		}
};