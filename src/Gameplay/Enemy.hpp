#pragma once
#include "Agent.hpp"
#include "Ball.hpp"

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

ScriptAgent* mAgent;

virtual void Start() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Start(); }
virtual void Update()
{
	WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.01f)); // temp
	mAgent->mCharacter->mEntity->WorldRotate(gce::Vector3f32(0.f, 0.1f, 0.f));
	gce::Quaternion rot = mAgent->mCharacter->mEntity->GetWorldRotate();
	ScriptBall* ball = ScriptBall::CreateBall(GetWorldPosition(), gce::Vector3f32(1.f, 0.f, 0.f), 100.f, *m_pOwner->m_pScene, gce::SHAPES.CUBE); //temp
	ball->mShootable->mObject->mEntity->SetWorldRotate(gce::Vector3f32(rot.GetX(), 0.f, 0.f));
}
virtual void Destroy() {}

virtual void CollisionEnter() {}
virtual void CollisionStay() {}
virtual void CollisionExit() {}


void SetWorldPosition(gce::Vector3f32 position) { mAgent->SetWorldPosition(position); }
gce::Vector3f32 GetWorldPosition() { return mAgent->GetWorldPosition(); }
void WorldTranslate(gce::Vector3f32 position) { mAgent->WorldTranslate(position); }




END_SCRIPT