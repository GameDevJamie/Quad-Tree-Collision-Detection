/**********************************
WorldSystem.h

* The World class is used as the primary source for creating objects in the scene

* Each World object contains a collection of Entities and UI objects that make up the world

* Can Use multiple World objects to create different levels, menu screens etc.

***********************************/

#pragma once

#include "EntityManager.h"
#include "Render\RenderEngine.h"
#include "Math\Vector3.h"
#include "WorldSystem.h"

#include <memory>

namespace Genesis
{
	namespace entity
	{
		class World
		{
			protected:
				std::vector<std::unique_ptr<WorldSystem>> m_WorldSystemList;

			public:
				//Destroy the world, removing all Entities, UI features etc., that make up this World
				virtual ~World() {}

				//ACCESSORS
				//------------------------------------

				virtual math::Vector3 GetAmbientLighting() const = 0;

				virtual EntityManager* GetEntityManager() const = 0;
				virtual render::RenderEngine* GetRenderer() const = 0;

				//Return the name of this World
				virtual std::string GetName() const = 0;

				//Check if Lighting is currently enabled for this World
				virtual bool LightingEnabled() const = 0;

				//------------------------------------


				//MUTATORS
				//------------------------------------

				//Set whether to enable/disable lighting for this World
				//@param enable: TRUE = Allow Lighting to be processed
				virtual void EnableLighting(bool enable = true) = 0;

				//Set how much Ambient Light is produced by this World
				virtual void SetAmbientLighting(const math::Vector3&) = 0;

				//------------------------------------

				//SYSTEMS
				//------------------------------------

				//Add a new System if it does not already exist
				//Automatically Activates them
				template<typename T>
				void AddSystem()
				{
					//Check System does not already Exist
					auto it = m_WorldSystemList.begin();
					while (it != m_WorldSystemList.end())
					{
						WorldSystem* system = (*it).get();
					
						if (dynamic_cast<T*>(system)) return;
					
						it++;
					}

					//Add New System
					m_WorldSystemList.push_back(std::make_unique<T>());
					m_WorldSystemList.back()->Start((*this));
				}

				//Remove the given System from the Manager, if it has been added
				template<typename T>
				void RemoveSystem()
				{
					//Iterates through all systems until it finds a match
					auto it = m_WorldSystemList.begin();
					while (it != m_WorldSystemList.end())
					{
						WorldSystem* system = (*it).get();
						if (dynamic_cast<T>(system))
						{
							(*it).reset(NULL);
							it = m_WorldSystemList.erase(it);
							return true;
						}
					
						it++;
					}
					
					return false	//No match found
				}

				//Remove All Systems from the Manager
				void RemoveAllSystems()
				{
					auto it = m_WorldSystemList.begin();
					while (it != m_WorldSystemList.end())
					{
						(*it).reset(NULL);
						it = m_WorldSystemList.erase(it);
					}
				}

				//------------------------------------


				//Destroy the World in the Next Engine Update.
				//(CANNOT BE UNDONE)
				virtual void Destroy() = 0;
		};
	}
}