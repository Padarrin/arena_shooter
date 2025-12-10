#pragma once
#include "Shootable.hpp"

DECLARE_SCRIPT(ScriptBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;

	virtual void Initia() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Initia(); }
	virtual void Start() { mShootable->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) { mShootable->CollisionEnter(other); if (other->GetName() == "Floor") m_pOwner->Destroy(); }
	virtual void CollisionStay(GameObject* other) { mShootable->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mShootable->CollisionExit(other); }



	




	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, nullptr, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, scene, geometry, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene) { return CreateBall(pos, dir, speed, scene, nullptr, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, dir, speed, scene, nullptr, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, dir, speed, scene, geometry, nullptr); }

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptBall>(scene, geometry, texture);
		gameBall.SetName("Ball");
		gameBall.transform.SetWorldScale(gce::Vector3f32{ 0.5f,0.5f,0.5f });
		gameBall.AddComponent<gce::BoxCollider>()->SetActive(true);
		ScriptBall* ball = gameBall.GetScript<ScriptBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}



	END_SCRIPT