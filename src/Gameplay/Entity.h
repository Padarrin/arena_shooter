#pragma once
#include "GameObject.h"

DECLARE_SCRIPT(ScriptEntity, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
	
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	virtual void CollisionEnter();
	virtual void CollisionStay();
	virtual void CollisionExit();

	void Translate(gce::Vector3f32 position);
	void Rotate(gce::Vector3f32 rotation);
	void Scale(gce::Vector3f32 rotation);

END_SCRIPT