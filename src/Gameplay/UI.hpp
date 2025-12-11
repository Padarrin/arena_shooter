#pragma once
#include <GameObject.h>

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

	std::vector<Ui*> mUiWeapon;

public:

	virtual void Start()
	{
		mBall.SetStockMax(5);
		mBall.SetInStock(0);

		mSeekerBall.SetStockMax(5);
		mSeekerBall.SetInStock(0);

		mImprPiece.SetStockMax(5);
		mImprPiece.SetInStock(0);
	}

	virtual void Update()
	{

	}

END_SCRIPT