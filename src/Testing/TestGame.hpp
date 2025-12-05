#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include "../Gameplay/Enemy.hpp"
#include "define.h"

gce::GameObject& CreateCamera(gce::Scene& scene)
{
		gce::GameObject& cameraObject = gce::GameObject::Create(scene);
	cameraObject.transform.LocalTranslate({ 0, 0, 0 });
	gce::Camera& camera = *cameraObject.AddComponent<gce::Camera>();
	camera.SetMainCamera();
	camera.SetType(gce::PERSPECTIVE);
	camera.perspective.fov = XM_PIDIV4;
	camera.perspective.nearPlane = 0.001f;
	camera.perspective.farPlane = 500.0f;
	camera.perspective.aspectRatio = 600.0f / 400.0f;
	camera.perspective.up = { 0.0f, 1.0f, 0.0f };
	return cameraObject;
}

ScriptPlayer* CreatePlayer(gce::GameObject& cameraObject, gce::Scene& scene)
{
	gce::GameObject& gamePlayer = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE);
	ScriptPlayer* player = gamePlayer.GetScript<ScriptPlayer>();

	gamePlayer.AddChild(cameraObject);
	player->SetCamera(cameraObject);
	player->WorldTranslate(gce::Vector3f32(-3.f, 0.f, 0.f));
	player->mCharacter->SetSpeed(90);
	return player;
}

void CreateEnemy(gce::Scene& scene, ScriptPlayer* player)
{
	gce::GameObject& cameraObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE);
	ScriptEnemy* enemy = cameraObject.GetScript<ScriptEnemy>();
	enemy->SetPlayer(player);
}

void CreateFloor(gce::Scene& scene)
{
	gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
	ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
	entity->SetWorldPosition({ 0.f ,-1.f ,0.f });
	entity->SetWorldScale({ 50.f,0.2f,50.f });
}


BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gce::GameObject& cameraObject = CreateCamera(scene);

	ScriptPlayer* player = CreatePlayer(cameraObject, scene);

	CreateEnemy(scene, player);

	CreateFloor(scene);

	//createur de gameobject (remplacer les 'x' par le nom de la class + modifier ou supprimer geometry et ou texture)
	//geometry = 
	//texture = 
	//Scriptx* x = CreateGameObject<Scriptx>(scene, geometry, texture);

	gce::WindowParam windowParam;
	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()



END_TEST(Game)

#endif