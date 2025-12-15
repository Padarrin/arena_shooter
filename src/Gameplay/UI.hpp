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

struct Image
{
	gce::GameObject* mImageObjet;

	Image() { mImageObjet = nullptr; }
	Image(gce::GameObject* buttonObjet) { mImageObjet = buttonObjet; }

	void SetAll(gce::GameObject* buttonObjet) { mImageObjet = buttonObjet; }

	void SetImageObjet(gce::GameObject* buttonObjet) { mImageObjet = buttonObjet; }
	gce::GameObject* GetImageObjet() { return mImageObjet; }
};

DECLARE_SCRIPT(ScriptUI, ScriptFlag::Start | ScriptFlag::Update)

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

	std::vector<Image*> mAllImages;

public:
	ScriptEntity* mEntity;

	virtual void Initia() 
	{ 
		mEntity = m_pOwner->AddScript<ScriptEntity>();
		mEntity->Initia();

		mAllImages = std::vector<Image*>();

		mCameraObject = m_pOwner->GetParent();
	}

	virtual void Start()
	{
		/*mUiWeapon = mPlayer->GetAllWeapons();
		mCurrentWeapon = mPlayer->GetCurrentWeapon();

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

	std::vector<Image*> ShowMenu() { return ActiveImage(); }

	std::vector<Image*> ActiveImage()
	{
		std::vector<Image*> allActiveImage;

		for (auto im = mAllImages.begin(); im != mAllImages.end(); ++im)
		{
			Image* image = *im;
			
			image->GetImageObjet()->SetActive(true);
			allActiveImage.push_back(image);
		}

		return allActiveImage;
	}

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

	void AddImage(gce::GameObject* imageObject) { mAllImages.push_back(new Image(imageObject)); }
	std::vector<Image*>* GetAllImages() { return &mAllImages; }

END_SCRIPT