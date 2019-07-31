#pragma once

#define INVALID_COMPONENT 0
#define PI 3.1415926535f

#define ASSET_DIRECTORY "Assets\\"		//Folder for Assets (Textures, Meshes, etc.)
#define SHADER_DIRECTORY "Shaders\\"	//Folder for Shaders

#if (defined(_WIN32) || defined(_WIN64))
	#define GEN_CALL         __stdcall
#else
	#define GEN_CALL
#endif

//ENUMS
//--------------------------------

enum class EEngineErrorCode
{
	SUCCESS,

	WINDOW_INITIALISATION_ERROR,				//Window Failed to load

	RENDER_ENGINE_DEVICE_INITIALISATION_ERROR,	//Failed to load Device from Render Engine
	RENDER_ENGINE_SHADER_INITIALISATION_ERROR,	//Failed to load shaders from Render Engine
	RENDER_ENGINE_STATES_INITIALISATION_ERROR,	//Failed to load Blend states or Sampler states etc.
	RENDER_ENGINE_UNKNOWN_ERROR,								//Unknown error occurred within Render Engine

	WORLDMANAGER_INITIALISATION_ERROR,	//World Manager Failed to Initialise
	UNKNOWN_ERROR	//Unknown Error Occurred
};

//--------------------------------

enum class EType
{
	BOOL,

	INT8,
	INT16,
	INT32,

	UINT8,
	UINT16,
	UINT32,

	FLOAT,
	DOUBLE,

	COLOR3,
	COLOR4,

	QUAT4,

	DIR3
};

//Fixed Size Types
//-------------------------------
typedef signed char      TInt8;
typedef signed short     TInt16;
typedef signed int       TInt32;
typedef signed __int64   TInt64;

typedef unsigned char    TUInt8;
typedef unsigned short   TUInt16;
typedef unsigned int     TUInt32;
typedef unsigned __int64 TUInt64;

typedef float TFloat32;
typedef double TFloat64;
//-------------------------------

//Entity Types
//-------------------------------
typedef unsigned int TEntityUID;
typedef unsigned int TComponentID;
//-------------------------------


//Editor/GUI Bar Types
//---------------------------------
typedef void (GEN_CALL * GUIButtonCallback)(void* clientData);
typedef void (GEN_CALL * GUISetCallback)(void* var, void* clientData);
typedef void (GEN_CALL * GUIGetCallback)(void* var, void* clientData);
//---------------------------------