#pragma once

/************************************************************
FILE: CQuadTree.h

SUMMARY: A QuadTree is a spatial partitioning method, used to contain a set of points.
		If the number of points exceeds the maximum number given, the quadtree splits into 4 smaller quadtrees.
************************************************************/

#include "AABB.h"
#include "Vector2.h"
#include <vector>

namespace Genesis
{
	namespace math
	{
		template <typename T>
		struct SQuadTreeNode
		{
			T data;			//Data contained in node (E.g. UID)
			Vector2 point;	//Where node is located in tree

			SQuadTreeNode(T iData, Vector2 fPoint)
			{
				data = iData;
				point = fPoint;
			}
		};

		template<typename T>
		class QuadTree
		{
			private:
				//A QuadTree is an Axis-Aligned Box
				AABB m_AABB;

				QuadTree* mp_TopLeft;
				QuadTree* mp_TopRight;
				QuadTree* mp_BottomLeft;
				QuadTree* mp_BottomRight;

				//TRUE = Quadtree has been Sub-Divided, new points added are inserted into the children quadtrees
				bool m_Divided;

				TFloat32 m_MaxPoints;		//Maximum Number of points allowed in the tree
				TInt32 m_MaxLayers;			//How deep can the QuadTree be
				TInt32 m_CurrentLayer;		//How far down this QuadTree is so far (How many times it has been divided)

				std::vector<SQuadTreeNode<T>> m_List;	//Points and data contained here

				bool m_EnumStart;
				bool m_EndOfEnum;

			public:
				//Constructor/Destructor
				//-----------------------------

				//Construct a Quad Tree of equal sides
				QuadTree(const Vector2& centre, const TFloat32& size, const TInt32& maxLayers, const TInt32& maxPointsPerTree, const TInt32& currentLayer = 0)
				{
					m_AABB = AABB(centre, math::Vector2(size, size));

					mp_TopLeft = nullptr;
					mp_TopRight = nullptr;
					mp_BottomLeft = nullptr;
					mp_BottomRight = nullptr;

					m_MaxLayers = maxLayers;
					m_MaxPoints = maxPointsPerTree;
					if (m_MaxPoints <= 0) m_MaxPoints = 1;	//Ensure atleast one node can exist per quad tree

					m_CurrentLayer = currentLayer;

					m_Divided = false;

					m_EnumStart = false;
					m_EndOfEnum = false;
				}

				//Destroy the QuadTree and Free Memory
				~QuadTree()
				{
					Reset();
				}

				//-----------------------------


				//ACCESSORS
				//------------------------------

				inline AABB GetAABB() const { return m_AABB; }

				//Returns a list of Box Data for each Quad Tree divided
				//Can be used for a visual representation of QuadTree
				std::vector<AABB> GetAABBListDivided()
				{
					std::vector<AABB> list;

					if (!m_Divided) return list;

					list.push_back(GetAABB());

					auto topLeftList = mp_TopLeft->GetAABBListDivided();
					auto topRightList = mp_TopRight->GetAABBListDivided();
					auto bottomLeftList = mp_BottomLeft->GetAABBListDivided();
					auto bottomRightList = mp_BottomRight->GetAABBListDivided();

					for (auto it = topLeftList.begin(); it != topLeftList.end(); ++it)
					{
						list.push_back((*it));
					}
					for (auto it = topRightList.begin(); it != topRightList.end(); ++it)
					{
						list.push_back((*it));
					}
					for (auto it = bottomLeftList.begin(); it != bottomLeftList.end(); ++it)
					{
						list.push_back((*it));
					}
					for (auto it = bottomRightList.begin(); it != bottomRightList.end(); ++it)
					{
						list.push_back((*it));
					}

					return list;
				}

				//------------------------------


				//Inserts the given point into the QuadTree
				//Returns false if QuadTree's max division size has been reached, or if out of bounds
				bool Insert(SQuadTreeNode<T> node)
				{
					//Check if point is contained withing QuadTree
					if (!m_AABB.Contains(node.point)) return false;

					if (m_Divided)
					{
						if (mp_TopLeft->Insert(node)) return true;
						if (mp_TopRight->Insert(node)) return true;
						if (mp_BottomLeft->Insert(node)) return true;
						if (mp_BottomRight->Insert(node)) return true;

						//Failed to insert point
						return false;
					}

					//Quad Tree can no longer divide and there are too many points
					if (m_CurrentLayer >= m_MaxLayers && m_List.size() >= m_MaxPoints) return false;

					m_List.push_back(node);

					//Check if Quad Tree needs to Divide
					if (m_List.size() > m_MaxPoints)
					{
						this->SubDivide();
					}

					return true;
				}

				//Divide the QuadTree into 4 smaller Trees
				void SubDivide()
				{
					if (m_Divided) return;	//Already Divided
					if (m_CurrentLayer >= m_MaxLayers) return;	//Reached maximum layers

					math::Vector3 centre = m_AABB.Centre;
					TFloat32 size = m_AABB.Size.x;
					TFloat32 halfSize = size / 2.0f;
					TFloat32 quadSize = halfSize / 2.0f;

					TInt32 nextLayer = m_CurrentLayer + 1;

					mp_TopLeft = new QuadTree(math::Vector2(centre.x - quadSize, centre.y + quadSize), halfSize, m_MaxLayers, m_MaxPoints, nextLayer);
					mp_TopRight = new QuadTree(math::Vector2(centre.x + quadSize, centre.y + quadSize), halfSize, m_MaxLayers, m_MaxPoints, nextLayer);
					mp_BottomLeft = new QuadTree(math::Vector2(centre.x - quadSize, centre.y - quadSize), halfSize, m_MaxLayers, m_MaxPoints, nextLayer);
					mp_BottomRight = new QuadTree(math::Vector2(centre.x + quadSize, centre.y - quadSize), halfSize, m_MaxLayers, m_MaxPoints, nextLayer);

					//Move points to new created trees
					for (auto it = m_List.begin(); it < m_List.end(); it++)
					{
						if (mp_TopLeft->Insert((*it))) continue;
						if (mp_TopRight->Insert((*it))) continue;
						if (mp_BottomLeft->Insert((*it))) continue;
						if (mp_BottomRight->Insert((*it))) continue;
					}

					//Clear List from this QuadTree
					m_List.clear();

					m_Divided = true;
				}

				void Reset()
				{
					if (mp_TopLeft) delete(mp_TopLeft);
					if (mp_TopRight) delete(mp_TopRight);
					if (mp_BottomLeft) delete(mp_BottomLeft);
					if (mp_BottomRight) delete(mp_BottomRight);

					m_List.clear();
					m_Divided = false;
				}


				//FUNCTIONS FOR GOING THROUGH EACH SET OF LISTS IN EACH QUAD TREE
				//---------------------------------------------------

				void BeginEnum()
				{
					if (m_EnumStart) return;

					if (m_Divided)
					{
						mp_TopLeft->BeginEnum();
						mp_TopRight->BeginEnum();
						mp_BottomLeft->BeginEnum();
						mp_BottomRight->BeginEnum();
					}

					m_EnumStart = true;
					m_EndOfEnum = false;
				}

				bool Enumerate(std::vector<SQuadTreeNode<T>> &list)
				{
					if (!m_EnumStart) return false;	//BeginEnum() has not been called
					if (m_EndOfEnum) return false;	//End of Enumeration for this Tree (Already Enumerated)
					

					if (m_List.size() == 0 && !m_Divided)
					{
						m_EndOfEnum = true;
						return false;
					}
					if (m_List.size() == 0 && m_Divided)
					{
						if (mp_TopLeft->Enumerate(list)) return true;
						if (mp_TopRight->Enumerate(list)) return true;
						if (mp_BottomLeft->Enumerate(list)) return true;
						if (mp_BottomRight->Enumerate(list)) return true;
					}
					if (m_List.size() != 0)
					{
						list = m_List;
						m_EndOfEnum = true;
						return true;
					}

					m_EndOfEnum = true;
					return false;
				}

				void EndEnum()
				{
					if (m_Divided)
					{
						mp_TopLeft->EndEnum();
						mp_TopRight->EndEnum();
						mp_BottomLeft->EndEnum();
						mp_BottomRight->EndEnum();
					}

					m_EnumStart = false;
					m_EndOfEnum = false;
				}

				//---------------------------------------------------
		};
	}
}