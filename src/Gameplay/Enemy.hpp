#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Grid.hpp"

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	ScriptPlayer* mPlayer;

public:
	ScriptAgent* mAgent;

	virtual void Initia() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Initia(); SetPlayer(nullptr); }
	virtual void Start() 
	{ 
		mAgent->Start();
		
		ScriptGrid* grid = GetGrid();
		Cell* nerestCell = grid->GetNearestCell(GetWorldPosition());
		SetWorldPosition(grid->GetPosOfCell(nerestCell));
	}
	virtual void Update() 
	{ 
		WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.05f)); // temp deplacement
		ScriptEntity* myParentEntity = mAgent->mCharacter->mEntity;
	
		if (mPlayer != nullptr)
		{
			myParentEntity->FocusEntity(myParentEntity, mPlayer->mCharacter->mEntity); // temp rotation
		}

		mAgent->mCharacter->CreateBallInFront<ScriptBall>(5.f, gce::SHAPES.CUBE, myParentEntity);//temp creation de ball
		
		if (mAgent->GetPaths()->Size() < 1)
		{
			mAgent->GoToCell(mPlayer->GetWorldPosition());
		}
	}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}


	void SetWorldPosition(gce::Vector3f32 position) { mAgent->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mAgent->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mAgent->WorldTranslate(position); }

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

	ScriptGrid* GetGrid() { return mAgent->GetPathFinding()->GetGrid(); }

END_SCRIPT