#pragma once
#include "Shootable.hpp"
#include "Character.hpp"

#define DEFAULT_BALL_DAMAGE 5

DECLARE_SCRIPT(ScriptBall, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
	ScriptShootable* mShootable;
	cstr mName;

	virtual void Initia() { mShootable = m_pOwner->AddScript<ScriptShootable>(); mShootable->Initia(); }
	virtual void Start() { mName = mShootable->mObject->mEntity->GetGameObject()->GetName(); }
	virtual void Update() {}
	virtual void Destroy() { m_pOwner->RemoveComponent< gce::BoxCollider >();  m_pOwner->RemoveComponent< gce::PhysicComponent >(); }

	virtual void CollisionEnter(gce::GameObject* other) 
	{ 
		ScriptCharacter* character = other->GetScript<ScriptCharacter>();
		if (character != nullptr)
		{
			if ((mName == "EnemyBall" && other->GetName() == "Player") || (mName == "PlayerBall" && other->GetName() == "Enemy"))
			{
				character->Damage(mShootable->GetDamage());
				mShootable->mObject->mEntity->DestroyEntity();
			}
			if (mName == "EnemyBall" && other->GetName() == "PlayerBall")
			{
				mShootable->mObject->mEntity->DestroyEntity();
				other->SetActive(false);
			}
		}
	}
	virtual void CollisionStay(gce::GameObject* other) {}
	virtual void CollisionExit(gce::GameObject* other) {}



	




	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr, color); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture, color); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene) { return CreateBall(name, pos, dir, speed, damage, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(name, pos, dir, speed, damage, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(name, pos, dir, speed, damage, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(name, pos, dir, speed, damage, scene, geometry, nullptr, color); }

	static ScriptBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptBall>(scene, geometry, texture,color);
		gameBall.AddComponent<gce::BoxCollider>()->SetActive(true);
		gameBall.AddComponent<gce::PhysicComponent>()->SetActive(false);
		gameBall.SetName(name);
		gameBall.transform.SetWorldScale(gce::Vector3f32{ 1.f,1.f,1.f });
		ScriptBall* ball = gameBall.GetScript<ScriptBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed, damage);
		return ball;
	}



	END_SCRIPT