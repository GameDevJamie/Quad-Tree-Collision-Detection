#pragma once

#include "Components\ComponentData.h"
#include <vector>

namespace Genesis
{
	namespace entity
	{
		class ComponentGroup
		{
			private:
				std::vector<TComponentID> m_FilterList;

			public:
				//Constructor/Destructor
				//----------------------------

				ComponentGroup() {}
				~ComponentGroup() {}

				//----------------------------

				template <typename T>
				void AddFilter()
				{
					//Get ID/Index of Component
					TComponentID id = GetComponentTypeId<T>();

					if (id == INVALID_COMPONENT) return;

					m_FilterList.push_back(id);
				}

				//Remove Filter From List
				template <typename T>
				void RemoveFilter()
				{
					//Get ID/Index of Component
					TComponentID id = GetComponentTypeId<T>();
					if (id == INVALID_COMPONENT) return;

					//Iterate through list to find Id
					for (auto it = m_FilterList.begin(); it != m_FilterList.end(); it++)
					{
						if ((*it) == id)
						{
							m_FilterList.erase(it);
							return;
						}
					}
				}

				void Reset()
				{
					m_FilterList.clear();
				}


				std::vector<TComponentID> GetList() const { return m_FilterList; }
		};
	}
}