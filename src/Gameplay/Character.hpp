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

public:
	ScriptEntity* mEntity;

	virtual void Start() 
	{ 
		mEntity = m_pOwner->AddScript<ScriptEntity>();
		mEntity->Start();

		int life = 1;
		SetLife(life);
		SetMaxLife(life);
		SetSpeed(1.f);
		SetTargetIsSet(false);
	}
	virtual void Update() 
	{
		//light engine Entity::Update()
		/*
		float dt = GetDeltaTime();
		float distance = dt * mSpeed;
		sf::Vector2f translation = distance * mDirection;
		mpShape->move(translation);

		if (mTarget.isSet) 
		{
			float x1 = GetPosition().x;
			float y1 = GetPosition().y;

			float x2 = x1 + mDirection.x * mTarget.distance;
			float y2 = y1 + mDirection.y * mTarget.distance;

			Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

			Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

			mTarget.distance -= distance;

			if (mTarget.distance <= 0.f)
			{
				SetPosition(mTarget.position.x, mTarget.position.y);
				mDirection = sf::Vector2f(0.f, 0.f);
				mTarget.isSet = false;
			}
		}
		*/
	}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	//void GoToPosition
	/*bool Entity::GoToPosition(int x, int y, float speed)
	{
		if (GoToDirection(x, y, speed) == false)
			return false;

		sf::Vector2f position = GetPosition();

		mTarget.position = { x, y };
		mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
		mTarget.isSet = true;

		return true;
	}*/

	//damage
	//health

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