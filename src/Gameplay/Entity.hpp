#pragma once
#include <GameObject.h>
#include "Functions.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:

public:
	virtual void Initia()
	{
		SetWorldPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		SetWorldRotate(gce::Vector3f32(0.f, 0.f, 0.f));
		SetWorldScale(gce::Vector3f32(1.f, 1.f, 1.f));

		SetLocalPosition(gce::Vector3f32(0.f, 0.f, 0.f));
		SetLocalRotate(gce::Vector3f32(0.f, 0.f, 0.f));
		SetLocalScale(gce::Vector3f32(1.f, 1.f, 1.f));
	}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}

	static void FocusEntity(ScriptEntity* entityGiveInformation, ScriptEntity* entityTarget)
	{
		gce::Vector3f32 dir = entityTarget->GetGameObject()->transform.GetWorldPosition() - entityGiveInformation->GetGameObject()->transform.GetWorldPosition();
		dir = dir.Normalize();
		entityGiveInformation->SetWorldRotate(gce::Vector3f32(-asin(dir.y), atan2(dir.x, dir.z), 0.f));
	}


	void SetWorldPosition(gce::Vector3f32 position) { m_pOwner->transform.SetWorldPosition(position); }
	void SetWorldRotate(gce::Vector3f32 rotation) { m_pOwner->transform.SetWorldRotation(rotation); }
	void SetWorldScale(gce::Vector3f32 scale) { m_pOwner->transform.SetWorldScale(scale); }
	gce::Vector3f32 GetWorldPosition() { return m_pOwner->transform.GetWorldPosition(); }
	gce::Quaternion GetWorldRotate() { return m_pOwner->transform.GetWorldRotation(); }
	gce::Vector3f32 GetWorldScale() { return m_pOwner->transform.GetWorldScale(); }
	void WorldTranslate(gce::Vector3f32 position) { m_pOwner->transform.WorldTranslate(position); }
	void WorldRotate(gce::Vector3f32 rotation) { m_pOwner->transform.WorldRotate(rotation); }
	void WorldScale(gce::Vector3f32 scale) { m_pOwner->transform.WorldScale(scale); }


	void SetLocalPosition(gce::Vector3f32 position) { m_pOwner->transform.SetLocalPosition(position); }
	void SetLocalRotate(gce::Vector3f32 rotation) { m_pOwner->transform.SetLocalRotation(rotation); }
	void SetLocalScale(gce::Vector3f32 scale) { m_pOwner->transform.SetLocalScale(scale); }
	gce::Vector3f32 GetLocalPosition() { return m_pOwner->transform.GetLocalPosition(); }
	gce::Quaternion GetLocalRotate() { return m_pOwner->transform.GetLocalRotation(); }
	gce::Vector3f32 GetLocalScale() { return m_pOwner->transform.GetLocalScale(); }
	void LocalTranslate(gce::Vector3f32 position) { m_pOwner->transform.LocalTranslate(position); }
	void LocalRotate(gce::Vector3f32 rotation) { m_pOwner->transform.LocalRotate(rotation); }
	void LocalScale(gce::Vector3f32 scale) { m_pOwner->transform.LocalScale(scale); }

	gce::Vector3f32 GetWorldForward() { return m_pOwner->transform.GetWorldForward(); }

	gce::GameObject* GetGameObject() { return m_pOwner; }
	gce::Scene* GetScene() { return m_pOwner->m_pScene; }

END_SCRIPT