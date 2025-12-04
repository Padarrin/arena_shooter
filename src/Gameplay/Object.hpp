#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptObject, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:

public:
	ScriptEntity* mEntity;

	virtual void Start() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

END_SCRIPT