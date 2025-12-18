#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED


#include <Render.h>
#include <Engine.h>

#include "../Engine/Components.h"

#include "../Gameplay/UI.hpp"
#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/Bot.hpp"
#include "../Gameplay/StaticGeometry.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Gameplay/SubMachineGun.hpp"
#include "../Gameplay/Ball.hpp"
#include "../Gameplay/Menu.hpp"
#include "../Gameplay/Functions.h"

#include "define.h"
#include "JsonLoader.hpp"

gce::GameObject* gCameraObject;
gce::GameObject* gMenuObject;
gce::GameObject* gPlayerObject;


BEGIN_TEST(Game)

gce::GameManager::Create();
gce::Scene& scene = gce::Scene::Create();

WindowParam windowParam;
windowParam.title = L"Test Light";
windowParam.width = 1700;
windowParam.height = 800;
windowParam.isFullScreen = true;

gCameraObject = CreateCamera(scene);

gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
directionalLight.color = { 0.0f, 0.0f, 0.0f, 1.0f };
directionalLight.DefaultDirectionLight();

//	//	//	//	 Menu   //	//	//	//
gce::GameObject& menuObject = CreateGameObject<ScriptMenu>(scene);
menuObject.SetName("Menu");
ScriptMenu* menu = menuObject.GetScript<ScriptMenu>();

gPlayerObject = &CreatePlayer(scene, gCameraObject, &menuObject);

////Main Menu////
//Image
gce::BitMapBrush imageButtonStart{ "/res/Gameplay/Texture/Jouer.png" };
gce::BitMapBrush imageCollideButtonStart{ "/res/Gameplay/Texture/Jouer_Cliquer.png" };
gce::BitMapBrush imageButtonQuit{ "/res/Gameplay/Texture/Quitter.png" };
gce::BitMapBrush imageCollideButtonQuit{ "/res/Gameplay/Texture/Quitter_Cliquer.png" };

gce::Vector3f32 posImageMainMenu = gce::Vector3f32(875.f, 425.f, 5.f);
gce::Vector3f32 scaleImageMainMenu = gce::Vector3f32(1750.f, 1000.f, 1.f);
gce::BitMapBrush imageBackgroundButtonMainMenu{ "/res/Gameplay/Texture/Menu_Princiapal.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
gce::GameObject& imageMainMenuObject = gce::GameObject::Create(scene); imageMainMenuObject.transform.LocalTranslate(posImageMainMenu); imageMainMenuObject.transform.SetWorldScale(scaleImageMainMenu); imageMainMenuObject.SetName("ImageButton"); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
gce::UIButton* imageMainMenu = imageMainMenuObject.AddComponent<gce::UIButton>(); imageMainMenu->pBitMapBrush = &imageBackgroundButtonMainMenu; imageMainMenu->pHoverBitMapBrush = &imageBackgroundButtonMainMenu;

//Start Button
gce::Vector3f32 posButtonStart = gce::Vector3f32(410.f, 410.f, 0.f);
gce::Vector3f32 scaleButtonStart = gce::Vector3f32(250.f, 125.f, 1.f);
gce::GameObject& buttonStartObject = gce::GameObject::Create(scene); buttonStartObject.transform.LocalTranslate(posButtonStart); buttonStartObject.transform.LocalScale(scaleButtonStart); buttonStartObject.SetName("Button");
gce::UIButton* buttonStart = buttonStartObject.AddComponent<gce::UIButton>(); buttonStart->AddListener(TestGame::Start); buttonStart->pBitMapBrush = &imageButtonStart; buttonStart->pHoverBitMapBrush = &imageCollideButtonStart;

//Quit Button
gce::Vector3f32 posButtonQuit = gce::Vector3f32(410.f, 610.f, 0.f);
gce::Vector3f32 scaleButtonQuit = gce::Vector3f32(250.f, 125.f, 1.f);
gce::GameObject& buttonQuitObject = gce::GameObject::Create(scene); buttonQuitObject.transform.LocalTranslate(posButtonQuit); buttonQuitObject.transform.LocalScale(scaleButtonQuit); buttonQuitObject.SetName("Button");
gce::UIButton* buttonQuit = buttonQuitObject.AddComponent<gce::UIButton>(); buttonQuit->AddListener(TestGame::Quit); buttonQuit->pBitMapBrush = &imageButtonQuit; buttonQuit->pHoverBitMapBrush = &imageCollideButtonQuit;
////Pause Menu////
//Image
gce::BitMapBrush imageButtonResume{ "/res/Gameplay/Texture/Reprendre.png" };
gce::BitMapBrush imageCollideButtonResume{ "/res/Gameplay/Texture/Reprendre_Cliquer.png" };
gce::BitMapBrush imageButtonRestart{ "/res/Gameplay/Texture/Recommencer.png" };
gce::BitMapBrush imageCollideButtonRestart{ "/res/Gameplay/Texture/Recommencer_Cliquer.png" };
gce::BitMapBrush imageButtonExit{ "/res/Gameplay/Texture/Quitter.png" };
gce::BitMapBrush imageCollideButtonExit{ "/res/Gameplay/Texture/Quitter_Cliquer.png" };

gce::Vector3f32 posImagePauseMenu = gce::Vector3f32(600.f, 400.f, 5.f);
gce::Vector3f32 scaleImagePauseMenu = gce::Vector3f32(1000.f, 1000.f, 1.f);
gce::BitMapBrush imageBackgroundButtonPauseMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
gce::GameObject& imagePauseMenuObject = gce::GameObject::Create(scene); imagePauseMenuObject.transform.LocalTranslate(posImagePauseMenu); imagePauseMenuObject.transform.SetWorldScale(scaleImagePauseMenu); imagePauseMenuObject.SetName("ImageButton"); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
gce::UIButton* imagePauseMenu = imagePauseMenuObject.AddComponent<gce::UIButton>(); imagePauseMenu->pBitMapBrush = &imageBackgroundButtonPauseMenu; imagePauseMenu->pHoverBitMapBrush = &imageBackgroundButtonPauseMenu;

//Resume Button
gce::Vector3f32 posButtonResume = gce::Vector3f32(600.0f, 200.0f, 0.0f);
gce::Vector3f32 scaleButtonResume = gce::Vector3f32(200.0f, 100.0f, 1.0f);
gce::GameObject& buttonResumeObject = gce::GameObject::Create(scene); buttonResumeObject.transform.LocalTranslate(posButtonResume); buttonResumeObject.transform.LocalScale(scaleButtonResume); buttonResumeObject.SetName("Button");
gce::UIButton* buttonResume = buttonResumeObject.AddComponent<gce::UIButton>(); buttonResume->AddListener(TestGame::Resume); buttonResume->pBitMapBrush = &imageButtonResume; buttonResume->pHoverBitMapBrush = &imageCollideButtonResume;

//Restart Button
gce::Vector3f32 posButtonRestart = gce::Vector3f32(600.0f, 400.0f, 0.0f);
gce::Vector3f32 scaleButtonRestart = gce::Vector3f32(200.0f, 100.0f, 1.0f);
gce::GameObject& buttonRestartObject = gce::GameObject::Create(scene); buttonRestartObject.transform.LocalTranslate(posButtonRestart); buttonRestartObject.transform.LocalScale(scaleButtonRestart); buttonRestartObject.SetName("Button");
gce::UIButton* buttonRestart = buttonRestartObject.AddComponent<gce::UIButton>(); buttonRestart->AddListener(TestGame::Restart); buttonRestart->pBitMapBrush = &imageButtonRestart; buttonRestart->pHoverBitMapBrush = &imageCollideButtonRestart;

//Exit Button
gce::Vector3f32 posButtonExit = gce::Vector3f32(600.0f, 600.0f, 0.0f);
gce::Vector3f32 scaleButtonExit = gce::Vector3f32(200.0f, 100.0f, 1.0f);
gce::GameObject& buttonExitObject = gce::GameObject::Create(scene); buttonExitObject.transform.LocalTranslate(posButtonExit); buttonExitObject.transform.LocalScale(scaleButtonExit); buttonExitObject.SetName("Button");
gce::UIButton* buttonExit = buttonExitObject.AddComponent<gce::UIButton>(); buttonExit->AddListener(TestGame::Exit); buttonExit->pBitMapBrush = &imageButtonExit; buttonExit->pHoverBitMapBrush = &imageCollideButtonExit;

//// WinLose Menu ////
//Image
gce::BitMapBrush imageButtonReplay{ "/res/Gameplay/Texture/Recommencer.png" };
gce::BitMapBrush imageCollideButtonReplay{ "/res/Gameplay/Texture/Recommencer_Cliquer.png" };
gce::BitMapBrush imageButtonEnd{ "/res/Gameplay/Texture/Quitter.png" };
gce::BitMapBrush imageCollideButtonEnd{ "/res/Gameplay/Texture/Quitter_Cliquer.png" };

gce::Vector3f32 posImageWinMenu = gce::Vector3f32(700.f, 400.f, 5.f);
gce::Vector3f32 scaleImageWinMenu = gce::Vector3f32(1400.f, 800.f, 1.f);
gce::BitMapBrush imageBackgroundButtonWinMenu{ "/res/Gameplay/Texture/Winner.jpg" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
gce::GameObject& imageWinMenuObject = gce::GameObject::Create(scene); imageWinMenuObject.transform.LocalTranslate(posImageWinMenu); imageWinMenuObject.transform.SetWorldScale(scaleImageWinMenu); imageWinMenuObject.SetName("ImageButton"); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
gce::UIButton* imageWinMenu = imageWinMenuObject.AddComponent<gce::UIButton>(); imageWinMenu->pBitMapBrush = &imageBackgroundButtonWinMenu; imageWinMenu->pHoverBitMapBrush = &imageBackgroundButtonWinMenu;

gce::Vector3f32 posImageLoseMenu = gce::Vector3f32(700.f, 400.f, 5.f);
gce::Vector3f32 scaleImageLoseMenu = gce::Vector3f32(1400.f, 800.f, 1.f);
gce::BitMapBrush imageBackgroundButtonLoseMenu{ "/res/Gameplay/Texture/Loser.jpg" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
gce::GameObject& imageLoseMenuObject = gce::GameObject::Create(scene); imageLoseMenuObject.transform.LocalTranslate(posImageLoseMenu); imageLoseMenuObject.transform.SetWorldScale(scaleImageLoseMenu); imageLoseMenuObject.SetName("ImageButton");//AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
gce::UIButton* imageLoseMenu = imageLoseMenuObject.AddComponent<gce::UIButton>(); imageLoseMenu->pBitMapBrush = &imageBackgroundButtonLoseMenu; imageLoseMenu->pHoverBitMapBrush = &imageBackgroundButtonLoseMenu;

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

menu->AddImage(&imageWinMenuObject, WIN_MENU);
menu->AddButton(&buttonReplayObject, WIN_MENU);
menu->AddButton(&buttonEndObject, WIN_MENU);

menu->AddImage(&imageLoseMenuObject, LOSE_MENU);
menu->AddButton(&buttonReplayObject, LOSE_MENU);
menu->AddButton(&buttonEndObject, LOSE_MENU);

menu->ShowMenu(MAIN_MENU);
gMenuObject = &menuObject;
//	//	//	//	 Menu Fin   //	//	//	//

//gce::WindowParam windowParam;
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

	static gce::GameObject& CreatePlayer(gce::Scene& scene, gce::GameObject* cameraObject, gce::GameObject* menuObject)
	{
		gce::GameObject& playerObject = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		playerObject.AddComponent<gce::BoxCollider>()->SetActive(true);
		playerObject.AddComponent<gce::PhysicComponent>()->SetActive(true);
		playerObject.SetName("Player");
		playerObject.AddChild(*cameraObject);

		ScriptPlayer* player = playerObject.GetScript<ScriptPlayer>();
		ResetPlayerBegin(player, cameraObject, menuObject);
		return playerObject;
	}

	static void ResetPlayerBegin(ScriptPlayer* player, gce::GameObject* cameraObject, gce::GameObject* menuObject)
	{
		player->Initia();
		player->SetCamera(cameraObject);
		player->SetMenu(menuObject);
		player->SetWorldPosition(gce::Vector3f32(45.f, 15.f, -55.f));
		player->mCharacter->SetSpeed(9.f);
		player->SetJump(6.f);
		player->mCharacter->SetMaxLife(100);
	}

	static void ResetPlayerEnd(ScriptPlayer* player)
	{
		player->SetCurrentWeapon(WEAPON_ORDER::ANGLEGRINGER);
		player->Start();
	}

	static void CreateBot(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptPlayer* player, ScriptGrid* grid)
	{
		//Life = 20 a 200, Damage = 1 a 5
		gce::GameObject& botObject = CreateGameObject<ScriptBot>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		botObject.SetName("Bot");
		botObject.transform.SetWorldPosition(gce::Vector3f32(-7.f, 1.f, 7.f));
		botObject.transform.SetWorldScale(gce::Vector3f32(1.f, 2.f, 1.f));
	}

	static void CreateNail(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos, const std::string_view path)
	{
		//Life = 20 a 200, Damage = 1 a 5
		Geometry* geo = GeometryFactory::LoadGeometry(path);
		gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, geo, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		enemyObject.SetName("Enemy");

		SetNail(&enemyObject, player, grid, pos);

	}

	static void SetNail(gce::GameObject* enemyObject, ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos)
	{
		//Life = 20 a 200, Damage = 1 a 5
		enemyObject->AddComponent<gce::BoxCollider>()->SetActive(true);
		enemyObject->AddComponent<gce::PhysicComponent>()->SetActive(false);

		ScriptEnemy* enemy = nullptr;
		if (enemyObject->HasScript<ScriptEnemy>())
		{
			enemy = enemyObject->GetScript<ScriptEnemy>();
		}
		else
		{
			enemy = enemyObject->AddScript<ScriptEnemy>();
		}
		enemy->SetPlayer(player);
		enemy->SetMaxLife(20);
		enemy->SetDamage(2);
		enemy->mAgent->mCharacter->SetSpeed(5.f);
		enemy->mAgent->GetPathFinding()->SetGrid(grid);
		enemy->SetCellTarget(grid->GetNearestCell(player->GetWorldPosition()));
		enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(pos.x, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, pos.z));
		//enemy->mAgent->mCharacter->mEntity->SetWorldScale(gce::Vector3f32(10.f, 10.f, 10.f));
	}

	static void CreateStaticObject(gce::Scene& scene, ScriptGrid* grid, bool isFix, bool isObstacle, gce::Vector3f32 pos, gce::Vector3f32 scale)
	{
		gce::GameObject& staticObject = CreateGameObject<ScriptStaticGeometry>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		staticObject.SetName("StaticObject");

		SetStaticObject(&staticObject, grid, isFix, isObstacle, pos, scale);

	}

	static void SetStaticObject(gce::GameObject* staticObject, ScriptGrid* grid, bool isFix, bool isObstacle, gce::Vector3f32 pos, gce::Vector3f32 scale)
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
		staticGeometry->mEntity->SetWorldPosition(pos);
		staticGeometry->mEntity->SetWorldScale(scale);
	}

	static void SetStaticObject(gce::GameObject* staticObject, ScriptGrid* grid, bool isFix, bool isObstacle)
	{
		staticObject->AddComponent<gce::BoxCollider>()->SetActive(true);

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

	static void CreatStaticWall(gce::Scene& scene, ScriptGrid* grid)
	{
		float s = 1.f;
		float h = 5.f;
		gce::Vector3f32 pos1 = gce::Vector3f32(35.f, h, -17.f);
		gce::Vector3f32 scale1 = gce::Vector3f32(47.f, h*2, s);
		CreateStaticObject(scene, grid, true, true, pos1, scale1);

		gce::Vector3f32 pos2 = gce::Vector3f32(54.f, h, -40.f);
		gce::Vector3f32 scale2 = gce::Vector3f32(s, h*2, 45.f);
		CreateStaticObject(scene, grid, true, true, pos2, scale2);

		gce::Vector3f32 pos3 = gce::Vector3f32(42.f, h, -60.f);
		gce::Vector3f32 scale3 = gce::Vector3f32(35.f, h*2, s);
		CreateStaticObject(scene, grid, true, true, pos3, scale3);

		gce::Vector3f32 pos4 = gce::Vector3f32(25.f, h, -45.f);
		gce::Vector3f32 scale4 = gce::Vector3f32(s, h*2, 38.f);
		CreateStaticObject(scene, grid, true, true, pos4, scale4);

		gce::Vector3f32 pos5 = gce::Vector3f32(10.f, h, -27.f);
		gce::Vector3f32 scale5 = gce::Vector3f32(30.f, h * 2, s);
		CreateStaticObject(scene, grid, true, true, pos5, scale5);

		gce::Vector3f32 pos6 = gce::Vector3f32(-4.f, h, -15.f);
		gce::Vector3f32 scale6 = gce::Vector3f32(s, h * 2, 30.f);
		CreateStaticObject(scene, grid, true, true, pos6, scale6);

		gce::Vector3f32 pos7 = gce::Vector3f32(11.2f, 1.f, -9.1f);
		gce::Vector3f32 scale7 = gce::Vector3f32(0.1f, 3.f, 18.f);
		CreateStaticObject(scene, grid, true, true, pos7, scale7);



		//gce::Vector3f32 pos8 = gce::Vector3f32(-5.f, h, 10.f);
		//gce::Vector3f32 scale8 = gce::Vector3f32(s, h * 2, 25.f);
		//CreateStaticObject(scene, grid, true, true, pos8, scale8);
	}

	static void CreateMap(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid, cstr name)
	{

		///////////////////////////////////////////////////////////
		// Map json
		std::vector<gce::GameObject*> atelier = JsonLoader::LoadMap(RES_PATH"res/Gameplay/Json/Atelier.json", &scene);
		std::vector<gce::GameObject*> hangar = JsonLoader::LoadMap(RES_PATH"res/Gameplay/Json/Hangar.json", &scene);
		std::vector<gce::GameObject*> outside = JsonLoader::LoadMap(RES_PATH"res/Gameplay/Json/Outside.json", &scene);

		std::vector<gce::GameObject*> gameObjectLoad;
		int lenghtHangar = (int)hangar.size();
		for (int i = 0; i < lenghtHangar; i++) { gameObjectLoad.push_back(hangar[i]); hangar[i]->transform.WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.f)); }
		int lenghtOutside = (int)outside.size();
		for (int i = 0; i < lenghtOutside; i++) { gameObjectLoad.push_back(outside[i]); outside[i]->transform.WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.f)); }
		int lenghtAtelier = (int)atelier.size();
		for (int i = 0; i < lenghtAtelier; i++) { gameObjectLoad.push_back(atelier[i]); atelier[i]->transform.WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.f)); }

		int lenghtLoad = (int)gameObjectLoad.size();
		for (int i = 0; i < lenghtLoad; i++)
		{
			gameObjectLoad[i]->SetName(name);
		}
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
		gce::GameObject& angleGringerObject = CreateGameObject<ScriptAngleGringer>(scene, gce::SHAPES.CUBE);
		angleGringerObject.SetName("AngleGringer");
		weaponParent.AddChild(angleGringerObject);

		ScriptAngleGringer* angleGringer = angleGringerObject.GetScript<ScriptAngleGringer>();
		angleGringer->mWeapons->mMagazine->SetMaxBullets(3);
		angleGringer->mWeapons->mMagazine->SetShootTime(0.1f);
		angleGringer->mWeapons->mMagazine->SetReloadTime(0.5f);
		angleGringer->mWeapons->mEntity->SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		angleGringer->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));
		angleGringer->mWeapons->mEntity->SetLocalScale(gce::Vector3f32(1, 1, 5));
		player->AddWeapon(angleGringer->mWeapons);//1
	}

	static ScriptSubMachineGun* CreateSubmachineGun(gce::Scene& scene, ScriptPlayer* player, gce::GameObject& weaponParent)
	{
		gce::GameObject& subMachineGunObject = *JsonLoader::LoadMap(RES_PATH"res/Gameplay/Json/smg.json", &scene)[0];
		subMachineGunObject.AddScript<ScriptSubMachineGun>();
		subMachineGunObject.GetScript<ScriptSubMachineGun>()->Initia();
		static gce::D12PipelineObject defaultPso(gce::SHADERS.VERTEX, gce::SHADERS.PIXEL, gce::SHADERS.HULL, gce::SHADERS.DOMAIN_, gce::SHADERS.ROOT_SIGNATURE);
		gce::MeshRenderer& meshRenderer = *subMachineGunObject.AddComponent<gce::MeshRenderer>();
		meshRenderer.pPso = &defaultPso;
		gce::Light* light = subMachineGunObject.AddComponent<gce::Light>();
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

	static gce::GameObject& CreateUIWeapon(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		ImageUI* uiImage = crosshair.AddComponent<ImageUI>();

		Vector2f32 posUi = pos - size * 0.5f;

		uiImage->InitializeImage(posUi, size, 0.f);

		uiImage->btmBrush = new BitMapBrush(path);
		uiImage->btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, scale, 0);
		uiImage->SetActive(true);

		return crosshair;
	}

	static gce::GameObject& CreateUILife(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		ImageUI* uiImage = crosshair.AddComponent<ImageUI>();

		Vector2f32 posUi = pos - size * 0.5f;

		uiImage->InitializeImage(posUi, size, 0.f);

		uiImage->btmBrush = new BitMapBrush(path);
		uiImage->btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, scale, 0);
		uiImage->btmBrush->SetOpacity(0.f);
		uiImage->SetActive(true);

		return crosshair;
	}

	static gce::GameObject& CreateUIText(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		TextRenderer* uiTexte = crosshair.AddComponent<TextRenderer>();

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
		menu->SetInterfaceShow(MAIN_MENU);

		ResetCamera(cameraObject);

		//ImageData data = ImageLoader::LoadTexture(String(RES_PATH) + path);
		ScriptPlayer* player = playerObject->GetScript<ScriptPlayer>();
		ResetPlayerBegin(player, cameraObject, menuObject);

		gce::GameObject& weaponParent = gce::GameObject::Create(scene);
		cameraObject->AddChild(weaponParent);

		gce::GameObject& uiObject = gce::GameObject::Create(scene);
		ScriptUI* ui = uiObject.AddScript<ScriptUI>();
		ui->SetPlayer(player);

		std::string healthlv1 = "res/Gameplay/Texture/Life/healthlvl1.png";
		std::string healthlv2 = "res/Gameplay/Texture/Life/healthlvl2.png";
		std::string healthlv3 = "res/Gameplay/Texture/Life/healthlvl3.png";
		ui->AddImageLife(healthlv1);
		ui->AddImageLife(healthlv2);
		ui->AddImageLife(healthlv3);

		std::string anglegringerPath = "res/Gameplay/Texture/Weapon/disqueuse.png";
		std::string submachineGunPath = "res/Gameplay/Texture/Weapon/mitrallette.png";
		std::string bazookaPath = "res/Gameplay/Texture/Weapon/bazooka.png";

		ui->AddImageWeapon(anglegringerPath);
		ui->AddImageWeapon(submachineGunPath);
		ui->AddImageWeapon(bazookaPath);

		gce::WindowParam windowParamUI = gce::GameManager::GetWindowParam();

		gce::GameObject& health = CreateUILife(scene, { (float)windowParamUI.width / 2, (float)windowParamUI.height / 2 }, { (float)windowParamUI.width, (float)windowParamUI.height}, { 1.f, 1.f, 1.f}, healthlv1, texturePso);
		ui->AddBoxLife(health);

		gce::GameObject& mainWeapon = CreateUIWeapon(scene, { windowParamUI.width -430.f,windowParamUI.height - 275.f }, { 72,72 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, anglegringerPath, texturePso);
		gce::GameObject& secondWeapon = CreateUIWeapon(scene, { windowParamUI.width - 350.f,windowParamUI.height - 275.f }, { 65,65 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, submachineGunPath, texturePso);
		gce::GameObject& thirdWeapon = CreateUIWeapon(scene, { windowParamUI.width - 275.f,windowParamUI.height - 275.f }, { 72,65 }, { 1.f / 3.5f, 1.f / 2.f, 1.f / 2.f }, bazookaPath, texturePso);
		mainWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);
		secondWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);
		thirdWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);
		ui->AddBoxWeapon(mainWeapon);
		ui->AddBoxWeapon(secondWeapon);
		ui->AddBoxWeapon(thirdWeapon);

		gce::GameObject& textAmo = CreateUIText(scene, { windowParamUI.width - 430.f,windowParamUI.height - 275.f }, { 72,72 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, submachineGunPath, texturePso);
		ui->AddTextAmo(textAmo);

		gce::Vector3f32 posPlayer = gce::Vector3f32(0.f, 10.f, 0.f);
		gce::Vector2f32 sizeGrid = gce::Vector2f32(40.f, 80.f);
		gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, 0.f, posPlayer.z + 20.f);

		ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

		gce::Vector3f32 posNail = gce::Vector3f32(5.f, 0.f, 5.f);
		//CreateNail(scene, player, grid, posNail, RES_PATH"res/Gameplay/Obj/clou.obj");
		CreateBot(scene, player, grid);

		CreatStaticWall(scene, grid);

		CreateMap(scene, player, grid, "Map");

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

	static void DeleteGameObject()
	{
		auto* mapGameObject = gMenuObject->m_pScene->GetGameObject();
		for (auto& [id, gameObject] : *mapGameObject)
		{
			bool scriptE = gameObject->GetScript<ScriptEntity>() != nullptr;
			bool scriptP = gameObject->GetScript<ScriptPlayer>() == nullptr;
			bool scriptG = gameObject->GetScript<ScriptGrid>() != nullptr;
			if ((scriptE && scriptP) || scriptG)
			{
				gameObject->SetActive(false);
			}
		}
	}

END_TEST(Game)

#endif