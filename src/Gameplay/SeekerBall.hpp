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
	virtual void Update() 
	{
		/*float deltaTime = gce::GameManager::GameDeltaTime();
		if (deltaTime > 0.f)
		{

		}
		*/
	}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) 
	{
		other->GetScript<ScriptCharacter>()->Damage(mShootable->GetDamage());
		m_pOwner->Destroy();
	}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}






	
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, nullptr, color); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color) { return CreateBall(name, pos, gce::Vector3f32(0.f, 0.f, 0.f), 0.f, damage, scene, geometry, texture, color); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene) { return CreateBall(name, pos, dir, speed, damage, scene, nullptr, nullptr, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Texture* texture) { return CreateBall(name, pos, dir, speed, damage, scene, nullptr, texture, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry) { return CreateBall(name, pos, dir, speed, damage, scene, geometry, nullptr, DEFAULTCOLOR); }
	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color) { return CreateBall(name, pos, dir, speed, damage, scene, geometry, nullptr, color); }


	static ScriptSeekerBall* CreateBall(cstr name, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage, gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color)
	{
		gce::GameObject& gameBall = CreateGameObject<ScriptSeekerBall>(scene, geometry, texture, color);
		gameBall.SetName(name);
		gameBall.AddComponent<gce::BoxCollider>()->SetActive(false);
		ScriptSeekerBall* ball = gameBall.GetScript<ScriptSeekerBall>();
		ball->mShootable->SetShootable(ball->mShootable, pos, dir, speed);
		return ball;
	}

	END_SCRIPT