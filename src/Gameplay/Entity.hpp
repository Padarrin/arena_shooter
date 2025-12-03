#pragma once
#include "../Engine/GameObject.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void Translate(gce::Vector3f32 position) { m_pOwner->transform.SetLocalPosition(position); }
	void Rotate(gce::Vector3f32 rotation) { m_pOwner->transform.SetLocalRotation(rotation); }
	void Scale(gce::Vector3f32 scale) { m_pOwner->transform.SetLocalScale(scale); }

END_SCRIPT