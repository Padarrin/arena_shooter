#pragma once
#include "../Engine/GameObject.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void SetPosition(gce::Vector3f32 position) { m_pOwner->transform.SetWorldPosition(position); }
	void SetRotate(gce::Vector3f32 rotation) { m_pOwner->transform.SetWorldRotation(rotation); }
	void SetScale(gce::Vector3f32 scale) { m_pOwner->transform.SetWorldScale(scale); }

	void WorldTranslate(gce::Vector3f32 position) { m_pOwner->transform.WorldTranslate(position); }
	void WorldRotate(gce::Vector3f32 rotation) { m_pOwner->transform.WorldRotate(rotation); }
	void WorldScale(gce::Vector3f32 scale) { m_pOwner->transform.WorldScale(scale); }

	void LocalTranslate(gce::Vector3f32 position) { m_pOwner->transform.LocalTranslate(position); }
	void LocalRotate(gce::Vector3f32 rotation) { m_pOwner->transform.LocalRotate(rotation); }
	void LocalScale(gce::Vector3f32 scale) { m_pOwner->transform.LocalScale(scale); }

END_SCRIPT