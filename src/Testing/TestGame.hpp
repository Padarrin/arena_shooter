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
	gce::BitMapBrush imageCollideButtonQuit{ "/res/Gameplay/Texture/Jouer_Cliquer.png" };

	gce::Vector3f32 posImageMainMenu = gce::Vector3f32(675.f, 325.f, 5.f);
	gce::Vector3f32 scaleImageMainMenu = gce::Vector3f32(1400.f, 800.f, 1.f);
	gce::BitMapBrush imageBackgroundButtonMainMenu{ "/res/Gameplay/Texture/Menu_Princiapal.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imageMainMenuObject = gce::GameObject::Create(scene); imageMainMenuObject.transform.LocalTranslate(posImageMainMenu); imageMainMenuObject.transform.SetWorldScale(scaleImageMainMenu); imageMainMenuObject.SetName("ImageButton"); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
	gce::UIButton* imageMainMenu = imageMainMenuObject.AddComponent<gce::UIButton>(); imageMainMenu->pBitMapBrush = &imageBackgroundButtonMainMenu; imageMainMenu->pHoverBitMapBrush = &imageBackgroundButtonMainMenu; 

	//Start Button
	gce::Vector3f32 posButtonStart = gce::Vector3f32(310.0f, 310.0f, 0.0f);
	gce::Vector3f32 scaleButtonStart = gce::Vector3f32(200.0f, 100.0f, 1.0f);
	gce::GameObject& buttonStartObject = gce::GameObject::Create(scene); buttonStartObject.transform.LocalTranslate(posButtonStart); buttonStartObject.transform.LocalScale(scaleButtonStart); buttonStartObject.SetName("Button");
	gce::UIButton* buttonStart = buttonStartObject.AddComponent<gce::UIButton>(); buttonStart->AddListener(TestGame::Start); buttonStart->pBitMapBrush = &imageButtonStart; buttonStart->pHoverBitMapBrush = &imageCollideButtonStart;

	//Quit Button
	gce::Vector3f32 posButtonQuit = gce::Vector3f32(310.0f, 460.0f, 0.0f);
	gce::Vector3f32 scaleButtonQuit = gce::Vector3f32(200.0f, 100.0f, 1.0f);
	gce::GameObject& buttonQuitObject = gce::GameObject::Create(scene); buttonQuitObject.transform.LocalTranslate(posButtonQuit); buttonQuitObject.transform.LocalScale(scaleButtonQuit); buttonQuitObject.SetName("Button");
	gce::UIButton* buttonQuit = buttonQuitObject.AddComponent<gce::UIButton>(); buttonQuit->AddListener(TestGame::Quit); buttonQuit->pBitMapBrush = &imageButtonQuit; buttonQuit->pHoverBitMapBrush = &imageCollideButtonQuit;
	////Pause Menu////
	//Image
	gce::BitMapBrush imageButtonResume{ "/res/Gameplay/Texture/Reprendre.png" };
	gce::BitMapBrush imageCollideButtonResume{ "/res/Gameplay/Texture/Reprendre_Cliquer.png" };
	gce::BitMapBrush imageButtonRestart{ "/res/Gameplay/Texture/Recommencer.png" };
	gce::BitMapBrush imageCollideButtonRestart{ "/res/Gameplay/Texture/Reprendre_Cliquer.png" };
	gce::BitMapBrush imageButtonExit{ "/res/Gameplay/Texture/Quitter.png" };
	gce::BitMapBrush imageCollideButtonExit{ "/res/Gameplay/Texture/Jouer_Cliquer.png" };

	//gce::Vector3f32 posImagePauseMenu = gce::Vector3f32(600.f, 400.f, 5.f);
	//gce::Vector3f32 scaleImagePauseMenu = gce::Vector3f32(1000.f, 1000.f, 1.f);
	//gce::BitMapBrush imageBackgroundButtonPauseMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	//gce::GameObject& imagePauseMenuObject = gce::GameObject::Create(scene); imagePauseMenuObject.transform.LocalTranslate(posImagePauseMenu); imagePauseMenuObject.transform.SetWorldScale(scaleImagePauseMenu); imagePauseMenuObject.SetName("ImageButton"); //AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);
	//gce::UIButton* imagePauseMenu = imagePauseMenuObject.AddComponent<gce::UIButton>(); imagePauseMenu->pBitMapBrush = &imageBackgroundButtonPauseMenu; imagePauseMenu->pHoverBitMapBrush = &imageBackgroundButtonPauseMenu;
	
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
	gce::BitMapBrush imageCollideButtonReplay{ "/res/Gameplay/Texture/Reprendre_Cliquer.png" };
	gce::BitMapBrush imageButtonEnd{ "/res/Gameplay/Texture/Quitter.png" };
	gce::BitMapBrush imageCollideButtonEnd{ "/res/Gameplay/Texture/Jouer_Cliquer.png" };

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
	gce::Vector3f32 scaleButtonReplay = gce::Vector3f32(200.0f, 100.0f, 1.0f);
	gce::GameObject& buttonReplayObject = gce::GameObject::Create(scene); buttonReplayObject.transform.LocalTranslate(posButtonReplay); buttonReplayObject.transform.LocalScale(scaleButtonReplay); buttonReplayObject.SetName("Button");
	gce::UIButton* buttonReplay = buttonReplayObject.AddComponent<gce::UIButton>(); buttonReplay->AddListener(TestGame::Restart); buttonReplay->pBitMapBrush = &imageButtonReplay; buttonReplay->pHoverBitMapBrush = &imageCollideButtonReplay;

	//End Button
	gce::Vector3f32 posButtonEnd = gce::Vector3f32(600.0f, 800.0f, 0.0f);
	gce::Vector3f32 scaleButtonEnd = gce::Vector3f32(200.0f, 100.0f, 1.0f);
	gce::GameObject& buttonEndObject = gce::GameObject::Create(scene); buttonEndObject.transform.LocalTranslate(posButtonEnd); buttonEndObject.transform.LocalScale(scaleButtonEnd); buttonEndObject.SetName("Button");
	gce::UIButton* buttonEnd = buttonEndObject.AddComponent<gce::UIButton>(); buttonEnd->AddListener(TestGame::Quit); buttonEnd->pBitMapBrush = &imageButtonEnd; buttonEnd->pHoverBitMapBrush = &imageCollideButtonEnd;

	menu->AddImage(&imageMainMenuObject, MAIN_MENU);
	menu->AddButton(&buttonStartObject, MAIN_MENU);
	menu->AddButton(&buttonQuitObject, MAIN_MENU);

	//menu->AddImage(&imagePauseMenuObject, PAUSE_MENU);
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
		player->SetWorldPosition(gce::Vector3f32(0.f, 10.f, 0.f));
		player->mCharacter->SetSpeed(9.f);
		player->SetJump(6.f);
		player->mCharacter->SetMaxLife(100);
	}
	
	static void ResetPlayerEnd(ScriptPlayer* player)
	{
		player->SetCurrentWeapon(WEAPON_ORDER::ANGLEGRINGER);
		player->Start();
	}

	static void CreateNail(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos)
	{
		//Life = 20 a 200, Damage = 1 a 5
		gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		enemyObject.SetName("Enemy");

		SetNail(&enemyObject, player, grid, pos);

	}

	static void SetNail(/*gce::Scene& scene,*/gce::GameObject*/*&*/ enemyObject, ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos)
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
		enemy->SetPlayer(player);
		enemy->SetMaxLife(20);
		enemy->SetDamage(2);
		enemy->mAgent->mCharacter->SetSpeed(5.f);
		enemy->mAgent->GetPathFinding()->SetGrid(grid);
		enemy->SetCellTarget(grid->GetNearestCell(player->GetWorldPosition()));
		enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(pos.x, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, pos.z));
		
	}

	static void CreateStaticObject(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptGrid* grid, bool isFix, bool isObstacle, gce::Vector3f32 pos, gce::Vector3f32 scale)
	{
		gce::GameObject& staticObject = CreateGameObject<ScriptStaticGeometry>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		staticObject.SetName("StaticObject");

		SetStaticObject(&staticObject, grid, isFix, isObstacle, pos, scale);

	}

	static void SetStaticObject(/*gce::Scene& scene,*/gce::GameObject* staticObject, ScriptGrid* grid, bool isFix, bool isObstacle, gce::Vector3f32 pos, gce::Vector3f32 scale)
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
		staticGeometry->mEntity->SetWorldScale(pos);
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

	static void CreateMap(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid, cstr name, const String& path)
	{
		///////////////////////////////////////////////////////////
		// Map json
		std::vector<gce::GameObject*> gameObjectLoad = JsonLoader::LoadMap(path, &scene);
		auto* mapGameObject = gMenuObject->m_pScene->GetGameObject();

		int lenghtLoad = (int)gameObjectLoad.size();
		for (int i = 0; i < lenghtLoad; i++)
		{
			gameObjectLoad[i]->SetName(name);
			//SetStaticObject(gameObjectLoad[i], grid, true, true);
		}

		for (auto& [id, currentGameObject] : *mapGameObject)
		{
			//gce::GameObject* currentGameObject= gameObjectLoad[i];
			if (currentGameObject->GetName() == "GameObject")
			{
				//if (currentGameObject->HasParent())
				//{
					//currentGameObject->RemoveParent();
				//}
				//////////////////////Enemy///////////////////////
				/*if ()//currentGameObject->GetName() == "Nail"
				{
					currentGameObject->SetName("Enemy");
					SetNail(currentGameObject, player, grid);
				}
				else if ()//currentGameObject->GetName() == "Bot"
				{
					currentGameObject->SetName("Bot");
					//SetNail(currentGameObject, player, grid);
				}
				//////////////////////Enemy Fin///////////////////////
				//////////////////////Item///////////////////////
				else if ()//currentGameObject->GetName() == "Item"
				{
					currentGameObject->SetName("Item");
					//SetNail(currentGameObject, player, grid);
				}
				//////////////////////Item Fin///////////////////////
				//////////////////////Furniture///////////////////////
				else if ()//currentGameObject->GetName() == "Box"
				{
					currentGameObject->SetName("Box");
					//SetNail(currentGameObject, player, grid);
				}
				//////////////////////Furniture Fin///////////////////////
				//////////////////////Floor///////////////////////
				else
				{*/
				auto isCube = [](Vector3f32 scale, float tolerance = 0.25f) -> bool
					{
						float minV = min(scale.x, min(scale.y, scale.z));
						float maxV = max(scale.x, max(scale.y, scale.z));
						return (maxV / minV) < (1.0f + tolerance);
					};
				auto isFloor = [](Vector3f32 scale, float ratio = 0.35f) -> bool
					{
						return scale.y < scale.x * ratio && scale.y < scale.z * ratio;
					};
				auto isWall = [](Vector3f32 scale, float ratio = 2.0f) -> bool
					{
						return scale.y > scale.x * ratio || scale.y > scale.z * ratio;
					};
				

				gce::Vector3f32 scale = currentGameObject->transform.GetWorldPosition();
				if (isWall(scale) && !isCube(scale))//currentGameObject->GetName() == "Wall"
				{
					bool isFix = false;
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
				else if (isFloor(scale) && !isCube(scale))//currentGameObject->GetName() == "Floor" || currentGameObject->GetName() == "Roof"
				{
					bool isFix = false;
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
				//else if ()//currentGameObject->GetName() == "Door"
				//{
					//bool isFix = false;
					//bool isObstacle = false;
					//SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					//currentGameObject->SetName("StaticObject");
				//}
				else //if ()//currentGameObject->GetName() == "GameObject"
				{
					bool isFix = false;
					bool isObstacle = false;
					SetStaticObject(currentGameObject, grid, isFix, isObstacle);
					currentGameObject->SetName("StaticObject");
				}
				//////////////////////Autre///////////////////////
				/*else
				{
					auto n = currentGameObject->GetName();
					n = n;
				}*/
				//////////////////////Autre Fin///////////////////////
				//}
				//////////////////////Floor Fin///////////////////////
			}
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
		gce::GameObject& angleGringerObject = CreateGameObject<ScriptAngleGringer>(scene, gce::SHAPES.CUBE);
		angleGringerObject.AddComponent<gce::BoxCollider>()->SetActive(true);
		angleGringerObject.SetName("AngleGringer");
		weaponParent.AddChild(angleGringerObject);

		ScriptAngleGringer* angleGringer = angleGringerObject.GetScript<ScriptAngleGringer>();
		angleGringer->mWeapons->mEntity->SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		angleGringer->mWeapons->mEntity->SetLocalPosition(gce::Vector3f32(2.f, 0.f, 3.f));
		angleGringer->mWeapons->mEntity->SetLocalScale(gce::Vector3f32(1, 1, 5));

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

	static gce::GameObject& CreateUIText(gce::Scene& scene)
	{
		GameObject& crosshair = GameObject::Create(scene);
		TextRenderer* uiTexte = crosshair.AddComponent<TextRenderer>();

		return crosshair;
	}

	static gce::GameObject& CreateUIFix(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		ImageUI* uiImage = crosshair.AddComponent<ImageUI>();

		Vector2f32 posUi = pos - size * 0.5f;

		uiImage->InitializeImage(posUi, size, 1.f);

		uiImage->btmBrush = new BitMapBrush(path);
		uiImage->btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, scale, 0);
		uiImage->btmBrush->SetOpacity(1.f);
		uiImage->SetActive(true);

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
		ResetPlayerBegin(player, cameraObject, menuObject);

		gce::GameObject& weaponParent = gce::GameObject::Create(scene);
		cameraObject->AddChild(weaponParent);

		gce::GameObject& uiObject = gce::GameObject::Create(scene);
		ScriptUI* ui = uiObject.AddScript<ScriptUI>();
		ui->SetPlayer(player);

		std::string crooshair = "res/Gameplay/Texture/crosshair.png";
		std::string amo = "res/Gameplay/Texture/balles.png";
		ui->AddImageUiFix(amo);
		ui->AddImageUiFix(amo);

		std::string healthlv1 = "res/Textures/Life/healthlvl1.png";
		std::string healthlv2 = "res/Textures/Life/healthlvl2.png";
		std::string healthlv3 = "res/Textures/Life/healthlvl3.png";
		ui->AddImageLife(healthlv1);
		ui->AddImageLife(healthlv2);
		ui->AddImageLife(healthlv3);

		std::string anglegringerPath = "res/Textures/Weapon/disqueuse.png";
		std::string submachineGunPath = "res/Textures/Weapon/mitrallette.png";
		std::string bazookaPath = "res/Textures/Weapon/bazooka.png";

		ui->AddImageWeapon(anglegringerPath);
		ui->AddImageWeapon(submachineGunPath);
		ui->AddImageWeapon(bazookaPath);

		gce::WindowParam windowParam = gce::GameManager::GetWindowParam();

		gce::GameObject& health = CreateUILife(scene, { (float)windowParam.width / 2, (float)windowParam.height / 2 }, { (float)windowParam.width, (float)windowParam.height}, { 1.f, 1.f, 1.f}, healthlv1, texturePso);
		ui->AddBoxLife(health);

		gce::GameObject& mainWeapon = CreateUIWeapon(scene, { windowParam.width -430.f,windowParam.height - 275.f }, { 72,72 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, anglegringerPath, texturePso);
		gce::GameObject& secondWeapon = CreateUIWeapon(scene, { windowParam.width - 350.f,windowParam.height - 275.f }, { 65,65 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, submachineGunPath, texturePso);
		gce::GameObject& thirdWeapon = CreateUIWeapon(scene, { windowParam.width - 275.f,windowParam.height - 275.f }, { 72,65 }, { 1.f / 3.5f, 1.f / 2.f, 1.f / 2.f }, bazookaPath, texturePso);
		mainWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);
		secondWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);
		thirdWeapon.GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);
		ui->AddBoxWeapon(mainWeapon);
		ui->AddBoxWeapon(secondWeapon);
		ui->AddBoxWeapon(thirdWeapon);

		gce::GameObject& textAmo = CreateUIText(scene);
		ui->AddTextAmo(textAmo);

		gce::GameObject& UiBall = CreateUIFix(scene, { windowParam.width - 1450.f,windowParam.height - 100.f }, { 65,65 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, amo, texturePso);
		ui->AddUiFix(UiBall);
		gce::GameObject& UiCrosshair = CreateUIFix(scene, { windowParam.width *0.5f,windowParam.height *0.5f }, { 65,65 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, crooshair, texturePso);
		ui->AddUiFix(UiCrosshair);

		gce::Vector3f32 posPlayer = gce::Vector3f32(0.f, 10.f, 0.f);
		gce::Vector2f32 sizeGrid = gce::Vector2f32(40.f, 80.f);
		gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 2.5f), posPlayer.z + 20.f);

		ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

		gce::Vector3f32 posNail = gce::Vector3f32(5.f, 0.f, 5.f);
		CreateNail(scene, player, grid, posNail);

		gce::Vector3f32 posCube = gce::Vector3f32(10.f, 10.f, 5.f);
		gce::Vector3f32 posScale = gce::Vector3f32(10.f, 2.f, 5.f);
		CreateStaticObject(scene, grid, true, true, posCube, posScale);

		CreateMap(scene, player, grid, "OutSide", RES_PATH"res/Gameplay/Json/outside.json");

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
			bool scriptE = gameObject->GetScript<ScriptEntity>() != nullptr;
			bool scriptP = gameObject->GetScript<ScriptPlayer>() == nullptr;
			bool scriptG = gameObject->GetScript<ScriptGrid>() != nullptr;
			if ((scriptE && scriptP) || scriptG)
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