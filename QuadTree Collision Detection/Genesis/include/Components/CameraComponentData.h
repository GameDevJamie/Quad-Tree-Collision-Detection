#pragma once

#include "ComponentData.h"
#include "..\Render\Camera.h"

#include <memory>

namespace Genesis
{
	namespace entity
	{
		class CameraComponentData : public ComponentData
		{
			private:
				std::unique_ptr<render::Camera> mp_Camera;

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				CameraComponentData
				(
					const render::ECameraProjectionMode& mode = render::ECameraProjectionMode::PERSPECTIVE,
					const TFloat32& nearClip = 0.1f,
					const TFloat32& farClip = 1000.0f,
					const TFloat32& fov = 60.0f
				);

				virtual ~CameraComponentData();

				//------------------------------


				//ACCESSORS
				//------------------------------

				render::Camera* GetCamera();

				//------------------------------
		};
	}
}