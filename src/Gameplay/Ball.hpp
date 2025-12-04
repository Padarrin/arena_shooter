#pragma once
#include "Shootable.hpp"

DECLARE_SCRIPT(ScriptBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;

	virtual void Start() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}



	




	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, nullptr, nullptr);
		ball->mShootable->SetShootable(ball->mShootable, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Texture* texture)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, nullptr, texture);
		ball->mShootable->SetShootable(ball->mShootable, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, geometry, nullptr);
		ball->mShootable->SetShootable(ball->mShootable, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, geometry, texture);
		ball->mShootable->SetShootable(ball->mShootable, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, nullptr, nullptr);
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Texture* texture)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, nullptr, texture);
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, geometry, nullptr);
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		ScriptBall* ball = CreateGameObject<ScriptBall>(scene, geometry, texture);
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}



	END_SCRIPT