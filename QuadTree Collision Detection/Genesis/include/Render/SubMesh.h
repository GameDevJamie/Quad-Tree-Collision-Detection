#pragma once

/*
	SUMMARY:
	-Each Mesh is made up of a SubMesh
	-Each SubMesh contains Material data to help render it
	-The SubMesh is the part that can be rendered, the Mesh is just a container for the SubMeshes
*/

#include "Drawable.h"
#include "Material.h"

namespace Genesis
{
	namespace render
	{
		class SubMesh : public Drawable
		{
			public:
				virtual ~SubMesh() {}

				//ACCESSORS
				//-----------------------------------

				virtual inline math::Vector3 GetMinBounds() const = 0;
				virtual inline math::Vector3 GetMaxBounds() const = 0;
				virtual inline TFloat32 GetBoundingRadius() const = 0;

				//-----------------------------------
		};
	}
}