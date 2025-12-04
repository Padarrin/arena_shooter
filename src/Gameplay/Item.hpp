#pragma once
#include "Object.hpp"

DECLARE_SCRIPT(ScriptItem, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	float mSpeed;
	gce::Vector3f32 mPos;
	gce::Vector3f32 mDisToDestroy;

	bool mIsGrabbed;
	bool mInInventory;

public:
	ScriptObject* mObject;

	virtual void Start() { mObject = m_pOwner->AddScript<ScriptObject>(); mObject->Start(); SetDisToDestroy(gce::Vector3f32(1000.f, 1000.f, 1000.f)); }
	virtual void Update() { UpdateDirection(); UpdateOutArea(); }
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
			gce::Vector3f32 translation = mPos * distance;
			mObject->mEntity->WorldTranslate(translation);
		}
	}

	void UpdateOutArea()
	{
		gce::Vector3f32 pos = mObject->mEntity->GetWorldPosition();
		if (mPos.x + mDisToDestroy.x < abs(pos.x) || mPos.y + mDisToDestroy.y < abs(pos.y) || mPos.z + mDisToDestroy.z < abs(pos.z))
		{
			m_pOwner->Destroy();
		}
	}

	void SetSpeed(float speed) { mSpeed = speed; }
	float GetSpeed() { return mSpeed; }

	void SetStartPos(gce::Vector3f32 startPos) { mPos = startPos; }
	gce::Vector3f32 GetStartPos() { return mPos; }

	void SetDisToDestroy(gce::Vector3f32 disToDestroy) { mDisToDestroy = disToDestroy; }
	gce::Vector3f32 GetDisToDestroy() { return mDisToDestroy; }

	bool IsGrabbed() { return mIsGrabbed; }
	bool InInventory() { return mInInventory; }

END_SCRIPT