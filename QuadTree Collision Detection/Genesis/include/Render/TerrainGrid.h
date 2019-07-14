/**********************************
	@File: TerrainGrid.h

	@Summary: -A Terrain Grid is used for drawing grid style terrains, that use Line Lists instead of Triangles
						-Useful for visually constructing a grid to place over the scene

***********************************/

#pragma once

#include "Drawable.h"
#include "..\Math\QuadTree.h"

namespace Genesis
{
	namespace render
	{
		class TerrainGrid : public Drawable
		{
			public:
				virtual ~TerrainGrid() {}

				//Updates the Terrain Grid with the new Rows, Columns and Size values
				//Y-Axis = 0
				//Returns TRUE on success
				virtual bool UpdateGrid(const TInt32& rows, const TInt32& columns, const TFloat32& size) = 0;

				//Updates the Terrain Grid to create a visual representation of how the given Quad Tree would look like
				//Y-Axis = 0
				//Returns TRUE on success
				virtual bool UpdateGrid(math::QuadTree<TEntityUID>*) = 0;
		};
	}
}