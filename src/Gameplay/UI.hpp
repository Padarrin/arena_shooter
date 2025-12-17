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

struct SettingImage
{
private:
	gce::Vector2f32 pos;
	gce::Vector2f32 size;
	gce::Vector3f32 scale;
	gce::Vector2f32 posUi;
	float32 opacity;

public:
	void SetPos(gce::Vector2f32 position) { pos = position; }
	gce::Vector2f32 GetPos() { return pos; }

	void SetSize(gce::Vector2f32 sizeImage) { size = sizeImage; }
	gce::Vector2f32 GetSize() { return size; }

	void SetScale(gce::Vector3f32 scaleImage) { scale = scaleImage; }
	gce::Vector3f32 GetScale() { return scale; }

	void SetPosUi(gce::Vector2f32 PositionUi) { posUi = PositionUi; }
	gce::Vector2f32 GetPosUi() { return posUi; }

	void SetOpacity(float32 opacityImage) { opacity = opacityImage; }
	float32 GetOpacity() { return opacity; }
};

DECLARE_SCRIPT(ScriptUI, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

private:
	Ui mBall;
	Ui mSeekerBall;
	Ui mImprPiece;
	
	SettingImage mWeaponPrincipal;
	SettingImage mWeaponSecond;
	SettingImage mWeaponThird;

	gce::GameObject* mCameraObject;

	std::vector<ScriptWeapons*>* mUiWeapon;

	ScriptWeapons* mCurrentWeapon;
	cstr mName;

	ScriptPlayer* mPlayer;

	ScriptPistolMagazine* mSubmachine;
	ScriptPistolMagazine* mBazooka;

	std::vector<gce::GameObject*> mAllTextures;
	std::vector<SettingImage*> mSettingsImages;
	std::vector< std::string> mAllImages;

	gce::WindowParam* mWindowParam;

public:
	ScriptEntity* mEntity;

	virtual void Initia() 
	{ 
		mWeaponPrincipal.SetSize(gce::Vector2f32{ 72,72 });
		mWeaponPrincipal.SetScale(gce::Vector3f32{ 1.f / 14.f, 1.f / 14.f, 1.f / 14.f });
		mWeaponPrincipal.SetOpacity(1.f);

		mWeaponSecond.SetSize(gce::Vector2f32{ 65,65 });
		mWeaponSecond.SetScale(gce::Vector3f32{ 1.f / 14.f, 1.f / 14.f, 1.f / 14.f });
		mWeaponSecond.SetOpacity(1.f);
	}

	virtual void Start()
	{
		mWindowParam = &gce::GameManager::GetWindowParam();

		mWeaponPrincipal.SetPos(gce::Vector2f32{ mWindowParam->width * 0.7f,mWindowParam->height * 0.68f });
		mWeaponSecond.SetPos(gce::Vector2f32{ mWindowParam->width * 0.74f,mWindowParam->height * 0.68f });

		mWeaponPrincipal.SetPosUi(mWeaponPrincipal.GetPos() - mWeaponPrincipal.GetSize() * 0.5f);
		mWeaponSecond.SetPosUi(mWeaponSecond.GetPos() - mWeaponSecond.GetSize() * 0.5f);

		mSettingsImages.push_back(&mWeaponPrincipal);
		mSettingsImages.push_back(&mWeaponSecond);

		mUiWeapon = mPlayer->GetAllWeapons();
		mCurrentWeapon = mPlayer->GetCurrentWeapon();

		mSubmachine = (*mUiWeapon)[SUBMACHINEGUN]->mMagazine;
		mBazooka = (*mUiWeapon)[SUBMACHINEGUN]->mMagazine;

		mBall.SetStockMax(mSubmachine->GetMaxBullets());
		mBall.SetInStock(mSubmachine->GetCurrentBullets());

		mSeekerBall.SetStockMax(mBazooka->GetMaxBullets());
		mSeekerBall.SetInStock(mBazooka->GetCurrentBullets());

		mImprPiece.SetStockMax(30);
		mImprPiece.SetInStock(0);

		mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();

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
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[0]);
			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 490.f,mWindowParam->height - 310.f, 0 }, { 1 / 14.f,1 / 14.f,1 / 14.f }, 0.f);

			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[1]);
			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 390.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[2]);
			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_2) && mName != "SubmachineGun")
		{
			mPlayer->SetCurrentWeapon(SUBMACHINEGUN);
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[1]);
			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 490.f,mWindowParam->height - 310.f, 0 }, { 1 / 14.f,1 / 14.f,1 / 14.f }, 0.f);

			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[0]);
			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 390.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[2]);
			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_3) && mName != "Bazooka")
		{
			mPlayer->SetCurrentWeapon(BAZOOKA);
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[2]);
			mAllTextures[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 490.f,mWindowParam->height - 310.f, 0 }, { 1 / 14.f,1 / 14.f,1 / 14.f }, 0.f);

			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[0]);
			mAllTextures[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 390.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImages[1]);
			mAllTextures[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 15.f, 1.f / 15.f, 1.f / 15.f }, 0.f);

		}
	}

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

	void AddTexture(gce::GameObject& textureObject) { mAllTextures.push_back(&textureObject); }
	void AddImage(std::string imagePath) { mAllImages.push_back(imagePath); }

	void SetWinParam(gce::WindowParam windowPa) { mWindowParam = &windowPa; }

END_SCRIPT