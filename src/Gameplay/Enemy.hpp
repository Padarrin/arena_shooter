#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include <chrono>
#include "../Core/StateMachine/StateMachine.h"


DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;
	Cell* mCellTarget;
	bool mIsNoPath;

	using mClock = std::chrono::steady_clock;
	mClock::time_point mPreviousTime = mClock::now();

	// StateMachine
	StateMachine* mStateMachine;

	String running = "Running";
	String attack = "Attack";
	String hit = "Hit";
	String die = "Die";

	inline static bool isChasingPlayer = true;
	inline static bool isAttacking = false;
	inline static bool tookDamage = false;
	inline static bool isDead = false;

	StateMachine::Condition condition2{ IsChasingPlayer };
	StateMachine::Condition condition3{ IsAttacking };
	StateMachine::Condition condition4{ TookDamage };
	StateMachine::Condition condition5{ IsDead };

	Vector<StateMachine::Condition> conditionRun{ condition2 };
	Vector<StateMachine::Condition> condittionAttack{ condition3 };
	Vector<StateMachine::Condition> conditionHit{ condition4 };
	Vector<StateMachine::Condition> conditionDie{ condition5 };


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


		// StateMachine
		mStateMachine->AddAction(running, OnBeginRunning, OnUpdateRunning, OnEndRunning);
		mStateMachine->AddAction(attack, OnBeginAttack, OnUpdateAttack, OnEndAttack);
		mStateMachine->AddAction(hit, OnBeginHit, OnUpdateHit, OnEndHit);
		mStateMachine->AddAction(die, OnBeginDie, OnUpdateDie, OnEndDie);

		mStateMachine->AddTransition(conditionRun, running);
		mStateMachine->AddTransition(condittionAttack, attack);
		mStateMachine->AddTransition(conditionHit, hit);
		mStateMachine->AddTransition(conditionDie, die);

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
				isChasingPlayer = true;
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
			//mAgent->mCharacter->CreateBallInFront<ScriptBall>(100.f, DEFAULT_BALL_DAMAGE, gce::SHAPES.CUBE, myParentEntity);
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

	static bool SetRun(bool run) { isChasingPlayer = run; }
	static bool IsChasingPlayer() { return isChasingPlayer; }
	static bool IsAttacking() { return isAttacking; }
	static bool TookDamage() { return tookDamage; }
	static bool IsDead() { return isDead; }

END_SCRIPT