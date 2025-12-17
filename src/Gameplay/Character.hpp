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

	int mDamage;
	int mLife;
	int mMaxLife;

	float mSpeed;
	Target mTarget;

public:
	ScriptEntity* mEntity;

	virtual void Initia()
	{ 
		mEntity = m_pOwner->AddScript<ScriptEntity>();
		mEntity->Initia();

		int life = 1;
		int damage = 1;
		SetDamage(damage);
		SetLife(life);
		SetMaxLife(life);

		SetSpeed(1.f);
	}
	virtual void Start() 
	{ 
		SetTargetIsSet(false);
	}
	virtual void Update() 
	{
		float dt = gce::GameManager::GameDeltaTime();
		float distance = dt * mSpeed;

		if (mTarget.isSet) 
		{
			gce::Vector3f32 pos = mEntity->GetWorldPosition();
			gce::Vector3f32 otherPosition = mTarget.position;

			gce::Vector3f32 direction = otherPosition - pos;
			direction = direction.Normalize();
			
			mTarget.distance -= distance;
			gce::Vector3f32 translate = direction * distance;
			mEntity->WorldTranslate(translate);

			if (mTarget.distance <= 0.f)
			{
				mEntity->SetWorldPosition(otherPosition);
				mTarget.isSet = false;
			}
		}
	}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(gce::GameObject* other) {}
	virtual void CollisionExit(gce::GameObject* other) {}

	void GoToPosition(gce::Vector3f32 pos, float speed)
	{
		gce::Vector3f32 position = mEntity->GetWorldPosition();

		mTarget.position = pos;
		mTarget.distance = GetDistance(position, pos);
		mTarget.isSet = true;
	}

	bool Damage(int damage) 
	{ 
		mLife -= damage; 
		if (mLife < 1) { mEntity->DestroyCharacter(); }
		return true;
	}
	void Heal(int heal) 
	{ 
		mLife += heal; 
		if (mLife > mMaxLife) { mLife = mMaxLife; } 
	}
	void SetDamage(int damage) 
	{ 
		mDamage = damage; 
	}
	int GetDamage() 
	{ 
		return mDamage; 
	}
	void SetMaxLife(int maxLife) 
	{ 
		mMaxLife = maxLife; 
		SetLife(maxLife); 
	}
	int GetMaxLife() 
	{ 
		return mMaxLife; 
	}
	void SetLife(int life) 
	{ 
		mLife = life; 
		if (mLife > mMaxLife) { mLife = mMaxLife; } 
		else if (mLife < 1) { mEntity->DestroyCharacter(); }
	}
	int GetLife() 
	{ 
		return mLife; 
	}

	void SetSpeed(float speed) { mSpeed = speed; }
	float GetSpeed() { return mSpeed; }

	void SetTarget(Target target) { mTarget = target; }
	Target GetTarget() { return mTarget; }

	void SetTargetIsSet(bool targetIsSet) { mTarget.isSet = targetIsSet; }
	bool GetTargetIsSet() { return mTarget.isSet; }

END_SCRIPT