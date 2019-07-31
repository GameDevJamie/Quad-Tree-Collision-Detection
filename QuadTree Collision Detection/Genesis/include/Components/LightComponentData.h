#pragma once

#include "ComponentData.h"
#include "..\Math\Vector3.h"
#include "..\Render\LightTypes.h"

namespace Genesis
{
	namespace entity
	{
		class LightComponentData : public ComponentData
		{
			public:
				render::ELightType LightType;

				math::Vector3 Colour;			//Colour of point light
				math::Vector3 Direction;	//Direction the light is facing (For Spot and Directional lights)

				TFloat32 Brightness;			//How bright is the light
			

				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				LightComponentData
				(
					const render::ELightType& lightType,
					const math::Vector3& colour = math::Vector3::kWhite,
					TFloat32 brightness = 10.0f
				)
				{
					LightType = lightType;
					Colour = colour;
					Direction = math::Vector3::kZero;
					Brightness = brightness;
				}

				~LightComponentData() {}
		};
	}
}