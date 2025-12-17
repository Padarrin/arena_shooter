#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include <chrono>
#include <Engine.h>
#include <Render.h>
#include "StateMachine/StateMachine.h"

using namespace gce;

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;
	Cell* mCellTarget;
	bool mIsNoPath;

	using mClock = std::chrono::steady_clock;
	mClock::time_point mPreviousTime = mClock::now();

	// StateMachine
	StateMachine* mStateMachine;

	String mIdle = "Idle";
	String mRunning = "Running";
	String mAttack = "Attack";
	String mHit = "Hit";
	String mDie = "Die";

	inline static bool mIsIdle = false;
	inline static bool mIsChasingPlayer = false;
	inline static bool mIsAttacking = false;
	inline static bool mTookDamage = false;
	inline static bool mIsDead = false;

	StateMachine::Condition mConditions{ [this] { return this->Conditions(); } };

	Vector<StateMachine::Condition> mConditionIdle{ mConditions };
	Vector<StateMachine::Condition> mConditionRun{ mConditions };
	Vector<StateMachine::Condition> mConditionAttack{ mConditions };
	Vector<StateMachine::Condition> mConditionHit{ mConditions };
	Vector<StateMachine::Condition> mConditionDie{ mConditions };


public:
	ScriptAgent* mAgent;

	// Fonctions
	virtual void Initia() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Initia(); SetPlayer(nullptr); SetCellTarget(nullptr); mAgent->mCharacter->SetMaxLife(100); mAgent->mCharacter->SetDamage(5); }
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

		mStateMachine = GameManager::GetStatesSystem().CreateStateMachine(m_pOwner);

		// StateMachine
		mStateMachine->AddAction(mIdle, OnBeginIdle, OnUpdateIdle, OnEndIdle);
		mStateMachine->AddAction(mRunning, OnBeginRunning, OnUpdateRunning, OnEndRunning);
		mStateMachine->AddAction(mAttack, OnBeginAttack, OnUpdateAttack, OnEndAttack);
		mStateMachine->AddAction(mHit, OnBeginHit, OnUpdateHit, OnEndHit);
		mStateMachine->AddAction(mDie, OnBeginDie, OnUpdateDie, OnEndDie);

		mStateMachine->AddTransition(mConditionRun, mIdle, mRunning);
		mStateMachine->AddTransition(mConditionAttack, mRunning, mIdle);
		mStateMachine->AddTransition(mConditionHit, mIdle, mHit);
		mStateMachine->AddTransition(mConditionDie, mIdle, mDie);

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
				mIsChasingPlayer = true;
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

	void SetMaxLife(int life) { mAgent->mCharacter->SetMaxLife(life); }
	int GetMaxLife() { return mAgent->mCharacter->GetMaxLife(); }

	void SetDamage(int damage) { mAgent->mCharacter->SetDamage(damage); }
	int GetDamage() { return mAgent->mCharacter->GetDamage(); }
	
	ScriptGrid* GetGrid() { return mAgent->GetPathFinding()->GetGrid(); }

	// === Idle State Functions ===
	static void OnBeginIdle() { Console::Log("[Idle] Begin"); }
	static void OnUpdateIdle() { Console::Log("[Idle] Updating... Waiting for start request."); }
	static void OnEndIdle() { Console::Log("[Idle] End"); }

	// === Running State Functions ===
	static void OnBeginRunning() { Console::Log("[Running] Begin"); }
	static void OnUpdateRunning() { Console::Log("[Running] Updating... Doing work."); }
	static void OnEndRunning() { Console::Log("[Running] End"); }

	// === Attack State Functions ===
	static void OnBeginAttack() { Console::Log("[Attack] Begin"); }
	static void OnUpdateAttack() { Console::Log("[Attack] Updating... Doing damage."); }
	static void OnEndAttack() { Console::Log("[Attack] End"); }

	// === Hit State Functions ===
	static void OnBeginHit() { Console::Log("[Hit] Begin"); }
	static void OnUpdateHit() { Console::Log("[Hit] Updating... Taking damage."); }
	static void OnEndHit() { Console::Log("[Hit] End"); }

	// === Die State Functions ===
	static void OnBeginDie() { Console::Log("[Die] Begin"); }
	static void OnUpdateDie() { Console::Log("[Die] Updating... Has no life."); }
	static void OnEndDie() { Console::Log("[Die] End"); }

	bool Conditions()
	{
		mIsIdle = false;
		mTookDamage = false;
		mIsChasingPlayer = false;
		mIsAttacking = false;
		mIsDead = false;

		ScriptCharacter* targetCharacter = mPlayer->mCharacter;
		ScriptCharacter* myCharacter = mPlayer->mCharacter;

		Vector3f32 playerPos = mPlayer->GetWorldPosition();
		Vector3f32 myPos = GetWorldPosition();
		float dist = abs((playerPos.x - myPos.x) + (playerPos.y - myPos.y) + (playerPos.z - myPos.z));
		if (dist <= 0.5f)
		{
			targetCharacter->Damage(myCharacter->GetDamage());
			mTookDamage = true;
		}

		/*if (dist <= 0.5f)
		{
			mIsIdle = false;
			mIsAttacking = true;

			if (this->mPlayer->mCharacter->Damage(mPlayer->mCharacter->GetDamage()))
			{
				mTookDamage = true;
			}
			else
			{
				mTookDamage = false;
			}

			if (this->mAgent->mCharacter->GetLife() == 0)
			{
				mIsIdle = false;
				mIsChasingPlayer = false;
				mIsAttacking = false;
				mTookDamage = false;
				mIsDead = true;
			}
			else
			{
				mIsDead = false;
			}

			
		}
		else if (dist > 0.5f)
		{
			mIsChasingPlayer = true;
			mIsIdle = false;
		}
		else
		{
			mIsIdle = true;
		}*/
		return true;
	}

	bool IsIdle() { return mIsIdle; }
	bool IsChasingPlayer() { return mIsChasingPlayer; }
	bool IsAttacking() { return mIsAttacking; }
	bool TookDamage() { return mTookDamage; }
	bool IsDead() { return mIsDead; }


END_SCRIPT