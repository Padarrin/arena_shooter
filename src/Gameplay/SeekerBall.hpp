#pragma once
#include "Shootable.hpp"

DECLARE_SCRIPT(ScriptSeekerBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;

	virtual void Start() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}









	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene) { return CreateBall(pos, dir, speed, scene, nullptr, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, dir, speed, scene, nullptr, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, dir, speed, scene, geometry, nullptr); }

	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptSeekerBall>(scene, geometry, texture);
		ScriptSeekerBall* ball = gameBall.GetScript<ScriptSeekerBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	END_SCRIPT