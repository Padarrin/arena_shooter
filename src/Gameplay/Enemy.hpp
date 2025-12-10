#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include <chrono>

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;

	using mClock = std::chrono::steady_clock;
	mClock::time_point mPreviousTime = mClock::now();

public:
	ScriptAgent* mAgent;

	virtual void Initia() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Initia(); mPlayer = nullptr; mAgent->mCharacter->SetMaxLife(100); mAgent->mCharacter->SetDamage(5); }
	virtual void Start() { mAgent->Start(); }
	virtual void Update() 
	{ 
		WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.01f)); // temp deplacement
		ScriptEntity* myParentEntity = mAgent->mCharacter->mEntity;
	
		if (mPlayer != nullptr)
		{
			myParentEntity->FocusEntity(myParentEntity, mPlayer->mCharacter->mEntity); // temp rotation
		}

		auto currentTime = mClock::now();
		auto elapsed = currentTime - mPreviousTime;

		if (elapsed >= std::chrono::seconds(3))
		{
			mAgent->mCharacter->CreateBallInFront<ScriptBall>("EnemyBall", 100.f, gce::SHAPES.CUBE, myParentEntity);
			mPreviousTime = currentTime;
		}
	}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) 
	{
		mAgent->CollisionEnter(other);

		if (other->GetName() == "PlayerBall")
		{
			mAgent->mCharacter->Damage(mPlayer->mCharacter->GetDamage());
			other->Destroy();
		}
	}
	virtual void CollisionStay(GameObject* other) { mAgent->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mAgent->CollisionExit(other); }


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

END_SCRIPT