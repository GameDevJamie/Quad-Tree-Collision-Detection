#pragma once

#include "..\Defines.h"
#include "..\Math\Vector3.h"

#include <vector>
#include <deque>

namespace Genesis
{
	namespace ai
	{
		class GridPathfinding
		{
			private:
				struct GridNode
				{
					TInt32 Row;
					TInt32 Col;

					TInt32 cost;
					TInt32 total;

					math::Vector3 WorldPos;	//Where in the world is this node positioned

					GridNode* parent;

					GridNode()
					{
						cost = 0;
						total = 0;
						parent = nullptr;
					}
				};

				TInt32 m_NumRows, m_NumCols;

				//All nodes in grid (Become allocated when assigning cost and position to node)
				std::vector<std::vector<GridNode*>> m_Grid;

				std::deque<GridNode*> m_OpenList;
				std::deque<GridNode*> m_ClosedList;

		private:
			//Resets the nodes for a new path to be calculated
			//DOES NOT DE-ALLOCATE MEMORY
			void Reset();

			//HELPER FUNCTIONS
			void AddToOpenList(GridNode* parent, const TInt32& row, const TInt32& col, const TInt32& heuristic);
			bool NodeExists(GridNode*);
			void RemoveNodeFromList(GridNode*);	//Removes the node from the Open/Closed List. (DOES NOT DEALLOCATE MEMORY)

			public:
				//CONSTRUCTOR / DESTRUCTOR
				//-----------------------------

				GridPathfinding();
				GridPathfinding(const TInt32& rows, const TInt32& cols);
				~GridPathfinding();

				//-----------------------------

				//Calculates a path from the given Start to the Goal
				//@partial: Return only a partial list if the Goal could not be reached. If FALSE, returns an empty list
				std::vector<math::Vector3> CalculatePath(const TInt32& startRow, const TInt32& startCol, const TInt32& goalRow, const TInt32& goalCol, bool partial = false);

				//Set the Grid Size to be used for pathfinding
				//Releases currently set nodes and starts over
				void SetGridSize(const TInt32& rows, const TInt32& cols);

				//Set the cost of the given node, and the world position 
				void SetNode(const TInt32& row, const TInt32& col, const TInt32& cost);
				void SetNode(const TInt32& row, const TInt32& col, const TInt32& cost, const math::Vector3& worldPos);

				//Release all memory used
				//Removes all currently assigned nodes in grid
				void Release();
		};
	}
}