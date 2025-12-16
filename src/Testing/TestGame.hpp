#ifndef TEST_Game_HPP_INCLUDED
#define TEST_Game_HPP_INCLUDED

#include <Render.h>
#include <Engine.h>
#include <ImageLoader.h>

#include "../Engine/Components/MeshRenderer.h"
#include "../Engine/Components/Light.h"

#include "../Gameplay/Enemy.hpp"
#include "../Gameplay/Grid.hpp"
#include "../Gameplay/Menu.hpp"

#include "../Gameplay/Functions.h"

#include "define.h"

gce::GameObject* gCameraObject;
gce::GameObject* gMenuObject;

BEGIN_TEST( Game )

	gce::GameManager::Create();
	gce::Scene& scene = gce::Scene::Create();

	gCameraObject = CreateCamera(scene);

	gce::GameObject& directionalLightObject = gce::GameObject::Create(scene);
	gce::Light& directionalLight = *directionalLightObject.AddComponent<gce::Light>();
	directionalLight.DefaultDirectionLight();
	directionalLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	//	//	//	//	 Menu   //	//	//	//
	gce::GameObject& menuObject = CreateGameObject<ScriptMenu>(scene);
	ScriptMenu* menu = menuObject.GetScript<ScriptMenu>();

	gce::Vector3f32 posCameraInMenu = gce::Vector3f32(0.f, 0.f, 0.f);

	////Main Menu////
	//Image
	gce::BitMapBrush imageButtonStart{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonStart{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonQuit{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonQuit{ "res/Testing/Button/Button2.png" };

	gce::Vector3f32 posImageMainMenu = gce::Vector3f32(0.f, 0.f, 5.f) + posCameraInMenu;
	gce::Vector3f32 scaleImageMainMenu = gce::Vector3f32(5.f, 5.f, 0.1f);
	gce::BitMapBrush imageBackgroundButtonMainMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imageMainMenuObject = gce::GameObject::Create(scene); imageMainMenuObject.transform.LocalTranslate(posImageMainMenu); imageMainMenuObject.transform.SetWorldScale(scaleImageMainMenu); imageMainMenuObject.transform.SetWorldScale(scaleImageMainMenu); AddMeshRenderer(imageMainMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);

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
	gce::BitMapBrush imageBackgroundButtonResume{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonRestart{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonRestart{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageBackgroundButtonRestart{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageButtonExit{ "res/Testing/Button/Button.png" };
	gce::BitMapBrush imageCollideButtonExit{ "res/Testing/Button/Button2.png" };
	gce::BitMapBrush imageBackgroundButtonExit{ "res/Testing/Button/Button2.png" };

	gce::Vector3f32 posImagePauseMenu = gce::Vector3f32(0.f, 0.f, 5.f) + posCameraInMenu;
	gce::Vector3f32 scaleImagePauseMenu = gce::Vector3f32(5.f, 5.f, 0.1f);
	gce::BitMapBrush imageBackgroundButtonPauseMenu{ "res/Testing/Button/Button2.png" };//gce::Texture imageBackgroundButtonQuit = ImageLoader::LoadTexture(String(RES_PATH) + "res/Testing/Button/Button2.png");
	gce::GameObject& imagePauseMenuObject = gce::GameObject::Create(scene); imagePauseMenuObject.transform.LocalTranslate(posImagePauseMenu); imagePauseMenuObject.transform.SetWorldScale(scaleImagePauseMenu); imagePauseMenuObject.transform.SetWorldScale(scaleImagePauseMenu); AddMeshRenderer(imagePauseMenuObject, gce::SHAPES.CUBE/*, (gce::Texture*)&imageBackgroundButtonStart*/);

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
	
	menu->SetCamera(gCameraObject);
	menu->SetWorldPositionCamera(posCameraInMenu);

	menu->AddButton(&buttonStartObject, MAIN_MENU);
	menu->AddButton(&buttonQuitObject, MAIN_MENU);
	menu->AddImage(&imageMainMenuObject, MAIN_MENU);

	menu->AddButton(&buttonResumeObject, PAUSE_MENU);
	menu->AddButton(&buttonRestartObject, PAUSE_MENU);
	menu->AddButton(&buttonExitObject, PAUSE_MENU);
	menu->AddImage(&imagePauseMenuObject, PAUSE_MENU);

	menu->ShowMenu(MAIN_MENU);
	gMenuObject = &menuObject;
	//	//	//	//	 Menu Fin   //	//	//	//

	gce::WindowParam windowParam;
	gce::GameManager::Run(windowParam);

	gce::GameManager::Destroy();

END_TEST_MAIN_FUNCTION()

public:
	static void Start()
	{
		gce::GameObject* cameraObject = gCameraObject;
		gce::Scene& scene = (*gCameraObject->m_pScene);

		gce::GameObject* menuObject = gMenuObject;
		ScriptMenu* menu = menuObject->GetScript<ScriptMenu>();
		menu->HideMenu();
		menu->SetInterfaceShow(NOTHING);

		ResetCamera(cameraObject);

		//ImageData data = ImageLoader::LoadTexture(String(RES_PATH) + path);

		ScriptPlayer* player = CreatePlayer(scene, cameraObject);

		gce::Vector3f32 posPlayer = player->GetWorldPosition();
		gce::Vector2f32 sizeGrid = gce::Vector2f32(40.f, 80.f);
		gce::Vector3f32 posGrid = gce::Vector3f32(posPlayer.x, posPlayer.y - (player->mCharacter->mEntity->GetWorldScale().y * 0.5f), posPlayer.z);

		ScriptGrid* grid = CreateGrid(scene, sizeGrid, posGrid, 5);

		CreateEnemy(scene, player, grid);

		CreateFloor(scene);

		//createur de gameobject (remplacer les 'x' par le nom de la class + modifier ou supprimer geometry et ou texture)
		//geometry = 
		//texture = 
		//Scriptx* x = CreateGameObject<Scriptx>(scene, geometry, texture);
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

	static gce::GameObject* CreateCamera(gce::Scene& scene)
	{
		gce::GameObject& cameraObject = gce::GameObject::Create(scene);
		gce::Camera& camera = *cameraObject.AddComponent<gce::Camera>();
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

	static ScriptPlayer* CreatePlayer(gce::Scene& scene, gce::GameObject* cameraObject)
	{
		gce::GameObject& playerObject = CreateGameObject<ScriptPlayer>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		ScriptPlayer* player = playerObject.GetScript<ScriptPlayer>();

		playerObject.AddChild(*cameraObject);
		player->SetCamera(*cameraObject);
		player->WorldTranslate(gce::Vector3f32(30.f, 10.f, 0.f));
		player->mCharacter->SetSpeed(90);
		return player;
	}

	static void CreateEnemy(gce::Scene& scene, ScriptPlayer* player, ScriptGrid* grid)
	{
		gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, gce::SHAPES.CUBE, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		ScriptEnemy* enemy = enemyObject.GetScript<ScriptEnemy>();
		enemy->SetPlayer(player);
		enemy->mAgent->mCharacter->SetSpeed(5.f);
		enemy->mAgent->GetPathFinding()->SetGrid(grid);
		enemy->SetCellTarget(grid->GetNearestCell(player->GetWorldPosition()));
		enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(0.f, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, 0.f));
	}

	static void CreateFloor(gce::Scene& scene)
	{
		gce::GameObject& floorObject = CreateGameObject<ScriptEntity>(scene, gce::SHAPES.CUBE);
		ScriptEntity* entity = floorObject.GetScript<ScriptEntity>();
		entity->SetWorldPosition({ 0.f ,-1.f ,0.f });
		entity->SetWorldScale({ 50.f,0.2f,50.f });
	}

	static ScriptGrid* CreateGrid(gce::Scene& scene, gce::Vector2f32 sizeTabCell, gce::Vector3f32 positionCenter, int sizeCell)
	{
		gce::GameObject& gridObject = CreateGameObject<ScriptGrid>(scene, gce::SHAPES.CUBE);
		ScriptGrid* grid = gridObject.GetScript<ScriptGrid>();
		grid->SetCellSize(sizeCell);
		grid->SetSizeTabCell(sizeTabCell); //SetScale et lance InitTab
		grid->SetCenterOfGrid(positionCenter);
		return grid;
	}

	static void DeleteGameObject()
	{
		auto* mapGameObject = gMenuObject->m_pScene->GetGameObject();
		/*for (auto& [id, gameObject] : *mapGameObject)
		{
			if (gameObject->GetScript<ScriptEntity>() != nullptr || gameObject->GetScript<ScriptGrid>() != nullptr)
			{
				gameObject->SetActive(false);
			}
		}*/
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
		}
	}


END_TEST(Game)

#endif