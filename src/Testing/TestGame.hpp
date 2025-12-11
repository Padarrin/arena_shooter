#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Engine/Components/MeshRenderer.h"
#include "../Engine/Components/Light.h"
#include "define.h"

gce::GameObject* gCameraObject;

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

void/*gce::UIButton&*/ CreateButtonStart(gce::Scene& scene)
{
	gce::BitMapBrush imageButtonStart{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageButtonStartCollide{ "res/Testing/Button/Button2.png" };

	// First Button
	gce::GameObject& object = gce::GameObject::Create(scene);
	object.transform.LocalTranslate({ 200.0f, 50.0f, 0.0f });
	object.transform.LocalScale({ 216.0f, 69.0f, 1.0f });

	gce::UIButton& buttonStart = *object.AddComponent<gce::UIButton>();
	buttonStart.AddListener(Start);
	buttonStart.pBitMapBrush = &imageButtonStart;
	buttonStart.pHoverBitMapBrush = &imageButtonStartCollide;
	//return buttonStart;
}

ScriptPlayer* CreatePlayer(gce::Scene& scene, gce::GameObject* cameraObject)
{
	gce::GameObject& gamePlayer = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	ScriptPlayer* player = gamePlayer.GetScript<ScriptPlayer>();

	gamePlayer.AddChild(*cameraObject);
	player->SetCamera(*cameraObject);
	player->WorldTranslate(gce::Vector3f32(30.f, 10.f, 0.f));
	player->mCharacter->SetSpeed(90);
	return player;
}

void CreateEnemy(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid)
{
	gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE);
	ScriptEnemy* enemy = enemyObject.GetScript<ScriptEnemy>();
	enemy->SetPlayer(player);
	enemy->mAgent->mCharacter->SetSpeed(5.f);
	enemy->mAgent->GetPathFinding()->SetGrid(grid);
	enemy->SetCellTarget(grid->GetCell(player->GetWorldPosition()));
	enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(0.f, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, 0.f));
}

void CreateFloor(gce::Scene& scene)
{
	gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
	ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
	entity->SetWorldPosition({ 0.f ,-1.f ,0.f });
	entity->SetWorldScale({ 50.f,0.2f,50.f });
}

ScriptGrid* CreateGrid(gce::Scene& scene, gce::Vector2f32 sizeTabCell, gce::Vector3f32 positionCenter, int sizeCell)
{
	gce::GameObject& gridObject = CreateGameObject<ScriptGrid>(scene, gce::SHAPES.CUBE);
	ScriptGrid* grid = gridObject.GetScript<ScriptGrid>();
	grid->SetCellSize(sizeCell);
	grid->SetSizeTabCell(sizeTabCell); //SetScale et lance InitTab
	grid->SetCenterOfGrid(positionCenter);
	return grid;
}

void Start()
{
	gce::GameObject* cameraObject = gCameraObject;
	gce::Scene& scene = (*gCameraObject->m_pScene);

	ScriptPlayer* player = CreatePlayer(scene, cameraObject);

	gce::Vector3f32 posPlayer = player->GetWorldPosition();
	gce::Vector2f32 sizeGrid = gce::Vector2f32(20.f, 40.f);
	gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 0.5f), posPlayer.z);

	ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

	CreateEnemy(scene, player, grid);

	CreateFloor(scene);

	//createur de gameobject (remplacer les 'x' par le nom de la class + modifier ou supprimer geometry et ou texture)
	//geometry = 
	//texture = 
	//Scriptx* x = CreateGameObject<Scriptx>(scene, geometry, texture);
}


BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gCameraObject = &CreateCamera(scene);

	gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
	gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
	directionalLight.DefaultDirectionLight();
	directionalLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	gce::ColorBrush redBrush{ gce::Color::Red,     1.0f };
	gce::ColorBrush greenBrush{ gce::Color::Green,   1.0f };
	gce::ColorBrush blueBrush{ gce::Color::Blue,    1.0f };
	gce::ColorBrush yellowBrush{ gce::Color::Yellow,  1.0f };

	CreateButtonStart(scene);

	gce::WindowParam windowParam;
	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()



END_TEST(Game)

#endif