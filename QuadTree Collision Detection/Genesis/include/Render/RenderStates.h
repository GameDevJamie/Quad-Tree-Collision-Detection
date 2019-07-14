#pragma once

namespace Genesis
{
	namespace render
	{
		enum ESamplerState
		{
			POINTCLAMP = 0,
			TRILINEARWRAP = 1,
			ENumSamplerStates = 2	//Number of Sampler states
		};

		enum EBlendState
		{
			BLEND_NONE = 0,
			ADDITIVE = 1,
			MULTIPLICATIVE = 2,
			ALPHA = 3,
			ENumBlendStates = 4		//Number of Blend states
		};

		enum ERasterizerState
		{
			RASTERIZER_NONE = 0,		// Cull none of the polygons, i.e. show both sides
			BACK = 1,					// Cull back side of polygon - normal behaviour, only show front of polygons
			FRONT = 2,
			ENumRasterizerStates = 3	//Number of Rasterizer states
		};

		enum EDepthStencilState
		{
			ZBUFFER_ON = 0,							//Depth Enable = ON
			ZBUFFER_OFF = 1,						//Depth Enable = OFF
			DEPTH_WRITE_OFF = 2,				//Depth Enable = ON, Depth Write Mask = OFF
			ENumDepthStencilStates = 3	//Number of Depth-Stencil States
		};

		enum class EShaderTechnique
		{
			STANDARD,		//Default Shader for Meshes
			PARTICLES,	//Default Shader for Particle Systems
			ONE_COLOUR	//For Line Rendering and Terrain Grids
		};
	}
}