#pragma once
#include "../Engine/GameObject.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void Translate(gce::Vector3f32 position)
	{
		m_pOwner->transform.WorldTranslate(position);
	}
	void Rotate(gce::Vector3f32 rotation)
	{
		m_pOwner->transform.WorldRotate(rotation);
	}
	void Scale(gce::Vector3f32 scale)
	{
		m_pOwner->transform.WorldScale(scale);
	}

END_SCRIPT