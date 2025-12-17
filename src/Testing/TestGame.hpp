#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED


#include <Render.h>
#include <Engine.h>

#include "../Gameplay/UI.hpp"
#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/StaticGeometry.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Gameplay/SubMachineGun.hpp"
#include "../Gameplay/Ball.hpp"
#include "../Gameplay/Menu.hpp"
#include "../Gameplay/Functions.h"
#include "../Engine/Components.h"
#include "define.h"
#include "JsonLoader.hpp"
using namespace gce;

gce::GameObject* gCameraObject;
gce::GameObject* gMenuObject;
gce::GameObject* gPlayerObject;


BEGIN_TEST(Game)

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	WindowParam windowParam;
	windowParam.title = L"Test Light";
	windowParam.width = 1920;
	windowParam.height = 1080;
	windowParam.isFullScreen = true;

	gCameraObject = CreateCamera(scene);

	gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
	gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
	directionalLight.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	directionalLight.DefaultDirectionLight();
	
	//	//	//	//	 Menu   //	//	//	//
	gce::GameObject& menuObject = CreateGameObject<ScriptMenu>(scene);
	ScriptMenu* menu = menuObject.GetScript<ScriptMenu>();

	gPlayerObject = &CreatePlayer(scene, gCameraObject);

	////Main Menu////
	//Image
	gce::BitMapBrush imageButtonStart{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonStart{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonQuit{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonQuit{ "res/Testing/Button/Button2.png" };

	gce::Vector3f32 posImageMainMenu = gce::Vector3f32(600.f, 400.f, 5.f)/* + posCameraInMenu*/;
	gce::Vector3f32 scaleImageMainMenu = gce::Vector3f32(1000.f, 1000.f, 1.f);
	gce::BitMapBrush imageBackgroundButtonMainMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imageMainMenuObject = gce::GameObject::Create(scene); imageMainMenuObject.transform.LocalTranslate(posImageMainMenu); imageMainMenuObject.transform.SetWorldScale(scaleImageMainMenu); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
	gce::UIButton* imageMainMenu = imageMainMenuObject.AddComponent<gce::UIButton>(); imageMainMenu->pBitMapBrush = &imageBackgroundButtonMainMenu; imageMainMenu->pHoverBitMapBrush = &imageBackgroundButtonMainMenu;

	//Start Button
	gce::Vector3f32 posButtonStart = gce::Vector3f32(600.0f, 300.0f, 0.0f);
	gce::Vector3f32 scaleButtonStart = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonStartObject = gce::GameObject::Create(scene); buttonStartObject.transform.LocalTranslate(posButtonStart); buttonStartObject.transform.LocalScale(scaleButtonStart);
	gce::UIButton* buttonStart = buttonStartObject.AddComponent<gce::UIButton>(); buttonStart->AddListener(TestGame::Start); buttonStart->pBitMapBrush = &imageButtonStart; buttonStart->pHoverBitMapBrush = &imageCollideButtonStart;

	//Quit Button
	gce::Vector3f32 posButtonQuit = gce::Vector3f32(600.0f, 500.0f, 0.0f);
	gce::Vector3f32 scaleButtonQuit = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonQuitObject = gce::GameObject::Create(scene); buttonQuitObject.transform.LocalTranslate(posButtonQuit); buttonQuitObject.transform.LocalScale(scaleButtonQuit);
	gce::UIButton* buttonQuit = buttonQuitObject.AddComponent<gce::UIButton>(); buttonQuit->AddListener(TestGame::Quit); buttonQuit->pBitMapBrush = &imageButtonQuit; buttonQuit->pHoverBitMapBrush = &imageCollideButtonQuit;
	////Pause Menu////
	//Image
	gce::BitMapBrush imageButtonResume{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonResume{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonRestart{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonRestart{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonExit{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonExit{ "res/Testing/Button/Button2.png" };

	gce::Vector3f32 posImagePauseMenu = gce::Vector3f32(600.f, 400.f, 5.f);
	gce::Vector3f32 scaleImagePauseMenu = gce::Vector3f32(1000.f, 1000.f, 1.f);
	gce::BitMapBrush imageBackgroundButtonPauseMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imagePauseMenuObject = gce::GameObject::Create(scene); imagePauseMenuObject.transform.LocalTranslate(posImagePauseMenu); imagePauseMenuObject.transform.SetWorldScale(scaleImagePauseMenu); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
	gce::UIButton* imagePauseMenu = imagePauseMenuObject.AddComponent<gce::UIButton>(); imagePauseMenu->pBitMapBrush = &imageBackgroundButtonPauseMenu; imagePauseMenu->pHoverBitMapBrush = &imageBackgroundButtonPauseMenu;
	
	//Resume Button
	gce::Vector3f32 posButtonResume = gce::Vector3f32(600.0f, 200.0f, 0.0f);
	gce::Vector3f32 scaleButtonResume = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonResumeObject = gce::GameObject::Create(scene); buttonResumeObject.transform.LocalTranslate(posButtonResume); buttonResumeObject.transform.LocalScale(scaleButtonResume);
	gce::UIButton* buttonResume = buttonResumeObject.AddComponent<gce::UIButton>(); buttonResume->AddListener(TestGame::Resume); buttonResume->pBitMapBrush = &imageButtonResume; buttonResume->pHoverBitMapBrush = &imageCollideButtonResume;
	
	//Restart Button
	gce::Vector3f32 posButtonRestart = gce::Vector3f32(600.0f, 400.0f, 0.0f);
	gce::Vector3f32 scaleButtonRestart = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonRestartObject = gce::GameObject::Create(scene); buttonRestartObject.transform.LocalTranslate(posButtonRestart); buttonRestartObject.transform.LocalScale(scaleButtonRestart);
	gce::UIButton* buttonRestart = buttonRestartObject.AddComponent<gce::UIButton>(); buttonRestart->AddListener(TestGame::Restart); buttonRestart->pBitMapBrush = &imageButtonRestart; buttonRestart->pHoverBitMapBrush = &imageCollideButtonRestart;
	
	//Exit Button
	gce::Vector3f32 posButtonExit = gce::Vector3f32(600.0f, 600.0f, 0.0f);
	gce::Vector3f32 scaleButtonExit = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonExitObject = gce::GameObject::Create(scene); buttonExitObject.transform.LocalTranslate(posButtonExit); buttonExitObject.transform.LocalScale(scaleButtonExit);
	gce::UIButton* buttonExit = buttonExitObject.AddComponent<gce::UIButton>(); buttonExit->AddListener(TestGame::Exit); buttonExit->pBitMapBrush = &imageButtonExit; buttonExit->pHoverBitMapBrush = &imageCollideButtonExit;
	
	//// WinLose Menu ////
	//Image
	gce::BitMapBrush imageButtonReplay{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonReplay{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonEnd{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonEnd{ "res/Testing/Button/Button2.png" };

	gce::Vector3f32 posImageWinLoseMenu = gce::Vector3f32(600.f, 400.f, 5.f)/* + posCameraInMenu*/;
	gce::Vector3f32 scaleImageWinLoseMenu = gce::Vector3f32(1000.f, 1000.f, 1.f);
	gce::BitMapBrush imageBackgroundButtonWinLoseMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imageWinLoseMenuObject = gce::GameObject::Create(scene); imageWinLoseMenuObject.transform.LocalTranslate(posImageWinLoseMenu); imageWinLoseMenuObject.transform.SetWorldScale(scaleImageWinLoseMenu); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
	gce::UIButton* imageWinLoseMenu = imageWinLoseMenuObject.AddComponent<gce::UIButton>(); imageWinLoseMenu->pBitMapBrush = &imageBackgroundButtonWinLoseMenu; imageWinLoseMenu->pHoverBitMapBrush = &imageBackgroundButtonWinLoseMenu;

	//Replay Button
	gce::Vector3f32 posButtonReplay = gce::Vector3f32(600.0f, 200.0f, 0.0f);
	gce::Vector3f32 scaleButtonReplay = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonReplayObject = gce::GameObject::Create(scene); buttonReplayObject.transform.LocalTranslate(posButtonReplay); buttonReplayObject.transform.LocalScale(scaleButtonReplay);
	gce::UIButton* buttonReplay = buttonReplayObject.AddComponent<gce::UIButton>(); buttonReplay->AddListener(TestGame::Restart); buttonReplay->pBitMapBrush = &imageButtonReplay; buttonReplay->pHoverBitMapBrush = &imageCollideButtonReplay;

	//End Button
	gce::Vector3f32 posButtonEnd = gce::Vector3f32(600.0f, 800.0f, 0.0f);
	gce::Vector3f32 scaleButtonEnd = gce::Vector3f32(216.0f, 69.0f, 1.0f);
	gce::GameObject& buttonEndObject = gce::GameObject::Create(scene); buttonEndObject.transform.LocalTranslate(posButtonEnd); buttonEndObject.transform.LocalScale(scaleButtonEnd);
	gce::UIButton* buttonEnd = buttonEndObject.AddComponent<gce::UIButton>(); buttonEnd->AddListener(TestGame::Quit); buttonEnd->pBitMapBrush = &imageButtonEnd; buttonEnd->pHoverBitMapBrush = &imageCollideButtonEnd;

	menu->AddImage(&imageMainMenuObject, MAIN_MENU);
	menu->AddButton(&buttonStartObject, MAIN_MENU);
	menu->AddButton(&buttonQuitObject, MAIN_MENU);

	menu->AddImage(&imagePauseMenuObject, PAUSE_MENU);
	menu->AddButton(&buttonResumeObject, PAUSE_MENU);
	menu->AddButton(&buttonRestartObject, PAUSE_MENU);
	menu->AddButton(&buttonExitObject, PAUSE_MENU);

	menu->AddImage(&imageWinLoseMenuObject, WINLOSE_MENU);
	menu->AddButton(&buttonReplayObject, WINLOSE_MENU);
	menu->AddButton(&buttonEndObject, WINLOSE_MENU);

	menu->ShowMenu(MAIN_MENU);
	gMenuObject = &menuObject;
	//	//	//	//	 Menu Fin   //	//	//	//

	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()

public:

	static gce::GameObject* CreateCamera(gce::Scene& scene)
	{
		gce::GameObject& cameraObject = gce::GameObject::Create(scene);
		gce::Camera& camera = *cameraObject.AddComponent<gce::Camera>();
		cameraObject.SetName("Camera");
		ResetCamera(&cameraObject);
		return &cameraObject;
	}

	static void ResetCamera(gce::GameObject* cameraObject)
	{
		cameraObject->transform.SetWorldPosition({ 0.f, 0.f, 0.f });
		cameraObject->transform.SetLocalPosition({ 0.f, 0.f, 0.f });

		cameraObject->transform.SetWorldRotation({ 0.f, 0.f, 0.f });
		cameraObject->transform.SetLocalRotation({ 0.f, 0.f, 0.f });

		cameraObject->transform.SetWorldScale({ 1.f, 1.f, 1.f });
		cameraObject->transform.SetLocalScale({ 1.f, 1.f, 1.f });
		
		gce::Camera& camera = *cameraObject->GetComponent<gce::Camera>();
		camera.SetMainCamera();
		camera.SetType(gce::PERSPECTIVE);
		camera.perspective.fov = XM_PIDIV4;
		camera.perspective.nearPlane = 0.001f;
		camera.perspective.farPlane = 500.0f;
		camera.perspective.aspectRatio = 600.0f / 400.0f;
		camera.perspective.up = { 0.0f, 1.0f, 0.0f };
	}

	static gce::GameObject& CreatePlayer(gce::Scene& scene, gce::GameObject* cameraObject)
	{
		gce::GameObject& playerObject = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		playerObject.AddComponent<gce::BoxCollider>()->SetActive(true);
		playerObject.AddComponent<gce::PhysicComponent>()->SetActive(true);
		playerObject.SetName("Player");
		playerObject.AddChild(*cameraObject);

		ScriptPlayer* player = playerObject.GetScript<ScriptPlayer>();
		ResetPlayerBegin(player, cameraObject);
		return playerObject;
	}

	static void ResetPlayerBegin(ScriptPlayer* player, gce::GameObject* cameraObject)
	{
		player->Initia();
		player->SetCamera(cameraObject);
		player->SetWorldPosition(gce::Vector3f32(0.f, 10.f, 0.f));
		player->mCharacter->SetSpeed(9.f);
		player->SetJump(6.f);
	}

	static void ResetPlayerEnd(ScriptPlayer* player)
	{
		player->SetCurrentWeapon(WEAPON_ORDER::SUBMACHINEGUN);
		player->Start();
	}

	static void CreateNail(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptPlayer* player, ScriptGrid* grid)
	{
		//Life = 20 a 200, Damage = 1 a 5
		gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		enemyObject.SetName("Enemy");

		SetNail(&enemyObject, player, grid);

	}

	static void SetNail(/*gce::Scene& scene,*/gce::GameObject*/*&*/ enemyObject, ScriptPlayer* player, ScriptGrid* grid)
	{
		//Life = 20 a 200, Damage = 1 a 5
		//gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE);
		enemyObject->AddComponent<gce::BoxCollider>()->SetActive(true);
		enemyObject->AddComponent<gce::PhysicComponent>()->SetActive(false);
		//enemyObject.SetName("Enemy");

		ScriptEnemy* enemy = nullptr;
		if (enemyObject->HasScript<ScriptEnemy>())
		{
			enemy = enemyObject->GetScript<ScriptEnemy>();
		}
		else
		{
			enemy = enemyObject->AddScript<ScriptEnemy>();
		}
		//ScriptEnemy* enemy = enemyObject->GetScript<ScriptEnemy>();
		enemy->SetWorldPosition({ 10,-8,10 });
		enemy->SetPlayer(player);
		enemy->SetMaxLife(20);
		enemy->SetDamage(10);
		enemy->mAgent->mCharacter->SetSpeed(5.f);
		enemy->mAgent->GetPathFinding()->SetGrid(grid);
		enemy->SetCellTarget(grid->GetNearestCell(player->GetWorldPosition()));
		enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(0.f, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, 0.f));
		
	}

	static void CreateStaticObject(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptGrid* grid, bool isFix, bool isObstacle)
	{
		gce::GameObject& staticObject = CreateGameObject<ScriptStaticGeometry>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		staticObject.SetName("StaticObject");

		SetStaticObject(&staticObject, grid, isFix, isObstacle);

	}

	static void SetStaticObject(/*gce::Scene& scene,*/gce::GameObject* staticObject, ScriptGrid* grid, bool isFix, bool isObstacle)
	{
		//gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
		staticObject->AddComponent<gce::BoxCollider>()->SetActive(true);
		//enemyObject.SetName("Enemy");

		ScriptStaticGeometry* staticGeometry = nullptr;
		if (staticObject->HasScript<ScriptStaticGeometry>())
		{
			staticGeometry = staticObject->GetScript<ScriptStaticGeometry>();
		}
		else
		{
			staticGeometry = staticObject->AddScript<ScriptStaticGeometry>();
		}
		staticGeometry->SetAll(grid, isFix, isObstacle);
	}


	static void CreateMap(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid)
	{
		///////////////////////////////////////////////////////////
		// Map json
		std::vector<gce::GameObject*> gameObjectLoad = JsonLoader::LoadMap(RES_PATH"res/Gameplay/Json/map_test.json", &scene);

		int lenghtLoad = (int)gameObjectLoad.size();
		for (int i = 0; i < lenghtLoad; i++)
		{
			gce::GameObject* currentGameObject= gameObjectLoad[i];
			
			//////////////////////Enemy///////////////////////
			if (currentGameObject->GetName() == "Nail")
			{
				currentGameObject->SetName("Enemy");
				SetNail(currentGameObject, player, grid);
			}
			else if (currentGameObject->GetName() == "Bot")
			{
				currentGameObject->SetName("Bot");
				//SetNail(currentGameObject, player, grid);
			}
			//////////////////////Enemy Fin///////////////////////
			//////////////////////Item///////////////////////
			else if (currentGameObject->GetName() == "Item")
			{
				currentGameObject->SetName("Item");
				//SetNail(currentGameObject, player, grid);
			}
			//////////////////////Item Fin///////////////////////
			//////////////////////Furniture///////////////////////
			else if (currentGameObject->GetName() == "Box")
			{
				currentGameObject->SetName("Box");
				//SetNail(currentGameObject, player, grid);
			}
			//////////////////////Furniture Fin///////////////////////
			//////////////////////Floor///////////////////////
			else
			{
				if (currentGameObject->GetName() == "Wall")
				{
					bool isFix = false; 
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
				else if (currentGameObject->GetName() == "Floor" || currentGameObject->GetName() == "Roof")
				{
					bool isFix = false;
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
				else if (currentGameObject->GetName() == "Door")
				{
					bool isFix = false;
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
			}
			//////////////////////Floor Fin///////////////////////
		}
		///////////////////////////////////////////////////////////

	}

	static ScriptGrid* CreateGrid(gce::Scene& scene, gce::Vector2f32 sizeTabCell, gce::Vector3f32 positionCenter, int sizeCell)
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

	static void CreateAngleGringer(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
	{
		gce::GameObject& angleGringerObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
		angleGringerObject.SetName("AngleGringer");
		weaponParent.AddChild(angleGringerObject);

		ScriptSubMachineGun* angleGringer = angleGringerObject.GetScript<ScriptSubMachineGun>();
		angleGringer->mWeapons->mMagazine->SetMaxBullets(30);
		angleGringer->mWeapons->mMagazine->SetShootTime(0.1f);
		angleGringer->mWeapons->mMagazine->SetReloadTime(2.5f);
		angleGringer->mWeapons->mEntity->SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		angleGringer->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

		player->AddWeapon(angleGringer->mWeapons);//1
	}

	static ScriptSubMachineGun* CreateSubmachineGun(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
	{
		gce::GameObject& subMachineGunObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
		subMachineGunObject.SetName("SubmachineGun");

		weaponParent.AddChild(subMachineGunObject);

		ScriptSubMachineGun* subMachineGun = subMachineGunObject.GetScript<ScriptSubMachineGun>();
		subMachineGun->mWeapons->mMagazine->SetMaxBullets(30);
		subMachineGun->mWeapons->mMagazine->SetShootTime(0.1f);
		subMachineGun->mWeapons->mMagazine->SetReloadTime(2.5f);
		subMachineGun->mWeapons->mEntity->SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		subMachineGun->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

		player->AddWeapon(subMachineGun->mWeapons);//2

		return subMachineGun;
	}

	static void CreateBazooka(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
	{
		gce::GameObject& bazookaObject = CreateGameObject<ScriptSubMachineGun>(scene, gce::SHAPES.CUBE);
		bazookaObject.SetName("Bazooka");

		weaponParent.AddChild(bazookaObject);

		ScriptSubMachineGun* bazooka = bazookaObject.GetScript<ScriptSubMachineGun>();
		bazooka->mWeapons->mMagazine->SetMaxBullets(30);
		bazooka->mWeapons->mMagazine->SetShootTime(0.1f);
		bazooka->mWeapons->mMagazine->SetReloadTime(2.5f);
		bazooka->mWeapons->mEntity->SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		bazooka->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));

		player->AddWeapon(bazooka->mWeapons);//3

	}

	static gce::GameObject& CreateUI(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		ImageUI* uiImage = crosshair.AddComponent<ImageUI>();

		Vector2f32 posUi = pos - size * 0.5f;

		uiImage->InitializeImage(posUi, size, 1.f);

		uiImage->btmBrush = new BitMapBrush(path);
		uiImage->btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, scale, 0);
		uiImage->SetActive(true);

		/*GameObject& Cube = GameObject::Create(scene);
		MeshRenderer* meshRenderer = Cube.AddComponent<MeshRenderer>();
		meshRenderer->pGeometry = SHAPES.CUBE;
		meshRenderer->pPso = &texturePso;
		Cube.transform.SetWorldPosition({ 0, 0, 10 });*/

		return crosshair;
	}

	static void Start()
	{
		D12PipelineObject texturePso(
			SHADERS.VERTEX,
			SHADERS.PIXEL,
			SHADERS.HULL,
			SHADERS.DOMAIN_,
			SHADERS.ROOT_SIGNATURE
		);

		gce::GameObject* cameraObject = gCameraObject;
		gce::Scene& scene = *(gCameraObject->m_pScene);
		gce::GameObject* playerObject = gPlayerObject;

		gce::GameObject* menuObject = gMenuObject;
		ScriptMenu* menu = menuObject->GetScript<ScriptMenu>();
		menu->HideMenu();
		menu->SetInterfaceShow(NOTHING);

		ResetCamera(cameraObject);

		//ImageData data = ImageLoader::LoadTexture(String(RES_PATH) + path);

		ScriptPlayer* player = playerObject->GetScript<ScriptPlayer>();
		ResetPlayerBegin(player, cameraObject);

		gce::GameObject& weaponParent = gce::GameObject::Create(scene);
		cameraObject->AddChild(weaponParent);

		gce::GameObject& uiObject = gce::GameObject::Create(scene);
		ScriptUI* ui = uiObject.AddScript<ScriptUI>();
		ui->SetPlayer(player);

		std::string anglegringerPath = "res/Textures/plastic_normal.png";
		std::string submachineGunPath = "res/Textures/test1.png";
		std::string bazookaPath = "res/Textures/plastic_roughness.png";

		gce::WindowParam windowParam = gce::GameManager::GetWindowParam();

		gce::GameObject& mainWeapon = CreateUI(scene, { windowParam.width -430.f,windowParam.height - 275.f }, { 72,72 }, { 1.f / 14.f, 1.f / 14.f, 1.f / 14.f }, submachineGunPath, texturePso);
		gce::GameObject& secondWeapon = CreateUI(scene, { windowParam.width - 350.f,windowParam.height - 275.f }, { 65,65 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, anglegringerPath, texturePso);
		gce::GameObject& thirdWeapon = CreateUI(scene, { windowParam.width - 275.f,windowParam.height - 275.f }, { 65,65 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, bazookaPath, texturePso);
		ui->AddTexture(mainWeapon);
		ui->AddTexture(secondWeapon);
		ui->AddTexture(thirdWeapon);

		ui->AddImage(anglegringerPath);
		ui->AddImage(submachineGunPath);
		ui->AddImage(bazookaPath);

		gce::Vector3f32 posPlayer = gce::Vector3f32(0.f, 10.f, 0.f);
		gce::Vector2f32 sizeGrid = gce::Vector2f32(40.f, 80.f);
		gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 2.5f), posPlayer.z + 20.f);

		ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

		CreateNail(scene, player, grid);

		CreateMap(scene, player, grid);

		CreateAngleGringer(scene, player, weaponParent);
		CreateSubmachineGun(scene, player, weaponParent);
		CreateBazooka(scene, player, weaponParent);

		ResetPlayerEnd(player);
	}

	static void Quit()
	{
		gce::GameManager::Destroy();
	}

	static void Resume()
	{
		ScriptMenu* menu = gMenuObject->GetScript<ScriptMenu>();
		menu->HideMenu();
		menu->SetInterfaceShow(NOTHING);
	}
	
	static void Restart()
	{
		DeleteGameObject();
		Start();
	}

	static void Exit()
	{
		ScriptMenu* menu = gMenuObject->GetScript<ScriptMenu>();
		DeleteGameObject();
		menu->ShowMenu(MAIN_MENU);
	}

	/*using Function = void(*)();
	static gce::GameObject& CreateButton(gce::Scene& scene, gce::Vector3f32 pos, gce::Vector3f32 scale, gce::BitMapBrush imageButton, gce::BitMapBrush imageButtonCollide, Function fonctionUse)
	{
		gce::GameObject& buttonObject = gce::GameObject::Create(scene);
		buttonObject.transform.LocalTranslate(pos);
		buttonObject.transform.LocalScale(scale);

		gce::UIButton* button = buttonObject.AddComponent<gce::UIButton>();
		button->AddListener(fonctionUse);
		button->pBitMapBrush = &imageButton;
		button->pHoverBitMapBrush = &imageButtonCollide;
		return buttonObject;
	}*/
	static void DeleteGameObject()
	{
		auto* mapGameObject = gMenuObject->m_pScene->GetGameObject();
		//gCameraObject->RemoveParent();
		for (auto& [id, gameObject] : *mapGameObject)
		{
			if ((gameObject->GetScript<ScriptEntity>() != nullptr && gameObject->GetScript<ScriptPlayer>() == nullptr) || gameObject->GetScript<ScriptGrid>() != nullptr)
			{
				gameObject->SetActive(false);
			}
		}
		/*gCameraObject->RemoveParent();
		for (auto it = mapGameObject->begin(); it != mapGameObject->end(); )
		{
			gce::GameObject* gameObject = it->second;
			if (gameObject->GetScript<ScriptEntity>() != nullptr || gameObject->GetScript<ScriptGrid>() != nullptr)
			{
				if (gameObject->HasChildren())
				{
					gce::Vector<gce::GameObject*> child = gameObject->GetChildren();
					int lenght = (int)child.Size() - 1;
					for (int i = lenght; i > -1; i--)
					{
						gameObject->RemoveChild(*child[i]);
					}
				}
				gameObject->Destroy();
				it = mapGameObject->erase(it);
			}
			else
			{
				++it;
			}
			
		}*/
	}

END_TEST(Game)

#endif