#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Engine/Components/MeshRenderer.h"
#include "../Engine/Components/Light.h"
#include "../Engine/Components/ColliderBase3D.h"
#include "../Engine/Components/BoxCollider.h"
#include "define.h"

gce::GameObject& CreateCamera(gce::Scene& scene)
{
	gce::GameObject& cameraObject = gce::GameObject::Create(scene);
	cameraObject.transform.LocalTranslate({ 0, 0, 0 });
	cameraObject.SetName("Camera");
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
	gce::GameObject& gamePlayer = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	gamePlayer.AddComponent<gce::BoxCollider>()->SetActive(true);
	gamePlayer.AddComponent<gce::PhysicComponent>()->SetActive(true);
	gamePlayer.SetName("Player");
	gamePlayer.AddChild(cameraObject);

	ScriptPlayer* player = gamePlayer.GetScript<ScriptPlayer>();
	player->SetWorldPosition(gce::Vector3f32(0.f, 10.f, 0.f));
	player->mCharacter->SetSpeed(9);
	player->SetJump(6.f);

	return player;
}

void CreateEnemy(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid)
{
	//Life = 20 a 200, Damage = 1 a 5
	gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE);
	enemyObject.AddComponent<gce::BoxCollider>()->SetActive(true);
	enemyObject.SetName("Enemy");

	
	ScriptEnemy* enemy = enemyObject.GetScript<ScriptEnemy>();
	enemy->SetWorldPosition({ 10,-8,10 });
	enemy->SetPlayer(player);
	enemy->SetMaxLife(20);
	enemy->SetDamage(10);
	enemy->mAgent->mCharacter->SetSpeed(5.f);
	enemy->mAgent->GetPathFinding()->SetGrid(grid);
	enemy->SetCellTarget(grid->GetCell(player->GetWorldPosition()));
	enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(0.f, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, 0.f));
}

void CreateFloor(gce::Scene& scene)
{
	gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
	floorObject.AddComponent<gce::BoxCollider>()->SetActive(true);
	floorObject.SetName("Floor");

	ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
	entity->SetWorldPosition({ 0.f ,-10.f ,0.f });
	entity->SetWorldScale({ 50.f,16.f,50.f });
}

ScriptGrid* CreateGrid(gce::Scene& scene, gce::Vector2f32 sizeTabCell, gce::Vector3f32 positionCenter, int sizeCell)
{
	gce::GameObject& gridObject = CreateGameObject<ScriptGrid>(scene, gce::SHAPES.CUBE);
	gridObject.AddComponent<gce::BoxCollider>()->SetActive(true);
	gridObject.SetName("Floor");

	ScriptGrid* grid = gridObject.GetScript<ScriptGrid>();
	grid->SetCellSize(sizeCell);
	grid->SetSizeTabCell(sizeTabCell); //SetScale et lance InitTab
	grid->SetCenterOfGrid(positionCenter);

	return grid;
}


BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gce::GameObject& cameraObject = CreateCamera(scene);

	gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
	gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
	directionalLight.DefaultDirectionLight();
	directionalLight.color = { 0.0f, 0.0f, 0.0f, 1.0f };

	ScriptPlayer* player = CreatePlayer(cameraObject, scene);
	gce::Vector3f32 posPlayer = player->GetWorldPosition();
	gce::Vector2f32 sizeGrid = gce::Vector2f32(20.f, 40.f);
	gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 0.5f), posPlayer.z);

	ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

	CreateEnemy(scene, player, grid);

	//CreateFloor(scene);

	//createur de gameobject (remplacer les 'x' par le nom de la class + modifier ou supprimer geometry et ou texture)
	//geometry = 
	//texture = 
	//Scriptx* x = CreateGameObject<Scriptx>(scene, geometry, texture);

	gce::WindowParam windowParam;
	/*windowParam.height = 992;
	windowParam.width = 1768;*/
	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()



END_TEST(Game)

#endif