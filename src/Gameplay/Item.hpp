#pragma once
#include "Object.hpp"

DECLARE_SCRIPT(ScriptItem, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	float mTurnSpeed;

public:
	ScriptObject* mObject;

	virtual void Initia() { mObject = m_pOwner->AddScript<ScriptObject>(); mObject->Initia(); }
	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}

	void SetTurnSpeed(float turnSpeed) { mTurnSpeed = turnSpeed; }
	float GetTurnSpeed() { return mTurnSpeed; }

	void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
	ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT