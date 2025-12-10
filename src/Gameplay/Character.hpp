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
		mEntity->Start();

		SetTargetIsSet(false);
		
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

	virtual void CollisionEnter(gce::GameObject* other) { mEntity->CollisionEnter(other); }
	virtual void CollisionStay(GameObject* other) { mEntity->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mEntity->CollisionExit(other); }

	template<typename T>
	static void CreateBallInFront(cstr name, float speed, gce::Geometry* geometry, ScriptEntity* entityGiveInformation , gce::GameObject* objectCamera = nullptr)
	{
		gce::Quaternion rot = entityGiveInformation->GetWorldRotate();
		gce::Quaternion rotCamera = { rot.GetX(), 1.f, 1.f, 1.f};
		if (objectCamera != nullptr)
			rotCamera = objectCamera->transform.GetWorldRotation();

		T* ball = T::CreateBall(name, entityGiveInformation->GetWorldPosition() + entityGiveInformation->GetWorldForward(), entityGiveInformation->GetWorldForward(), speed, *entityGiveInformation->GetScene(), geometry);
		gce::Vector3f32 posBall = ball->mShootable->mObject->mEntity->GetWorldPosition();
		
		ball->mShootable->mObject->mEntity->SetWorldRotate(gce::Vector3f32(rotCamera.GetX(), rot.GetY(), rot.GetZ()));
	}

	bool GoToPosition(gce::Vector3f32 pos, float speed)
	{
		gce::Vector3f32 position = mEntity->GetWorldPosition();

		mTarget.position = pos;
		mTarget.distance = GetDistance(position, pos);
		mTarget.isSet = true;

		return true;
	}

	void Damage(int damage) 
	{ 
		mLife -= damage; 
		if (mLife < 1) { mEntity->GetGameObject()->Destroy(); } 
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
		else if (mLife < 1) { mEntity->GetGameObject()->Destroy(); }
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