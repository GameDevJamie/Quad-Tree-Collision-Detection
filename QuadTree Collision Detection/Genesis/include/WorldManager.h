#pragma once

/*
	SUMMARY:
	-Main interface for creating and destroying Worlds.
	-Worlds are the main centre point of Entity creation.

	-Retrieved via an instance of the GenesisCore class. (Engine)
*/

#include "World.h"

#include <string>

namespace Genesis
{
	namespace entity
	{
		class WorldManager
		{
			public:
				virtual ~WorldManager() {}

				//Load the given world and set it as active
				//Only one world can be active at a time
				virtual bool LoadWorld(const std::string& worldName) = 0;

				//Create a new world with the given name
				//If a world with the given name already exists, will return that world
				//@param worldName: Name to give to world
				//@param load: Load the world once created
				//Returns either a new world or existing world if names match
				virtual World*  CreateWorld(const std::string& worldName, bool load = true) = 0;

				//Retrieve a world with the given name
				//@param: Name of the world to retrieve
				//Returns the world with the given name or NULL if not found
				virtual World*  GetWorld(const std::string& worldName) = 0;

				//Retrieve the current active world (The world that is being rendered)
				//Returns the active world or NULL if not found
				virtual World* GetActiveWorld() = 0;

				//Destroy the given World, along with its Entities, Components and Systems
				//@param worldName: The name of the world to destroy
				//Returns false if not found
				virtual bool DestroyWorld(const std::string& worldName) = 0;


				//Destroy all worlds created
				virtual void DestroyAllWorlds() = 0;
		};
	}
}