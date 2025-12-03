#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
//#include "../Gameplay/Entity.hpp"
#include "../Gameplay/Enemy.hpp"
#include "define.h"


BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gce::D12PipelineObject defaultPso(
		gce::SHADERS.VERTEX,
		gce::SHADERS.PIXEL,
		gce::SHADERS.HULL,
		gce::SHADERS.DOMAIN_,
		gce::SHADERS.ROOT_SIGNATURE
	);

	gce::GameObject& cameraObject = gce::GameObject::Create(scene);
	cameraObject.transform.LocalTranslate({ 0, 0, -10 });
	gce::Camera& camera = *cameraObject.AddComponent<gce::Camera>();
	camera.SetMainCamera();
	camera.SetType(gce::PERSPECTIVE);
	camera.perspective.fov = XM_PIDIV4;
	camera.perspective.nearPlane = 0.001f;
	camera.perspective.farPlane = 500.0f;
	camera.perspective.aspectRatio = 600.0f / 400.0f;
	camera.perspective.up = { 0.0f, 1.0f, 0.0f };

	gce::GameObject& testObject = gce::GameObject::Create(scene);
	testObject.AddScript<ScriptEnemy>();
	gce::MeshRenderer& meshRenderer = *testObject.AddComponent<gce::MeshRenderer>();
	meshRenderer.pGeometry = gce::SHAPES.CUBE;
	meshRenderer.pPso = &defaultPso;

	//gce::GameObject& gameManager = gce::GameObject::Create(scene);
	//gameManager.AddScript<ActiveStateTestManager>()->testObject = &testObject;

	gce::WindowParam windowParam;
	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()



END_TEST(Game)

#endif