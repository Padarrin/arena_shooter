#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptObject, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:

public:
	ScriptEntity* mEntity;

	virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); }
	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}

END_SCRIPT