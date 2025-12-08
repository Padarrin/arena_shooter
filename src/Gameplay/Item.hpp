#pragma once
#include "Object.hpp"

DECLARE_SCRIPT(ScriptItem, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	float mTurnSpeed;

public:
	ScriptObject* mObject;

	virtual void Initia() { mObject = m_pOwner->AddScript<ScriptObject>(); mObject->Initia(); }
	virtual void Start() { mObject->Start(); }
	virtual void Update() { }
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) { mObject->CollisionEnter(other); }
	virtual void CollisionStay(GameObject* other) { mObject->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mObject->CollisionExit(other); }

	void SetTurnSpeed(float turnSpeed) { mTurnSpeed = turnSpeed; }
	float GetTurnSpeed() { return mTurnSpeed; }

END_SCRIPT