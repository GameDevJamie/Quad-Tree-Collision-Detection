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
			private:
				render::ELightType m_LightType;

				math::Vector3 m_Colour;			//Colour of point light
				TFloat32 m_Brightness;			//How bright is the light
				

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				LightComponentData
				(
					const math::Vector3& colour = math::Vector3::kWhite,
					TFloat32 brightness = 10.0f
				);

				virtual ~LightComponentData();

				//------------------------------


				//ACCESSORS
				//------------------------------

				math::Vector3 GetColour();
				TFloat32 GetBrightness();

				//------------------------------


				//MUTATORS
				//--------------------------------
				void SetColour(const math::Vector3&);
				void SetBrightness(const TFloat32&);
				//--------------------------------
		};
	}
}