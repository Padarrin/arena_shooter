#pragma once
#include <GameObject.h>
#include "Weapons.hpp"
#include "Player.hpp"

DECLARE_SCRIPT(ScriptUI, ScriptFlag::Start | ScriptFlag::Update)

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

private:
	Ui mBall;
	Ui mSeekerBall;
	Ui mImprPiece;

	std::vector<ScriptWeapons*>* mUiWeapon;

	ScriptWeapons* mCurrentWeapon;
	cstr mName;

	ScriptPlayer* mPlayer;

	ScriptPistolMagazine* mSubmachine;
	ScriptPistolMagazine* mBazooka;


public:
	virtual void Initia() 
	{ 
		mUiWeapon = mPlayer->GetAllWeapons();

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

	virtual void Start()
	{
		mCurrentWeapon = mPlayer->GetCurrentWeapon();
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

		mCurrentWeapon = mPlayer->GetCurrentWeapon();
		mName = mCurrentWeapon->mEntity->GetGameObject()->GetName();
	}

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT