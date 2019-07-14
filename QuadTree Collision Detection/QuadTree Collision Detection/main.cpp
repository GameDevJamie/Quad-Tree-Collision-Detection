#include <Genesis.h>

//Components
#include "GlobalComponentData.h"

//Systems
#include "CameraSystem.h"
#include "SpawnerSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "QuadTreeBuilderSystem.h"

using namespace Genesis;
using namespace Genesis::entity;

//Globals
TFloat32 fps = 0;

bool LoadMaterials(render::RenderEngine*);
bool SetupScene(World*);

int main()
{
	auto engine = CreateEngine();
	auto errorCode = engine->Initialise(EGraphicsAPI::DirectX11, "Quad Tree Collision Detection", 1280, 960);
	if (errorCode != EEngineErrorCode::SUCCESS)
	{
		engine->ShutDown();
		engine.reset(nullptr);
		return 0;
	}

	//Set Backgroud Colour
	engine->GetRenderer()->SetBackgroundColour(math::Vector3(0.06f, 0.69f, 0.98f));

	World* world = engine->GetWorldManager()->CreateWorld("World");

	if (!LoadMaterials(engine->GetRenderer()) || !SetupScene(world))
	{
		engine->ShutDown();
		return 0;
	}

	//Add Systems
	world->AddSystem<Render3DSystem>();
	world->AddSystem<CameraSystem>();
	world->AddSystem<SpawnerSystem>();
	world->AddSystem<MovementSystem>();
	world->AddSystem<CollisionSystem>();
	world->AddSystem<QuadTreeBuilderSystem>();

	while (engine->IsRunning())
	{
		fps = 1.0f / system::DeltaTime();

		engine->GetRenderer()->Clear();
		engine->Update();
		engine->GetRenderer()->PresentScene();

		if (input::IsKeyDown(input::EKeyCode::KEY_ESCAPE))
		{
			engine->ShutDown();
			continue;
		}
	}
}

bool LoadMaterials(render::RenderEngine* renderer)
{
	auto mat = renderer->LoadMaterial("FloorMat");
	mat->SetShader(render::EShaderTechnique::ONE_COLOUR);
	mat->SetDiffuseColour(math::Vector3::kWhite);

	mat = renderer->LoadMaterial("NonCollidedMat");
	mat->SetShader(render::EShaderTechnique::ONE_COLOUR);
	mat->SetDiffuseColour(math::Vector3::kRed);

	mat = renderer->LoadMaterial("CollidedMat");
	mat->SetShader(render::EShaderTechnique::ONE_COLOUR);
	mat->SetDiffuseColour(math::Vector3::kGreen);
	mat->SetRasterizerState(render::ERasterizerState::BACK);

	return true;
}

//Create the Entities and load the starting scene
bool SetupScene(World* world)
{
	const TFloat32 floorSize = 50.0f;
	EntityManager* EntityManager = world->GetEntityManager();

	//Create GUI Bar
	auto guiBar = world->GetRenderer()->CreateGUIBar("GUI");
	guiBar->SetTitle("GUI");
	guiBar->AddVarRW("FPS", EType::FLOAT, &fps, "group='FPS'");
	guiBar->DefineBar("refresh=1");	//Refresh bar every second (For FPS)
	

	//Create Global Entity (Holds GUI Bar)
	Entity globalEntity = EntityManager->CreateEntity();
	auto globalData = EntityManager->AddComponent<GlobalComponentData>(globalEntity, guiBar);
	globalData->MinSpawn = math::Vector3::kOne * -(floorSize - 5.0f);
	globalData->MinSpawn.y = 0.0f;
	globalData->MaxSpawn = math::Vector3::kOne * (floorSize - 5.0f);
	globalData->MaxSpawn.y = 0.0f;

	//Create Camera Entity
	Entity cameraEntity = EntityManager->CreateEntity();
	EntityManager->AddComponent<TransformComponentData>(cameraEntity, math::Vector3::kYAxis * 100.0f, math::Quaternion::Euler(90.0f, 0.0f, 0.0f));
	EntityManager->AddComponent<CameraComponentData>(cameraEntity);

	//Create Floor Entity
	Entity floorEntity = EntityManager->CreateEntity();
	EntityManager->AddComponent<TransformComponentData>(floorEntity, math::Vector3(0.0f, -0.1f, 0.0f), math::Quaternion::Euler(90.0f, 0.0f, 0.0f), math::Vector3::kOne * floorSize);
	EntityManager->AddComponent<StaticMeshComponentData>(floorEntity, world->GetRenderer()->LoadMesh(render::EMeshPrimitiveTypes::SQUARE))->SetCustomMaterial(0, world->GetRenderer()->LoadMaterial("FloorMat"));

	return true;
}