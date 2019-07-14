#pragma once

/*
	SUMMARY:
	-Contains data about a mesh (Vertex Size, Index Count etc.)
	-Each mesh is made up of submeshes, each containing a default material

	-The default materials are constructed during the creation of the Mesh object. 
	-The name of each material will be the name of the file it loads, minus the extension
*/

#include "..\Defines.h"
#include "SubMesh.h"
#include "..\Asset.h"
#include "..\Math\Vector3.h"

#include <string>

namespace Genesis
{
	namespace render
	{
		//Common Primitives that can be created without importing a file
		enum EMeshPrimitiveTypes
		{
			SQUARE = 0,
			CUBE = 1,
			SPHERE = 2,
			PYRAMID = 3,
			CYLINDER = 4,

			ENumPrimitives = 5
		};

		class Mesh : public Asset
		{
			public:
				virtual ~Mesh() {}

				//ACCESSORS
				//------------------------------

				virtual SubMesh* GetSubMesh(const TUInt32& index) = 0;

				virtual inline TUInt32 GetSubMeshCount() const = 0;

				virtual inline math::Vector3 GetMinBounds() const = 0;
				virtual inline math::Vector3 GetMaxBounds() const = 0;
				virtual inline TFloat32 GetBoundingRadius() const = 0;

				virtual inline bool HasGeometry() const = 0;

				//------------------------------
		};
	}
}