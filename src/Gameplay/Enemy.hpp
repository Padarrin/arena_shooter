#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include <chrono>

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;
	Cell* mCellTarget;
	bool mIsNoPath;

	using mClock = std::chrono::steady_clock;
	mClock::time_point mPreviousTime = mClock::now();

public:
	ScriptAgent* mAgent;

	virtual void Initia() { mAgent = m_pOwner->AddScript<ScriptAgent>(); mAgent->Initia(); SetPlayer(nullptr); SetCellTarget(nullptr); mAgent->mCharacter->SetMaxLife(100); mAgent->mCharacter->SetDamage(5); }
	virtual void Start() 
	{
		ScriptGrid* grid = GetGrid();
		Cell* nearestCell = grid->GetNearestCell(GetWorldPosition());
		if (nearestCell != nullptr)
		{
			gce::Vector3f32 pos = grid->GetPosOfCell(nearestCell);
			SetWorldPosition(gce::Vector3f32(pos.x, pos.y + mAgent->GetOffsetOfGrid().y, pos.z));
		}

		SetIsNoPath(false);
	}
	virtual void Update() 
	{ 
		ScriptEntity* myParentEntity = mAgent->mCharacter->mEntity;
		if (mPlayer != nullptr)
		{
			myParentEntity->FocusEntity(myParentEntity, mPlayer->mCharacter->mEntity); // temp rotation
		}

		if (mAgent->GetPaths()->Size() < 1)
		{
			mIsNoPath = true;
			if (mCellTarget != nullptr)
			{
				mAgent->GoToCell(mCellTarget);
				SetCellTarget(nullptr);
			}
		}
		else
		{
			mIsNoPath = false;
		}

		auto currentTime = mClock::now();
		auto elapsed = currentTime - mPreviousTime;

		if (elapsed >= std::chrono::seconds(1))
		{
			//mAgent->mCharacter->CreateBallInFront<ScriptBall>("EnemyBall", 100.f, DEFAULT_BALL_DAMAGE, gce::SHAPES.CUBE, myParentEntity);
			mPreviousTime = currentTime;
		}
	}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other){}
	virtual void CollisionStay(gce::GameObject* other) {}
	virtual void CollisionExit(gce::GameObject* other) {}

	void SetIsNoPath(bool isNoPath) { mIsNoPath = isNoPath; }
	bool GetIsNoPath() { return mIsNoPath; }

	void SetCellTarget(Cell* cellTarget) { mCellTarget = cellTarget; }
	Cell* GetCellTarget() { return mCellTarget; }

	void SetWorldPosition(gce::Vector3f32 position) { mAgent->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mAgent->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mAgent->WorldTranslate(position); }

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

	void SetMaxLife(int life)
	{
		mAgent->mCharacter->SetMaxLife(life);
	}
	int GetMaxLife()
	{
		return mAgent->mCharacter->GetMaxLife();
	}

	void SetDamage(int damage)
	{
		mAgent->mCharacter->SetDamage(damage);
	}
	int GetDamage()
	{
		return mAgent->mCharacter->GetDamage();
	}
	
	ScriptGrid* GetGrid() { return mAgent->GetPathFinding()->GetGrid(); }

END_SCRIPT