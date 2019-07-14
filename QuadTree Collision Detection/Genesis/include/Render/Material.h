#pragma once

/*
	SUMMARY:
	-Materials are used to define how a mesh/sprite is rendered (Textures, Lighting, Level of Transparency, Shininess etc.)
	-Each Drawable object uses a Material to help render it
	-A Material is an Asset, as can have multiple of the same material shared across SubMeshes and other renderable objects
*/

#include "Texture.h"
#include "RenderStates.h"
#include "..\Math\Vector3.h"
#include <memory>

namespace Genesis
{
	namespace render
	{
		class Material : public Asset
		{
			public:
				virtual ~Material() {}

				//ACCESSORS
				//------------------------------

				virtual inline math::Vector3 GetDiffuseColour() const  = 0;
				virtual inline math::Vector3 GetSpecularColour() const = 0;
				virtual inline TFloat32 GetSpecularPower() const  = 0;

				virtual inline std::string GetShader() const = 0;
				virtual inline std::shared_ptr<Texture> GetMainTexture() const  = 0;
				virtual inline std::shared_ptr<Texture> GetNormalMap() const = 0;

				virtual inline EBlendState GetBlendState() const = 0;
				virtual inline ERasterizerState GetRasterizerState() const = 0;
				virtual inline ESamplerState GetSamplerState() const = 0;
				virtual inline EDepthStencilState GetDepthStencilState() const = 0;

				//Get the Opacity of the Material (How Transparent is the Material)
				virtual inline TFloat32 GetOpacity() const = 0;

				//------------------------------


				//MUTATORS
				//-------------------------------

				virtual inline void SetDiffuseColour(const math::Vector3&) = 0;
				virtual inline void SetSpecularColour(const math::Vector3&) = 0;
				virtual inline void SetSpecularPower(const TFloat32&) = 0;

				virtual inline void SetShader(const std::string& shaderTechnique) = 0;
				virtual inline void SetShader(const EShaderTechnique&) = 0;
				virtual inline void SetMainTexture(std::shared_ptr<Texture>) = 0;
				virtual inline void SetNormalMap(std::shared_ptr<Texture>) = 0;

				virtual inline void SetBlendState(const EBlendState&) = 0;
				virtual inline void SetRasterizerState(const ERasterizerState&) = 0;
				virtual inline void SetSamplerState(const ESamplerState&) = 0;
				virtual inline void SetDepthStencilState(const EDepthStencilState&) = 0;

				//Set the Opacity of the Material (How Transparent is the Material)
				virtual inline void SetOpacity(const TFloat32&) = 0;

				//-------------------------------

				//Reset the Material back to its default settings (Removes Shader attached)
				virtual void Reset() = 0;
		};
	}
}