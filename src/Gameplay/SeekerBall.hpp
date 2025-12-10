#pragma once
#include "Shootable.hpp"
#include "Character.hpp"

#define DEFAULT_SEEKER_BALL_DAMAGE 30

DECLARE_SCRIPT(ScriptSeekerBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;

	virtual void Initia() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Initia(); }
	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) 
	{
		other->GetScript<ScriptCharacter>()->Damage(mShootable->GetDamage());
		m_pOwner->Destroy();
	}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}









	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene) { return CreateBall(pos, dir, speed, damage, scene, nullptr, nullptr); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, dir, speed, damage, scene, nullptr, texture); }
	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, dir, speed, damage, scene, geometry, nullptr); }

	static ScriptSeekerBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptSeekerBall>(scene, geometry, texture);
		gameBall.SetName("Ball");
		gameBall.AddComponent<gce::BoxCollider>()->SetActive(false);
		ScriptSeekerBall* ball = gameBall.GetScript<ScriptSeekerBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	END_SCRIPT