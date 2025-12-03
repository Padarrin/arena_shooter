#pragma once
#include "Object.hpp"

DECLARE_SCRIPT(ScriptShootable, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	float mSpeed;
	gce::Vector3f32 mDirection;
public:
	ScriptObject* mObject;

	virtual void Start() { mObject = m_pOwner->AddScript<ScriptObject>(); mObject->Start(); }
	virtual void Update() { UpdateDirection(); }
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void UpdateDirection()
	{
		if (mSpeed != 0.f)
		{
			float dt = gce::GameManager::DeltaTime();
			float distance = dt * mSpeed;
			gce::Vector3f32 translation = mDirection * distance;
			mObject->mEntity->Translate(translation);
		}
	}

	bool GoToDirection(float x, float y, float z, float speed)
	{
		return GoToDirection(gce::Vector3f32(x, y, z), speed);
	}

	bool GoToDirection(gce::Vector3f32 dir, float speed)
	{
		gce::Vector3f32 position = mObject->mEntity->GetWorldPosition();
		gce::Vector3f32 direction = gce::Vector3f32(dir.x - position.x, dir.y - position.y, dir.z - position.z);

		bool success = Normalize(direction);
		if (success == false)
			return false;

		SetDirection(direction.x, direction.y, direction.z, speed);

		return true;
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

	void SetShootable(ScriptShootable* shootable, gce::Vector3f32 pos, gce::Vector3f32 dir, float speed)
	{
		shootable->mObject->mEntity->SetWorldPosition(pos);
		shootable->SetDirection(dir, speed);
	}

	END_SCRIPT