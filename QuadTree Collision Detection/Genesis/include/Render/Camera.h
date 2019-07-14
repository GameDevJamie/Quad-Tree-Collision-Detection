#pragma once

/*
	SUMMARY:
	-A camera class interface, to control where the scene is rendered from. Used in conjunction with the CameraComponent
	-Contains a View and Projection matrix.
	-Does not contain a World Matrix, as that is held within a seperate component within the Entity
*/

#include "..\Defines.h"
#include "..\Math\Vector2.h"
#include "..\Math\Matrix4x4.h"

namespace Genesis
{
	namespace render
	{
		enum class ECameraProjectionMode
		{
			PERSPECTIVE,	//Camera uses a Perspective Matrix to Render Objects (3D Rendering)
			ORTHOGRAPHIC	//Camera uses an Orthographic Matrix to Render objects (2D Rendering, Sprites, etc.)
		};

		class Camera
		{
			public:
				virtual ~Camera() {}

				//MUTATORS
				//-----------------------------

				//Set which Projection Matrix to use when rendering
				virtual void SetCameraMode(const ECameraProjectionMode&) = 0;

				virtual void SetNearClip(const TFloat32&) = 0;
				virtual void SetFarClip(const TFloat32&) = 0;
				virtual void SetFOV(const TFloat32&) = 0;

				virtual void SetActive(bool active) = 0;

				//-----------------------------

				
				//ACCESSORS
				//-------------------------------

				virtual ECameraProjectionMode GetCameraMode() const = 0;

				virtual TFloat32 GetNearClip() const = 0;
				virtual TFloat32 GetFarClip() const = 0;
				virtual TFloat32 GetFOV() const = 0;

				virtual math::Matrix4x4 GetViewMatrix() const = 0;
				virtual math::Matrix4x4 GetProjectionMatrix() const = 0;
				virtual math::Matrix4x4 GetViewProjMatrix() const = 0;

				virtual bool IsActive() const = 0;

				//-------------------------------

				//Returns a Ray in world space, using the given screen co-ordinates
				//The resulting Vector is the direction of the Ray
				virtual math::Vector3 GetRay(const math::Vector2& pixelPos) = 0;

				//Update the Camera's matrices using the given World Matrix
				virtual void Update(const math::Matrix4x4& worldMatrix) = 0;
		};
	}
}