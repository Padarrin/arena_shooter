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



	




	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, nullptr, color); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, texture, color); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene) { return CreateBall(pos, dir, speed, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, dir, speed, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, dir, speed, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(pos, dir, speed, scene, geometry, nullptr, color); }

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptBall>(scene, geometry, texture,color);
		ScriptBall* ball = gameBall.GetScript<ScriptBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}



	END_SCRIPT