/**********************************
	@File: RenderEngine.h

	@Summary: -Render Engine Interface
						-Used by the Main Engine class (Genesis) to interface with the rendering of objects and allow the world to be rendered
						-Allows the creation of multiple different render engine classes that use different API versions, without needing to alter the Genesis class

***********************************/

#pragma once

#include "Drawable.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "TerrainGrid.h"
#include "ParticleSystem.h"
#include "GUIBar.h"
#include "..\Math\Matrix4x4.h"

namespace Genesis
{
	namespace render
	{
		enum class EPrimitive
		{
			TRIANGLE_LIST,
			LINE_LIST,
			POINT_LIST
		};

		class RenderEngine
		{
			public:
				virtual ~RenderEngine() {}

				//Create a GUI Editor Bar
				virtual std::shared_ptr<GUIBar> CreateGUIBar(const std::string& name) = 0;

				//Create a Particle System Object
				virtual std::shared_ptr<ParticleSystem> CreateParticleSystem() = 0;

				//Construct a Terrain Grid of the given size
				virtual std::shared_ptr<TerrainGrid> CreateTerrainGrid(const TInt32& rows, const TInt32& columns, const TFloat32& gridSize) = 0;

				//FOR LOADING ASSETS
				//---------------------------------

				//Creates a new Material for rendering
				//If the given name already exists, returns the same one
				virtual std::shared_ptr<Material> LoadMaterial(const std::string& materialName) = 0;

				//Load mesh data using the given File Name (Uses the default Asset Path as the starting directory);
				virtual std::shared_ptr<Mesh> LoadMesh(const std::string& fileName) = 0;

				//Load mesh data using the given Primitive Type
				virtual std::shared_ptr<Mesh> LoadMesh(const EMeshPrimitiveTypes&) = 0;

				//Load the Texture data using the given File Name (Uses the default Asset Path as the starting directory)
				virtual std::shared_ptr<Texture> LoadTexture(const std::string& fileName) = 0;

				//Load a new Shader Technique using the Shader Files (Uses the default Asset Path as the starting directory)
				virtual bool LoadShader
				(
					const std::string& techniqueName, 
					const std::string& vertexShaderFileName, 
					const std::string& geometryShaderFileName, 
					const std::string& pixelShaderFileName,
					const TInt32& textureCount,
					bool hasNormalMap
				) = 0;

				//---------------------------------


				//RENDERING STAGES
				//--------------------------------

				//Ready the Engine to start Rendering the next Scene 
				virtual void Clear() = 0;

				//Set the Ambient Lighting to use for Lighting Calculations
				virtual bool SetAmbientLighting(const math::Vector3&) = 0;

				//Add a Point light to be used in the next rendered frame
				virtual bool AddPointLight(const math::Vector3& position, const math::Vector3& colour, const TFloat32& brightness) = 0;

				//Add a Spot light to be used in the next rendered frame
				virtual bool AddSpotLight(const math::Vector3& position, const math::Vector3& colour, const math::Vector3& direction, const TFloat32& brightness) = 0;

				//Add a Directional light to be used in the next rendered frame
				virtual bool AddDirectionalLight(const math::Vector3& colour, const math::Vector3& direction, const TFloat32& brightness) = 0;

				//Update which Camera to use for Rendering. The View and Projection matrices to send to shader
				virtual bool SetCamera(Camera*) = 0;			

				//Load the given material into the Render Engine, to be used by the Shaders
				//@param Material: How to Render
				virtual bool SetMaterial(Material*) = 0;

				//Render the given Drawable object with the given material, at the given location
				//@param Drawable: What To Render
				//@param worldMatrix: Where To Render
				virtual bool Draw(Drawable*, const math::Matrix4x4& worldMatrix, const EPrimitive& primitive = EPrimitive::TRIANGLE_LIST) = 0;
				virtual bool Draw(Drawable*, const math::Matrix4x4& worldMatrix, const TInt32& indexCount, const EPrimitive& primitive = EPrimitive::TRIANGLE_LIST) = 0;
				virtual bool DrawVertex(Drawable*, const math::Matrix4x4& worldMatrix, const TUInt32& vertexCount, const EPrimitive& primitive = EPrimitive::TRIANGLE_LIST) = 0;

				//Draw a world space line using the given points.
				//(A Material will be set automatically)
				virtual bool DrawLine(const math::Vector3& p1, const math::Vector3& p2, const math::Vector3& colour) = 0;

				//Present the next Frame/Scene
				virtual void PresentScene() = 0;

				//--------------------------------

				//Set the colour to display as the background when the back-buffer is cleared
				virtual void SetBackgroundColour(const math::Vector3&) = 0;
		};
	}
}