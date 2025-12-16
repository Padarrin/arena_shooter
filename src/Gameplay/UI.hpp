#pragma once
#include <GameObject.h>
#include "Weapons.hpp"
#include "Player.hpp"

struct Ui
{
private:
	int stockMax;
	int inStock;

public:
	void SetStockMax(int stock) { stockMax = stock; }
	int GetStockMax() { return stockMax; }

	void SetInStock(int stock) { inStock = stock; }
	int GetInStock() { return inStock; }
};

DECLARE_SCRIPT(ScriptUI, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

private:
	Ui mBall;
	Ui mSeekerBall;
	Ui mImprPiece;
	
	gce::GameObject* mCameraObject;

	std::vector<ScriptWeapons*>* mUiWeapon;

	ScriptWeapons* mCurrentWeapon;
	cstr mName;

	ScriptPlayer* mPlayer;

	ScriptPistolMagazine* mSubmachine;
	ScriptPistolMagazine* mBazooka;

	std::vector<gce::GameObject*> mAllImages;

public:
	ScriptEntity* mEntity;

	virtual void Initia() 
	{ 
		/*mUiWeapon = mPlayer->GetAllWeapons();

		mSubmachine = (*mUiWeapon)[SUBMACHINEGUN]->mMagazine;
		mBazooka = (*mUiWeapon)[SUBMACHINEGUN]->mMagazine;

		mBall.SetStockMax(mSubmachine->GetMaxBullets());
		mBall.SetInStock(mSubmachine->GetCurrentBullets());

		mSeekerBall.SetStockMax(mBazooka->GetMaxBullets());
		mSeekerBall.SetInStock(mBazooka->GetCurrentBullets());

		mImprPiece.SetStockMax(30);
		mImprPiece.SetInStock(0);

		mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();*/
	}

	virtual void Start()
	{
		//mCurrentWeapon = mPlayer->GetCurrentWeapon();
	}

	virtual void Update()
	{
		InputWeapon();
	}

	void InputWeapon()
	{
		if (gce::GetKeyDown(gce::Keyboard::Key::_1) && mName != "AngleGringer")
		{
			mPlayer->SetCurrentWeapon(ANGLEGRINGER);
		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_2) && mName != "SubmachineGun")
		{
			mPlayer->SetCurrentWeapon(SUBMACHINEGUN);
		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_3) && mName != "Bazooka")
		{
			mPlayer->SetCurrentWeapon(BAZOOKA);
		}

		/*mCurrentWeapon = mPlayer->GetCurrentWeapon();
		mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();*/
	}

	void CreateUI(gce::Scene& scene, gce::Vector2f32 pos, gce::Vector2f32 size, gce::Vector3f32 scale, std::string path, D12PipelineObject& texturePso)
	{
		GameObject& crosshair = GameObject::Create(scene);
		ImageUI* uiImage = crosshair.AddComponent<ImageUI>();

		Vector2f32 posUi = pos - size * 0.5f;

		uiImage->InitializeImage(posUi, size, 1.f);

		uiImage->btmBrush = new BitMapBrush(path);
		uiImage->btmBrush->SetTransformMatrix({ posUi.x, posUi.y, 0 }, scale, 0);
		uiImage->SetActive(true);

		mAllImages.push_back(&crosshair);

		/*GameObject& Cube = GameObject::Create(scene);
		MeshRenderer* meshRenderer = Cube.AddComponent<MeshRenderer>();
		meshRenderer->pGeometry = SHAPES.CUBE;
		meshRenderer->pPso = &texturePso;
		Cube.transform.SetWorldPosition({ 0, 0, 10 });*/

	}

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT