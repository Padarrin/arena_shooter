#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include "../Gameplay/UI.hpp"
#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Gameplay/SubMachineGun.hpp"
#include "../Gameplay/Ball.hpp"
#include "../Engine/Components/MeshRenderer.h"
#include "../Engine/Components/Light.h"
#include "../Engine/Components/ColliderBase3D.h"
#include "../Engine/Components/BoxCollider.h"
#include "../Engine/Components/UiImage.h"
#include "define.h"
#include "JsonLoader.hpp"
using namespace gce;

gce::GameObject& CreateCamera(gce::Scene& scene/*, gce::GameObject& weaponParent*/)
{
	gce::GameObject& cameraObject = gce::GameObject::Create(scene);
	//cameraObject.transform.LocalTranslate({ 0, 0, 0 });
	//cameraObject.transform.SetWorldPosition({ 0,0,-10 });
	cameraObject.SetName("Camera");
	//cameraObject.AddChild(weaponParent);

	gce::Camera& camera = *cameraObject.AddComponent<gce::Camera>();
	//camera.SetMainCamera();
	camera.SetType(gce::PERSPECTIVE);
	camera.perspective.fov = XM_PIDIV4;
	camera.perspective.nearPlane = 0.001f;
	camera.perspective.farPlane = 500.0f;
	//camera.perspective.aspectRatio = 600.0f / 400.0f;
	camera.perspective.up = { 0.0f, 1.0f, 0.0f };
	return cameraObject;
}

ScriptPlayer* CreatePlayer(gce::Scene& scene, gce::GameObject& cameraObject)
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
	enemyObject.AddComponent<gce::PhysicComponent>()->SetActive(false);
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

void CreateFloor(gce::Scene& scene, D12PipelineObject* pso)
{
	///////////////////////////////////////////////////////////
	// Map json
	JsonLoader::LoadMap("../../res/Gameplay/Json/map_test.json", &scene, pso);
	///////////////////////////////////////////////////////////

	//gce::GameObject& floorObject;
	//floorObject.AddComponent<gce::BoxCollider>()->SetActive(true);
	//floorObject.AddComponent<gce::PhysicComponent>()->SetActive(false);
	//floorObject.SetName("Floor");

	//ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
	//entity->SetWorldPosition({ 0.f ,-10.f ,0.f });
	//entity->SetWorldScale({ 50.f,16.f,50.f });

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

void CreateAngleGringer(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
{
	gce::GameObject& angleGringerObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
	angleGringerObject.SetName("AngleGringer");

	weaponParent.AddChild(angleGringerObject);

	ScriptSubMachineGun* angleGringer = angleGringerObject.GetScript<ScriptSubMachineGun>();
	angleGringer->mWeapons->mMagazine->SetMaxBullets(30);
	angleGringer->mWeapons->mMagazine->SetShootTime(0.1f);
	angleGringer->mWeapons->mMagazine->SetReloadTime(2.5f);
	angleGringer->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

	player->AddWeapon(angleGringer->mWeapons);

}

ScriptSubMachineGun* CreateSubmachineGun(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
{
	gce::GameObject& subMachineGunObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
	subMachineGunObject.SetName("SubmachineGun");

	weaponParent.AddChild(subMachineGunObject);

	ScriptSubMachineGun* subMachineGun = subMachineGunObject.GetScript<ScriptSubMachineGun>();
	subMachineGun->mWeapons->mMagazine->SetMaxBullets(30);
	subMachineGun->mWeapons->mMagazine->SetShootTime(0.1f);
	subMachineGun->mWeapons->mMagazine->SetReloadTime(2.5f);
	subMachineGun->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

	player->AddWeapon(subMachineGun->mWeapons);//2

	return subMachineGun;
}

void CreateBazooka(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
{
	gce::GameObject& bazookaObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
	bazookaObject.SetName("Bazooka");

	weaponParent.AddChild(bazookaObject);

	ScriptSubMachineGun* bazooka = bazookaObject.GetScript<ScriptSubMachineGun>();
	bazooka->mWeapons->mMagazine->SetMaxBullets(30);
	bazooka->mWeapons->mMagazine->SetShootTime(0.1f);
	bazooka->mWeapons->mMagazine->SetReloadTime(2.5f);
	bazooka->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

	player->AddWeapon(bazooka->mWeapons);

}

//std::vector<ScriptBall*> CreateBall(gce::Scene& scene)
//{
//	int maxBall = 10;
//	float x = 0;
//
//	std::vector<ScriptBall*> balls;
//
//	while (maxBall != 0)
//	{
//		ScriptBall* ball = ScriptBall::CreateBall("PlayerBall", { x,-50,0 }, {0,0,0}, 0, DEFAULT_BALL_DAMAGE, scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
//		balls.push_back(ball);
//		maxBall--;
//		x += 3;
//	}
//
//	return balls;
//}

void CreateUI(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& cameraObject, gce::Vector3f32 pos, gce::Vector3f32 scale)
{
	gce::GameObject& uiObject = CreateGameObject<ScriptUI>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	cameraObject.AddChild(uiObject);
	ScriptUI* ui = uiObject.GetScript<ScriptUI>();
	ui->mEntity->SetWorldPosition(gce::Vector3f32(pos));
	ui->mEntity->SetWorldScale(gce::Vector3f32(scale));
}

BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	D12PipelineObject texturePso(
		SHADERS.VERTEX,
		SHADERS.PIXEL,
		SHADERS.HULL,
		SHADERS.DOMAIN_,
		SHADERS.ROOT_SIGNATURE
	);

	WindowParam windowParam;
	windowParam.title = L"Test Light";
	windowParam.width = 1920;
	windowParam.height = 1080;
	windowParam.isFullScreen = true;

	//gce::GameObject& weaponParent = gce::GameObject::Create(scene);

	

	/*gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
	gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
	directionalLight.DefaultDirectionLight();
	directionalLight.color = { 0.0f, 0.0f, 0.0f, 1.0f };*/

	//ScriptPlayer* player = CreatePlayer(scene, cameraObject);
	//gce::Vector3f32 posPlayer = player->GetWorldPosition();
	//gce::Vector2f32 sizeGrid = gce::Vector2f32(20.f, 40.f);
	//gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 0.5f), posPlayer.z);

	//D12PipelineObject* pso = new D12PipelineObject{ SHADERS.VERTEX, SHADERS.PIXEL, SHADERS.HULL, SHADERS.DOMAIN_, SHADERS.ROOT_SIGNATURE };

	//ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

	//CreateUI(scene, player, cameraObject, { 0.5f, 9.7f, 1.f }, { 0.1f, 0.1f, 0.01f });
	//CreateUI(scene, player, cameraObject, { 0.6f, 9.7f, 1.f }, { 0.08f, 0.08f, 0.01f });

	GameObject& crosshair = GameObject::Create(scene);
	ImageUI& uiImage = *crosshair.AddComponent<ImageUI>();
	Vector2f32 center = { windowParam.width / 2.f, windowParam.height / 2.f };
	Vector2f32 size = { 32, 32 };
	Vector2f32 posUi = center - size * 0.5f;
	uiImage.InitializeImage(posUi, size, 1.f);

	uiImage.btmBrush = new BitMapBrush("res/Textures/test1.png");
	uiImage.btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, { 1.f / 16.f, 1.f / 16.f, 1.f / 16.f }, 0);
	uiImage.SetActive(true);



	HideMouseCursor();
	GameObject& Cube = GameObject::Create(scene);
	MeshRenderer* meshRenderer = Cube.AddComponent<MeshRenderer>();
	meshRenderer->pGeometry = SHAPES.CUBE;
	meshRenderer->pPso = &texturePso;
	Cube.transform.SetWorldPosition({ 0, 0, 10 });

	//gce::GameObject& cameraObject = CreateCamera(scene/*, weaponParent*/);
	GameObject& cameraObject = GameObject::Create(scene);
	Camera* camera = cameraObject.AddComponent<Camera>();
	cameraObject.AddScript<CameraScript>();
	camera->SetType(PERSPECTIVE);
	camera->perspective.fov = XM_PIDIV4;
	camera->perspective.nearPlane = 0.001f;
	camera->perspective.farPlane = 500.0f;
	camera->perspective.up = { 0.0f, 1.0f, 0.0f };
	//CreateEnemy(scene, player, grid);

	//CreateFloor(scene, pso);
	//
	//CreateAngleGringer(scene, player, weaponParent);
	//
	//ScriptSubMachineGun* weapon = CreateSubmachineGun(scene, player, weaponParent);
	//weapon->SetBall(CreateBall(scene));

	//CreateBazooka(scene, player, weaponParent);
	//
	//player->SetCurrentWeapon(WEAPON_ORDER::SUBMACHINEGUN);

	//createur de gameobject (remplacer les 'x' par le nom de la class + modifier ou supprimer geometry et ou texture)
	//geometry = 
	//texture = 
	//Scriptx* x = CreateGameObject<Scriptx>(scene, geometry, texture);

	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()

DECLARE_SCRIPT(CameraScript, ScriptFlag::Update)

void Update() override
{
	if (m_pOwner == nullptr) return;

	float32 const deltaTime = GameManager::DeltaTime();

	// Position
	Vector3f32 translation{};
	translation += m_pOwner->transform.GetLocalRight() * static_cast<float32>(GetKey(Keyboard::D) - GetKey(Keyboard::Q));
	translation += m_pOwner->transform.GetLocalUp() * static_cast<float32>(GetKey(Keyboard::SPACE) - GetKey(Keyboard::LCONTROL));
	translation += m_pOwner->transform.GetLocalForward() * static_cast<float32>(GetKey(Keyboard::Z) - GetKey(Keyboard::S));
	translation *= deltaTime;

	// Scale
	float32 const allScale = static_cast<float32>(GetKey(Keyboard::NUMPAD_ADD) - GetKey(Keyboard::NUMPAD_SUBTRACT));

	Vector3f32 scale;
	scale.x = static_cast<float32>(GetKey(Keyboard::INSERT) - GetKey(Keyboard::DELETE_)) + allScale;
	scale.y = static_cast<float32>(GetKey(Keyboard::HOME) - GetKey(Keyboard::END)) + allScale;
	scale.z = static_cast<float32>(GetKey(Keyboard::PAGE_UP) - GetKey(Keyboard::PAGE_DOWN)) + allScale;
	scale *= deltaTime;

	Vector3f32 one;
	one.SetOne();
	scale += one;

	Vector2i32 const middlePosition(GameManager::GetWindow()->GetWidth() / 2, GameManager::GetWindow()->GetHeight() / 2);

	Vector2i32 mouseDirection = GetMousePosition();
	mouseDirection.x -= middlePosition.x;
	mouseDirection.y -= middlePosition.y;

	SetMousePosition(middlePosition);

	// Rotation
	Vector3f32 localRotation{
		static_cast<float32>(mouseDirection.y),
		0.0f,
		static_cast<float32>(GetKey(Keyboard::NUMPAD7) - GetKey(Keyboard::NUMPAD9))
	};
	localRotation *= 3.14f / 180.0f * deltaTime * 5.0f;

	Vector3f32 worldRotation{
		0.0f,
		static_cast<float32>(mouseDirection.x),
		0.0f
	};
	worldRotation *= 3.14f / 180.0f * deltaTime * 5.0f;

	m_pOwner->transform.LocalTranslate(translation);
	m_pOwner->transform.LocalScale(scale);
	m_pOwner->transform.LocalRotate(localRotation);
	m_pOwner->transform.WorldRotate(worldRotation);
}

END_SCRIPT

END_TEST(Game)

#endif