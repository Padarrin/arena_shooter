#pragma once
#include "Entity.hpp"
#include "PistolMagazine.hpp"

DECLARE_SCRIPT(ScriptWeapons, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    float mShootSpeed;

    int mTypeBullet;

public:
    ScriptEntity* mEntity;
    ScriptPistolMagazine* mPMagazine;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); mPMagazine = m_pOwner->AddScript<ScriptPistolMagazine>(); mPMagazine->Initia(); }
    virtual void Start() { mEntity->Start(); }
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

END_SCRIPT