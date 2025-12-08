#pragma once
#include "Weapons.hpp"

DECLARE_SCRIPT(ScriptSubMachineGun, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    float mShootSpeed = 0.5f;
    float mReloadTime = 2.5f;
    float mTimer = mReloadTime;

public:
    ScriptWeapons* mWeapons;

    virtual void Initia() { mWeapons = m_pOwner->AddScript<ScriptWeapons>(); mWeapons->Initia(); }
    virtual void Start() { mWeapons->Start(); }
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void Reload()
    {
        // faut reload
    }

    void Shoot()
    {
        if (mWeapons->mPMagazine->GetCurrentBullets() == 0)
        {
            Reload();
            return;
        }

        mWeapons->mPMagazine->SetCurrentBullets(-1);
    }

    END_SCRIPT