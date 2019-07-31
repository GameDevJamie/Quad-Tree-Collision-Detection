#include <Genesis.h>

//Components
#include "GlobalComponentData.h"

//Systems
#include "CameraSystem.h"
#include "SpawnerSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "QuadTreeBuilderSystem.h"
#include "FloorSystem.h"
#include "ColourSystem.h"

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
	engine->GetRenderer()->SetAmbientLighting(math::Vector3::kGrey * 0.5f);

	World* world = engine->GetWorldManager()->CreateWorld("World");
	world->SetAmbientLighting(math::Vector3::kGrey * 0.5f);

	if (!LoadMaterials(engine->GetRenderer()) || !SetupScene(world))
	{
		engine->ShutDown();
		return 0;
	}

	//Add Systems
	world->AddSystem<Lighting3DSystem>();	//Lighting must go first
	world->AddSystem<Render3DSystem>();
	//world->AddSystem<CameraSystem>();
	world->AddSystem<FloorSystem>();
	world->AddSystem<SpawnerSystem>();
	world->AddSystem<MovementSystem>();
	world->AddSystem<CollisionSystem>();
	world->AddSystem<QuadTreeBuilderSystem>();
	world->AddSystem<ColourSystem>();

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
	mat->SetShader(render::EShaderTechnique::STANDARD);
	mat->SetMainTexture(renderer->LoadTexture("White.png"));
	mat->SetDiffuseColour(math::Vector3::kOne * 0.3f);

	mat = renderer->LoadMaterial("NonCollidedMat");
	mat->SetShader(render::EShaderTechnique::ONE_COLOUR);
	mat->SetDiffuseColour(math::Vector3::kBlack);

	mat = renderer->LoadMaterial("CollidedMat");
	mat->SetShader(render::EShaderTechnique::ONE_COLOUR);
	mat->SetDiffuseColour(math::Vector3::kGreen);

	return true;
}

//Create the Entities and load the starting scene
bool SetupScene(World* world)
{
	EntityManager* EntityManager = world->GetEntityManager();

	//Create GUI Bar
	auto guiBar = world->GetRenderer()->CreateGUIBar("GUI");
	guiBar->SetTitle("GUI");
	guiBar->AddVarRW("FPS", EType::FLOAT, &fps);
	guiBar->DefineBar("refresh=1");	//Refresh bar every second (For FPS)

	//Create Global Entity (Holds GUI Bar)
	Entity globalEntity = EntityManager->CreateEntity();
	auto globalData = EntityManager->AddComponent<GlobalComponentData>(globalEntity, guiBar);

	//Create Camera Entity
	Entity cameraEntity = EntityManager->CreateEntity();
	EntityManager->AddComponent<TransformComponentData>(cameraEntity, math::Vector3::kYAxis * 190.0f, math::Quaternion::Euler(90.0f, 0.0f, 0.0f));
	EntityManager->AddComponent<CameraComponentData>(cameraEntity);


	//Setup Lighting
	//Entity lightEntity = EntityManager->CreateEntity();
	//EntityManager->AddComponent<TransformComponentData>(lightEntity);
	//auto lightComp = EntityManager->AddComponent<LightComponentData>(lightEntity, render::ELightType::DIRECTIONAL);
	//lightComp->Brightness = 10.0f;
	//lightComp->Colour = math::Vector3::kWhite;
	//lightComp->Direction = math::Vector3(-1.0f, -1.0f, -1.0f);
	//
	//guiBar->AddVarRW("Light Direction", EType::DIR3, &lightComp->Direction, "group='Lighting'");

	return true;
}