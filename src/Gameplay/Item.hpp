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

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void SetTurnSpeed(float turnSpeed) { mTurnSpeed = turnSpeed; }
	float GetTurnSpeed() { return mTurnSpeed; }

END_SCRIPT