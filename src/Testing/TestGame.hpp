#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include "../Gameplay/Enemy.hpp"
#include "../Engine/Components/ColliderBase3D.h"
#include "../Engine/Components/BoxCollider.h"
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
	gamePlayer.AddComponent<gce::BoxCollider>()->SetActive(true);
	gamePlayer.AddComponent<gce::PhysicComponent>()->SetActive(true);
	gamePlayer.SetName("Player");
	gamePlayer.AddChild(cameraObject);

	ScriptPlayer* player = gamePlayer.GetScript<ScriptPlayer>();
	player->SetCamera(cameraObject);
	player->SetPlayer(gamePlayer);
	player->WorldTranslate(gce::Vector3f32(-3.f, 0.f, 0.f));
	player->mCharacter->SetSpeed(10);
	player->SetJump(6.f);

	return player;
}

void CreateEnemy(gce::Scene& scene, ScriptPlayer* player)
{
	//Life = 20 à 200, Damage = 1 à 5
	gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE); 
	enemyObject.SetName("Enemy");
	ScriptEnemy* enemy = enemyObject.GetScript<ScriptEnemy>();
	enemy->SetPlayer(player);
	enemy->SetMaxLife(20);
	enemy->SetDamage(5);
}

void CreateFloor(gce::Scene& scene)
{
	gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
	floorObject.AddComponent<gce::BoxCollider>()->SetActive(true);
	floorObject.AddComponent<gce::PhysicComponent>()->SetActive(false);
	floorObject.SetName("Floor");

	ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
	entity->SetWorldPosition({ 0.f ,-10.f ,0.f });
	entity->SetWorldScale({ 50.f,0.2f,50.f });

}


BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gce::GameObject& cameraObject = CreateCamera(scene);

	ScriptPlayer* player = CreatePlayer(cameraObject, scene);

	//CreateEnemy(scene, player);

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