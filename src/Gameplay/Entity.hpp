#pragma once
#include <GameObject.h>
#include "Functions.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	gce::Vector3f32 GetWorldPosition()
	{
		return m_pOwner->transform.GetWorldPosition();
	}

	void SetWorldPosition(gce::Vector3f32 position)
	{
		m_pOwner->transform.SetWorldPosition(position);
	}

	void Translate(gce::Vector3f32 position)
	{
		m_pOwner->transform.WorldTranslate(position);
	}
	void Rotate(gce::Vector3f32 rotation)
	{
		
	}
	void Scale(gce::Vector3f32 rotation)
	{

	}

END_SCRIPT