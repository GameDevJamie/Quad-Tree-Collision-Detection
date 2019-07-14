#pragma once

/*
	SUMMARY:
	The main interface class for accessing the engine and all of its components (Entities, Rendering etc.)
	An instance of this class must be created before all other components can be accessed. (E.g. Resource Manager)
*/

#include "Defines.h"

//INCLUDES FOR EASY ACCESS TO OTHER PARTS OF ENGINE
//-----------------------------
//RENDER
#include "Render\RenderEngine.h"

//INPUT
#include "Input.h"

//MATH
#include "Math/BaseMath.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"
#include "Math/Quaternion.h"
#include "Math/Transform.h"
#include "Math/MousePicker.h"
#include "Math\QuadTree.h"

//ENTITY
#include "WorldManager.h"
#include "WorldSystem.h"
#include "Components\Components.h"

//AI
#include "AI\GridPathfinding.h"
//-----------------------------

#include <string>
#include <memory>

namespace Genesis
{
	enum class EGraphicsAPI
	{
		DirectX11	//Have the Render Engine use DirectX 11
	};

	class GenesisEngine
	{
		public:
			virtual ~GenesisEngine() {}

			//ACCESSORS
			//-----------------------------------------

			//TRUE = Engine is currently Running
			virtual bool IsRunning() const = 0;

			virtual entity::WorldManager* GetWorldManager() const = 0;

			virtual render::RenderEngine* GetRenderer() const = 0;

			//-----------------------------------------


			//MUTATORS
			//-------------------------------------

			//Sets the Window to fullscreen mode
			//@param fullScreen: TRUE = fullscreen, FALSE = Windowed
			virtual void SetFullScreen(bool fullScreen = true) = 0;

			//-------------------------------------

			//Startup the engine, Initialising all the necessary components (Render Engine, Physics Engine, Entities etc.).
			//Will automatically call ShutDown if fails to initialise
			//@param graphicsApi: What Graphics API to use to render Drawable objects
			//@param wndName: Name to use for the Window Title
			//@param resWidth: Resolution Width
			//@param resHeight: Resolution Height
			//Returns an error code based on failure type, or of type SUCCESS if setup completed successfully
			virtual EEngineErrorCode Initialise(EGraphicsAPI, const std::string& wndName, const TInt32& resWidth, const TInt32& resHeight) = 0;
			
			//Shuts Down the Engine, de-allocating all memory used
			virtual void ShutDown() = 0;

			//Update all components of the Engine
			virtual bool Update() = 0;
	};

	
	//Load the Genesis Engine with the given API
	std::unique_ptr<GenesisEngine> CreateEngine();
}