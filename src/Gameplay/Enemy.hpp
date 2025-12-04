#pragma once
#include "Agent.hpp"
#include "Ball.hpp"

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

ScriptAgent* mAgent;

virtual void Start() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Start(); }
virtual void Update() 
{ 
	mAgent->mCharacter->mEntity->WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.1f)); // temp
	ScriptBall* ball = ScriptBall::CreateBall(mAgent->mCharacter->mEntity->GetWorldPosition(), gce::Vector3f32(1.f, 0.f, 0.f), 100.f, *m_pOwner->m_pScene, gce::SHAPES.CUBE); //temp
}
virtual void Destroy() {}

virtual void CollisionEnter() {}
virtual void CollisionStay() {}
virtual void CollisionExit() {}



END_SCRIPT