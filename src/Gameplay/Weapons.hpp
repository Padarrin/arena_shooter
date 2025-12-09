#pragma once
#include "Entity.hpp"
#include "PistolMagazine.hpp"
#include "Player.hpp"

DECLARE_SCRIPT(ScriptWeapons, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    float mShootSpeed;

    int mTypeBullet;

    ScriptPlayer* mPlayer;

public:
    ScriptEntity* mEntity;
    ScriptPistolMagazine* mPMagazine;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); mPMagazine = m_pOwner->AddScript<ScriptPistolMagazine>(); mPMagazine->Initia(); }
    virtual void Start() { mEntity->Start(); mPMagazine->Start(); }
    virtual void Update() 
    {
        mEntity->SetWorldPosition(mPlayer->GetWorldPosition());
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
    ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT