#pragma once

#include "ComponentData.h"
#include "..\Render\TerrainGrid.h"
#include "..\Render\Material.h"

#include <memory>

namespace Genesis
{
	namespace entity
	{
		class TerrainGridComponentData : public ComponentData
		{
			private:
				std::shared_ptr<render::TerrainGrid> mp_Terrain;

				bool m_IsGrid;	//TRUE = Render a Terrain Grid (Line List)

			public:
				//CONSTRUCTOR/DESTRUCTOR
				//------------------------------

				TerrainGridComponentData
				(
					std::shared_ptr<render::TerrainGrid> terrain
				);

				virtual ~TerrainGridComponentData();

				//------------------------------


				//ACCESSORS
				//------------------------------

				std::shared_ptr<render::TerrainGrid> GetTerrain();

				//------------------------------
		};
	}
}