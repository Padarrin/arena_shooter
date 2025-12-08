#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptObject, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:

public:
	ScriptEntity* mEntity;

	virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); }
	virtual void Start() { mEntity->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) { mEntity->CollisionEnter(other); }
	virtual void CollisionStay(GameObject* other) { mEntity->CollisionStay(other); }
	virtual void CollisionExit(GameObject* other) { mEntity->CollisionExit(other); }

END_SCRIPT