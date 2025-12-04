#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptCharacter, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	struct Target //GoToPosition
	{
		gce::Vector3f32 position;
		float distance;
		bool isSet;
	};

	int mLife;
	int mMaxLife;

	float mSpeed;
	Target mTarget;

	int mDamage;

public:
	ScriptEntity* mEntity;

	virtual void Start() 
	{ 
		mEntity = m_pOwner->AddScript<ScriptEntity>();

		int life = 1;
		int damage = 1;
		SetLife(life);
		SetMaxLife(life);
		SetSpeed(1.f);
		SetTargetIsSet(false);
		SetDamage(damage);
	}
	virtual void Update() 
	{
		float dt = gce::GameManager::DeltaTime();
		float distance = dt * mSpeed;

		if (mTarget.isSet) 
		{
			gce::Vector3f32 pos = mEntity->GetWorldPosition();

			float x1 = pos.x;
			float y1 = pos.y;
			float z1 = pos.z;

			mTarget.distance -= distance;

			if (mTarget.distance <= 0.f)
			{
				mEntity->SetWorldPosition(mTarget.position);
				mTarget.isSet = false;
			}
		}
	}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	bool GoToPosition(gce::Vector3f32 pos, float speed)
	{
		gce::Vector3f32 position = mEntity->GetWorldPosition();

		mTarget.position = pos;
		mTarget.distance = GetDistance(position, pos);
		mTarget.isSet = true;

		return true;
	}

	void Damage(int damage) { mLife -= damage; }
	void Heal(int heal) { mLife += heal; }

	void SetDamage(int damage) { mDamage = damage; }
	int GetDamage() { return mDamage; }

	void SetMaxLife(int maxLife) { mMaxLife = maxLife; SetLife(maxLife); }
	int GetMaxLife() { return mMaxLife; }

	void SetLife(int life) { mLife = life; }
	int GetLife() { return mLife; }

	void SetSpeed(float speed) { mSpeed = speed; }
	float GetSpeed() { return mSpeed; }

	void SetTarget(Target target) { mTarget = target; }
	Target GetTarget() { return mTarget; }

	void SetTargetIsSet(bool targetIsSet) { mTarget.isSet = targetIsSet; }
	bool GetTargetIsSet() { return mTarget.isSet; }

END_SCRIPT