//remplace 'X' par Le nom de la classe et 'Y' par le nom de son parent
/*
#pragma once
#include "Y.hpp"

DECLARE_SCRIPT(ScriptX, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
ScriptY* mY;

virtual void Start() { mY = m_pOwner->AddScript<ScriptY>(); mY->Start();}
virtual void Update() {}
virtual void Destroy() {}

virtual void CollisionEnter() {}
virtual void CollisionStay() {}
virtual void CollisionExit() {}

END_SCRIPT

*/
