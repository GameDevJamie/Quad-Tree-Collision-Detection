#pragma once

#include "Vector2.h"
#include "Matrix4x4.h"

namespace Genesis
{
	namespace math
	{
		class MousePicker
		{
			private:
				Matrix4x4 m_ViewMatrix;
				Matrix4x4 m_ProjectionMatrix;

			private:
				//HELPER FUNCTIONS
				//------------------------

				Vector2 GetNormalisedDeviceCoords(const TFloat32& mouseX, const TFloat32& mouseY, const TFloat32& screenWidth, const TFloat32& screenHeight);
				Vector4 ToEyeCoords(const Vector4& clipCoords);
				Vector3 ToWorldCoords(const Vector4& eyeCoords);

				//------------------------

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//--------------------------

				MousePicker();

				~MousePicker();

				//--------------------------

				//Calculate where the ray is pointing, based on the given view and projection matrix
				//Returns the direction vector of the ray
				Vector3 CalculateMouseRay(const Vector2& mousePos, const TFloat32& screenWidth, const TFloat32& screenHeight, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
				{
					m_ViewMatrix = viewMatrix;
					m_ProjectionMatrix = projectionMatrix;

					TFloat32 mouseX = mousePos.x;
					TFloat32 mouseY = mousePos.y;

					Vector2 normalisedCoords = GetNormalisedDeviceCoords(mouseX, mouseY, screenWidth, screenHeight);
					Vector4 clipCoords = Vector4(normalisedCoords.x, normalisedCoords.y, -1.0f, 1.0f);
					Vector4 eyeCoords = ToEyeCoords(clipCoords);
					Vector3 worldRay = ToWorldCoords(eyeCoords);
					
					return worldRay;
				}
		};
	}
}