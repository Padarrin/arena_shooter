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
	cstr mNameWeapon;

	ScriptPlayer* mPlayer;

	ScriptPistolMagazine* mSubmachine;
	ScriptPistolMagazine* mBazooka;

	std::vector<gce::GameObject*> mAllBoxWeapon;
	std::vector<gce::GameObject*> mAllUiFix;
	gce::GameObject* mBoxLife;
	gce::GameObject* mTextAmo;

	std::vector<SettingImage*> mSettingsImages;

	std::vector< std::string> mAllImagesWeapon;
	std::vector< std::string> mAllImagesLife;
	std::vector< std::string> mAllImagesUiFix;

	gce::WindowParam* mWindowParam;

	int mMaxLifePlayer;

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

		mSeekerBall.SetStockMax(mBazooka->GetMaxBullets());

		mImprPiece.SetStockMax(30);
		mImprPiece.SetInStock(0);

		mNameWeapon = mCurrentWeapon->mEntity->GetGameObject()->GetName();

		mMaxLifePlayer = mPlayer->mCharacter->GetMaxLife();
	}

	virtual void Update()
	{
		mBall.SetInStock(mSubmachine->GetCurrentBullets());

		mSeekerBall.SetInStock(mBazooka->GetCurrentBullets());

		UiLife();
		UiAmo();

		float deltaTime = gce::GameManager::GameDeltaTime();
		if (deltaTime > 0.f)
		{
			InputWeapon();
		}
	}

	void InputWeapon()
	{
		if (gce::GetKeyDown(gce::Keyboard::Key::_1) && mNameWeapon != "AngleGringer")
		{
			mPlayer->SetCurrentWeapon(ANGLEGRINGER);
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mNameWeapon = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[0]);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 473.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);

			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[1]);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 384.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[2]);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 3.5f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_2) && mNameWeapon != "SubmachineGun")
		{
			mPlayer->SetCurrentWeapon(SUBMACHINEGUN);
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mNameWeapon = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[1]);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 468.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);

			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[0]);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 388.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[2]);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 3.5f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

		}

		else if (gce::GetKeyDown(gce::Keyboard::Key::_3) && mNameWeapon != "Bazooka")
		{
			mPlayer->SetCurrentWeapon(BAZOOKA);
			mCurrentWeapon = mPlayer->GetCurrentWeapon();
			mNameWeapon = mCurrentWeapon->mEntity->GetGameObject()->GetName();

			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[2]);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 470.f,mWindowParam->height - 300.f, 0 }, { 1.f / 3.5f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[0]->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);

			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[0]);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 388.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[1]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesWeapon[1]);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetTransformMatrix({ mWindowParam->width - 310.f,mWindowParam->height - 310.f, 0 }, { 1.f / 2.f, 1.f / 2.f, 1.f / 2.f }, 0.f);
			mAllBoxWeapon[2]->GetComponent<ImageUI>()->btmBrush->SetOpacity(0.5f);

		}
	}

	void UiLife()
	{
		int currentLife = mPlayer->mCharacter->GetLife();

		if (currentLife <= mMaxLifePlayer * 0.75f && currentLife > mMaxLifePlayer * 0.5f)
		{
			mBoxLife->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);
			mBoxLife->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesLife[0]);
		}
		else if (currentLife <= mMaxLifePlayer * 0.5f && currentLife > mMaxLifePlayer * 0.25f)
		{
			mBoxLife->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);
			mBoxLife->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesLife[1]);
		}
		else if (currentLife <= mMaxLifePlayer * 0.25f && currentLife > 0)
		{
			mBoxLife->GetComponent<ImageUI>()->btmBrush->SetOpacity(1.f);
			mBoxLife->GetComponent<ImageUI>()->btmBrush = new BitMapBrush(mAllImagesLife[2]);
		}
	}

	void UiAmo()
	{
		Color colors[] = {
			Color::Cyan,
			Color::Red
		};

		mTextAmo->GetComponent<TextRenderer>()->pFont = new Font(L"Ashley Crawford");

		mTextAmo->GetComponent<TextRenderer>()->rectPosF = new RectanglePosF(10.0f, mWindowParam->height - 200.f, 500.0f, 50.0f);
		mTextAmo->GetComponent<TextRenderer>()->pBrush = new ColorBrush(gce::Color::Cyan);

		if (mNameWeapon == "SubmachineGun")
		{
			static std::wstring buffer;

			buffer = std::to_wstring(mBall.GetInStock()) + L" / " + std::to_wstring(mBall.GetStockMax());
			mTextAmo->GetComponent<TextRenderer>()->text = buffer;
		}
		else if (mNameWeapon == "Bazooka")
		{
			static std::wstring buffer;

			buffer = std::to_wstring(mSeekerBall.GetInStock()) + L" / " + std::to_wstring(mSeekerBall.GetStockMax());
			mTextAmo->GetComponent<TextRenderer>()->text = buffer;
		}
		else if (mNameWeapon == "AngleGringer")
		{
			mTextAmo->GetComponent<TextRenderer>()->text = L"0 / 0";
			mTextAmo->GetComponent<TextRenderer>()->pBrush = new LinearGradientBrush(*mTextAmo->GetComponent<TextRenderer>()->rectPosF, 1, colors, 0.5f);
		}
	}

	void UiFix()
	{
		
	}

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

	void AddBoxWeapon(gce::GameObject& boxWeaponObject) { mAllBoxWeapon.push_back(&boxWeaponObject); }
	void AddUiFix(gce::GameObject& boxWeaponObject) { mAllUiFix.push_back(&boxWeaponObject); }
	void AddBoxLife(gce::GameObject& boxLifeObject) { mBoxLife = &boxLifeObject; }
	void AddTextAmo(gce::GameObject& textAmoObject) { mTextAmo = &textAmoObject; }

	void AddImageWeapon(std::string imagePath) { mAllImagesWeapon.push_back(imagePath); }
	void AddImageLife(std::string imagePath) { mAllImagesLife.push_back(imagePath); }
	void AddImageUiFix(std::string imagePath) { mAllImagesUiFix.push_back(imagePath); }

	void SetWinParam(gce::WindowParam windowPa) { mWindowParam = &windowPa; }

END_SCRIPT