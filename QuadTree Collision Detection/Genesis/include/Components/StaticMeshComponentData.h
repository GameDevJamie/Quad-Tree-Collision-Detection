#pragma once

#include "ComponentData.h"
#include "..\Render\Mesh.h"
#include "..\Render\Material.h"

#include <memory>
#include <vector>

namespace Genesis
{
	namespace entity
	{
		class StaticMeshComponentData : public ComponentData
		{
			private:
				std::shared_ptr<render::Mesh> mp_Mesh;
				std::vector<std::shared_ptr<render::Material>> m_CustomMaterialList;	//Materials to use instead of the default ones in the mesh (An empty string means "USE DEFAULT")

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				StaticMeshComponentData(std::shared_ptr<render::Mesh>);

				virtual ~StaticMeshComponentData();

				//------------------------------


				//ACCESSORS
				//------------------------------

				std::shared_ptr<render::Mesh> GetMesh();
				std::shared_ptr<render::Material> GetCustomMaterial(const TInt32& subMeshIndex);

				//------------------------------


				//MUTATORS
				//--------------------------------

				void SetMesh(std::shared_ptr<render::Mesh>);

				//Set the material to force the given submesh to use when rendering
				void SetCustomMaterial(const TInt32& subMeshIndex, std::shared_ptr<render::Material>);

				//Set all submeshes to use the same given material
				void SetAllCustomMaterial(std::shared_ptr<render::Material> customMat);

				//--------------------------------
		};
	}
}