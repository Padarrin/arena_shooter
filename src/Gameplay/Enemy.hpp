#pragma once
#include "Agent.hpp"
#include "Ball.hpp"
#include <Console.h>

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

ScriptAgent* mAgent;

virtual void Start() { mAgent = m_pOwner->AddScript <ScriptAgent>(); mAgent->Start(); }
virtual void Update()
{
	WorldTranslate(gce::Vector3f32(0.f, 0.f, 0.01f)); // temp
	mAgent->mCharacter->mEntity->WorldRotate(gce::Vector3f32(0.f, 0.1f, 0.f));
	gce::Quaternion rot = mAgent->mCharacter->mEntity->GetWorldRotate();
	float rotY = rot.GetY();

	//gce::Vector3f32 dir = gce::Vector3f32(0.f, 0.f, 0.f);

	//dir.x = gce::Cos(rotY * gce::PI);
	//dir.z = gce::Sin(rotY * gce::PI);

	//std::cout << dir.z << std::endl;
	ScriptBall* ball = ScriptBall::CreateBall(GetWorldPosition(), mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldForward(), 100.f, *m_pOwner->m_pScene, gce::SHAPES.CUBE); //temp
	ball->mShootable->mObject->mEntity->SetWorldRotate(gce::Vector3f32(0.f, rotY, 0.f));
}
virtual void Destroy() {}

virtual void CollisionEnter() {}
virtual void CollisionStay() {}
virtual void CollisionExit() {}


void SetWorldPosition(gce::Vector3f32 position) { mAgent->SetWorldPosition(position); }
gce::Vector3f32 GetWorldPosition() { return mAgent->GetWorldPosition(); }
void WorldTranslate(gce::Vector3f32 position) { mAgent->WorldTranslate(position); }




END_SCRIPT