/**********************************
	Drawable.h

	* Any object that can be rendered will be derived from this class
	* Used by the Render Engine when rendering objects
	* Helps control what should be rendered based on the Project

***********************************/


#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

namespace Genesis
{
	namespace render
	{
		class Drawable
		{
			private:
				std::shared_ptr<Material> mp_Material;
				bool m_IsVisible;

			public:
				//Constructor/Destructor
				//----------------------------

				Drawable();
				virtual ~Drawable();

				//----------------------------


				//ACCESSORS
				//------------------------------

				bool IsVisible() const;
				std::shared_ptr<Material> GetMaterial() const;

				virtual inline VertexBuffer* GetVertexBuffer() const = 0;
				virtual inline IndexBuffer* GetIndexBuffer() const = 0;

				

				//------------------------------

				//MUTATORS
				//--------------------------------

				void IsVisible(bool visible);
				void SetMaterial(std::shared_ptr<Material>);

				//--------------------------------
		};
	}
}