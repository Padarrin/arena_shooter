#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;

public:
	ScriptAgent* mAgent;

	virtual void Initia() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Initia(); mPlayer = nullptr;}
	virtual void Start() { mAgent->Start(); }
	virtual void Update() 
	{ 
		WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.01f)); // temp deplacement
		ScriptEntity* myParentEntity = mAgent->mCharacter->mEntity;
	
		if (mPlayer != nullptr)
		{
			myParentEntity->FocusEntity(myParentEntity, mPlayer->mCharacter->mEntity); // temp rotation
		}

		mAgent->mCharacter->CreateBallInFront<ScriptBall>(100.f, gce::SHAPES.CUBE, myParentEntity);//temp creation de ball
	}
	virtual void Destroy() {}

	virtual void CollisionEnter(GameObject* other) { mAgent->CollisionEnter(other); }
	virtual void CollisionStay(GameObject* other) { mAgent->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mAgent->CollisionExit(other); }


	void SetWorldPosition(gce::Vector3f32 position) { mAgent->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mAgent->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mAgent->WorldTranslate(position); }

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT