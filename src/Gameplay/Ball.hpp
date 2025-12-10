#pragma once
#include "Shootable.hpp"
#include "Character.hpp"

#define DEFAULT_BALL_DAMAGE 5

DECLARE_SCRIPT(ScriptBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;

	virtual void Initia() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Initia(); }
	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) 
	{ 
		ScriptCharacter* character = other->GetScript<ScriptCharacter>();
		if (character != nullptr)
		{
			character->Damage(mShootable->GetDamage());
		}
		m_pOwner->Destroy();
	}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}



	




	static ScriptBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene) { return CreateBall(pos, dir, speed, damage, scene, nullptr, nullptr); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(pos, dir, speed, damage, scene, nullptr, texture); }
	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(pos, dir, speed, damage, scene, geometry, nullptr); }

	static ScriptBall* CreateBall(gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptBall>(scene, geometry, texture);
		gameBall.SetName("Ball");
		gameBall.transform.SetWorldScale(gce::Vector3f32{ 0.125f,0.125f,0.125f });
		gameBall.AddComponent<gce::BoxCollider>()->SetActive(true);
		ScriptBall* ball = gameBall.GetScript<ScriptBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed, damage);
		return ball;
	}



	END_SCRIPT