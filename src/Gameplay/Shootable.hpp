#pragma once
#include "Object.hpp"
#include "Time.h"

DECLARE_SCRIPT(ScriptShootable, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	float mSpeed;
	gce::Vector3f32 mDirection;
	gce::Vector3f32 mStartPos;
	gce::Vector3f32 mDisToDestroy;

	int mDamage;

	Time mDestroyTime;
public:
	ScriptObject* mObject;

	virtual void Initia() { mObject = m_pOwner->AddScript<ScriptObject>(); mObject->Initia(); mDestroyTime = Time(5);  SetDamage(0); }
	virtual void Start() { }
	virtual void Update() { UpdateDirection(); UpdateOutTime(); mDestroyTime.Update(GameManager::GameDeltaTime());}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(gce::GameObject* other) {}
	virtual void CollisionExit(gce::GameObject* other) {}

	void UpdateDirection()
	{
		if (mSpeed != 0.f)
		{
			float dt = gce::GameManager::GameDeltaTime();
			float distance = dt * mSpeed;
			gce::Vector3f32 translation = mDirection * distance;
			WorldTranslate(translation);
		}
	}

	void UpdateOutTime()
	{
		if (mDestroyTime.IsFinish())
		{
			mObject->mEntity->DestroyEntity();
		}
	}

	bool GoToDirection(float x, float y, float z, float speed)
	{
		return GoToDirection(gce::Vector3f32(x, y, z), speed);
	}

	bool GoToDirection(gce::Vector3f32 dir, float speed)
	{
		gce::Vector3f32 position = GetWorldPosition();
		gce::Vector3f32 direction = gce::Vector3f32(dir.x - position.x, dir.y - position.y, dir.z - position.z);

		bool success = Normalize(direction);
		if (success == false)
			return false;

		SetDirection(direction.x, direction.y, direction.z, speed);

		return true;
	}

	static void SetShootable(ScriptShootable* shootable, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed, int damage)
	{
		shootable->SetWorldPosition(pos);
		shootable->SetDirection(dir, speed);
		shootable->SetDamage(damage);
	}

	void SetDirection(float x, float y, float z, float speed)
	{
		SetDirection(gce::Vector3f32(x, y, z), speed);
	}

	void SetDirection(gce::Vector3f32 dir, float speed)
	{
		if (speed > 0.f)
			mSpeed = speed;

		mDirection = dir;
	}

	gce::Vector3f32 GetDirection() { return mDirection; }

	void SetSpeed(float speed) { mSpeed = speed; }
	float GetSpeed() { return mSpeed; }

	void SetDestroyTime(Time destroyTime) { mDestroyTime = destroyTime; }
	Time* GetDestroyTime() { return &mDestroyTime; }

	void SetDamage(int damage) { mDamage = damage; }
	int GetDamage() { return mDamage; }

	void SetWorldPosition(gce::Vector3f32 position) { mObject->mEntity->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition(){ return mObject->mEntity->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mObject->mEntity->WorldTranslate(position); }

	END_SCRIPT