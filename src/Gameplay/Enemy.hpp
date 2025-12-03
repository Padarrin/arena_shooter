#pragma once
#include "Agent.hpp"

DECLARE_SCRIPT(ScriptEnemy, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

ScriptAgent* mAgent;

virtual void Start() { mAgent = m_pOwner->AddScript <ScriptAgent>(); }
virtual void Update() {}
virtual void Destroy() {}

virtual void CollisionEnter() {}
virtual void CollisionStay() {}
virtual void CollisionExit() {}

END_SCRIPT
