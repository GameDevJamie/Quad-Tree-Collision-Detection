#pragma once

/*
	SUMMARY:
	-Main interface for creating and destroying Entities, Components and Systems.
	-Retrieved via the World class. Cannot be instantiated alone
*/

#include "Defines.h"
#include "Entity.h"
#include "Components\ComponentData.h"
#include "ComponentGroup.h"

#include <memory>
#include <typeinfo>

namespace Genesis
{
	namespace entity
	{
		typedef std::vector<Entity> EntityList;

		class EntityManager
		{
			private:
				virtual bool AddComponent(const Entity&, const TComponentID&, std::shared_ptr<ComponentData>) = 0;
				virtual std::shared_ptr<ComponentData> GetComponent(const TComponentID&) = 0;
				virtual std::shared_ptr<ComponentData> GetComponent(const Entity&, const TComponentID&) = 0;
				virtual bool HasComponent(const Entity&, const TComponentID&) = 0;
				virtual bool DestroyComponent(const Entity&, const TComponentID&) = 0;


			public:
				//DESTRUCTOR
				virtual ~EntityManager() {}

				//Add Component Data to the given Entity
				//Returns the same Component if already attached
				template<typename T, typename... Args>
				std::shared_ptr<T> AddComponent(const Entity& entity, Args... args)
				{
					std::shared_ptr<T> exist = GetComponent<T>(entity);
					if (exist) return exist;
					
					//Get Component Id for the given type
					TComponentID componentId = GetComponentTypeId<T>();
					
					std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
					
					if (!AddComponent(entity, componentId, component))
					{
						//Failed to Add Component, so remove memory
						component.reset();
						return nullptr;
					}
					
					return component;
				}

				//Get Component Data from the first Entity that contains it
				template<typename T>
				std::shared_ptr<T> GetComponent()
				{
					TComponentID componentId = GetComponentTypeId<T>();
					auto component = GetComponent(componentId);
					if (!component) return nullptr;

					return std::static_pointer_cast<T>(component);
				}

				//Get Component Data from the given Entity
				template<typename T>
				std::shared_ptr<T> GetComponent(const Entity& entity)
				{
					//Get Component Id for the given type
					TComponentID componentId = GetComponentTypeId<T>();
					auto component = GetComponent(entity, componentId);
					if (!component) return nullptr;

					return std::static_pointer_cast<T>(component);
				}

				//Check if the given Entity has the given Component
				template<typename T>
				bool HasComponent(const Entity& entity)
				{
					//Get Component Id for the given type
					TComponentID componentId = GetComponentTypeId<T>();
					return HasComponent(entity, componentId);
				}

				//Destroy the Component attached to the given Entity
				//Returns FALSE if Component does not exist, or failed to Destroy
				template<typename T>
				bool DestroyComponent(const Entity& entity)
				{
					//Get Component Id for the given type
					TComponentID componentId = GetComponentTypeId<T>();
					return DestroyComponent(entity, componentId);
				}


				//Create a new Entity object with no Components attached
				virtual Entity CreateEntity() = 0;

				//Returns a list of all Entities that have the assigned Components in the given Group
				virtual EntityList GetEntities(const ComponentGroup&) = 0;

				//Destroy the given Entity
				//Returns FALSE if entity does not exist
				virtual bool DestroyEntity(const Entity&) = 0;

				//Destroy All components for one entity
				//Returns FALSE if entity does not exist
				virtual bool DestroyAllComponents(const Entity&) = 0;	

				//Destroy all Components for all entities
				virtual void DestroyAllComponents() = 0;	

				//Destroy all Entity objects
				virtual void DestroyAllEntities() = 0;
		};

		/*
		class EntityManager
		{
			protected:
				//List of all Component Types
				ComponentDataArray* m_ComponentDataArrayList[MaxComponents];		

				//UID maps to boolean value, which indicates if it is to be destroyed or not
				CHashTable<TEntityUID, bool>* mp_EntityUIDMap;

				//Used when selecting Entities with common components
				std::vector<ComponentId> m_TempComponentIdList;

				//True = Components have been added/removed, or an entity has been destroyed
				bool m_Change;

			private:
				template <typename... T>
				decltype(typename std::enable_if<sizeof...(T) == 0, bool>::type()) GetComponentIdList()
				{
					return true;
				}

				template<typename First, typename... Args>
				bool GetComponentIdList()
				{
					ComponentId id = GetComponentTypeId<First>();
					if (id == -1) return false;
					m_TempComponentIdList.push_back(id);
					return GetComponentIdList<Args...>();
				}

				template <typename... T>
				decltype(typename std::enable_if<sizeof...(T) == 0, bool>::type()) EntityHasComponents(const TEntityUID& entity)
				{
					return true;
				}

				template<typename First, typename... Args>
				bool EntityHasComponents(const TEntityUID& entity)
				{
					if (HasComponent<First>(entity))
					{
						return EntityHasComponents<Args...>(entity);
					}

					return false;
				}

			public:
				virtual ~EntityManager() {}

				//ENTITIES
				//------------------------------------

				//Create a new Entity with no components
				virtual TEntityUID CreateEntity() = 0;

				//Destroy the given Entity and its components.
				//Destroys Entity in the next Update
				//Returns FALSE if Entity does not exist
				virtual bool DestroyEntity(const TEntityUID& uid) = 0;

				//Destroy all Entities that have been created by this manager
				//Resets UID counter
				virtual void DestroyAllEntities() = 0;

				//Get a list of Entities that contain all the given component data types
				template <typename T, typename... Args>
				EntityList GetEntities()
				{
					m_TempComponentIdList.clear();	//Empty Current List

					if (!GetComponentIdList<T, Args...>()) return EntityList();
					if (m_TempComponentIdList.size() == 0) return EntityList();	//Return Empty Entity List

					TInt32 currentSize = m_ComponentDataArrayList[m_TempComponentIdList[0]]->GetNumEntities();
					ComponentId bestComponentId = m_TempComponentIdList[0];


					//Find the Component list with the lowest amount of entities in use
					//------------------------------
					for (auto it = m_TempComponentIdList.begin() + 1; it != m_TempComponentIdList.end(); it++)
					{
						ComponentId compId = (*it);
						
						TInt32 newSize = m_ComponentDataArrayList[compId]->GetNumEntities();
						if (newSize < currentSize)
						{
							currentSize = newSize;
							bestComponentId = compId;
						}
					}
					//------------------------------


					EntityList entityList = m_ComponentDataArrayList[bestComponentId]->GetEntities();					
					auto it = entityList.begin();
					while(it != entityList.end())
					{
						if (!EntityHasComponents<T, Args...>((*it)))
						{
							//Entity Does not have all components, so remove from list
							it = entityList.erase(it);
						}
						else it++;
					}

					return entityList;
				}
				//------------------------------------


				//COMPONENTS
				//--------------------------------------

				//Add a new component to the entity
				//Returns the Component Type added, or NULL if Entity does not exist
				template<typename T, typename... Args>
				T* AddComponent(const TEntityUID& uid, Args&&... args)
				{
					bool destroy;
					if (!mp_EntityUIDMap->LookUp(uid, &destroy))
					{
						//Entity Not found
						return NULL;
					}
					T* comp = GetComponent<T>(uid);
					if (comp) return comp;	//If already exists, return it

					ComponentId compId = GetComponentTypeId<T>();
					T* component = new T(std::forward<Args>(args)...);
					m_ComponentDataArrayList[compId]->AddComponent(uid, component);

					m_Change = true;

					return GetComponent<T>(uid);
				}

				template<typename T>
				T* GetComponent(const TEntityUID& uid) const
				{
					//Check Entity Exists using HashMap
					//If LookUp = false, return NULL;
					bool destroy;
					if(!mp_EntityUIDMap->LookUp(uid, &destroy)) return NULL;

					//Get the Unique Id of the component
					TInt32 compId = GetComponentTypeId<T>();

					//Unique Id = Index, so grab the Correct Component Array via the index
					IComponentData* comp = m_ComponentDataArrayList[compId]->GetComponent(uid);
					if (!comp) return NULL;

					return static_cast<T*>(comp);
				}

				//Returns TRUE if the given Entity has the given Component Type
				template<typename T>
				bool HasComponent(const TEntityUID& uid)
				{
					//Get the Unique Id of the component
					TInt32 compId = GetComponentTypeId<T>();

					return m_ComponentDataArrayList[compId]->GetComponent(uid);
				}

				//Destroy the given component that is attached to an Entity
				template<typename T>
				void DestroyComponent(const TEntityUID& uid)
				{
					//Check Entity Exists
					bool destroy;
					if (!mp_EntityUIDMap->LookUp(uid, &destroy)) return;

					TInt32 compId = GetComponentTypeId<T>();
					m_ComponentDataArrayList[compId]->CleanComponent(uid);

					m_Change = true;
				}

				//Destroy all components attached to the given entity
				virtual void DestroyAllComponents(const TEntityUID& uid) = 0;

				//--------------------------------------
		};
		*/
	}
}