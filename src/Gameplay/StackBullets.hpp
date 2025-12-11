#pragma once
#include "Item.hpp"

DECLARE_SCRIPT(ScriptstackBullets, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
    ScriptItem* mItem;

    virtual void Initia() { mItem = m_pOwner->AddScript<ScriptItem>(); mItem->Initia(); mItem->SetTurnSpeed(2.f); }
    virtual void Start() { mItem->Start(); }
    virtual void Update() 
    {
        
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

END_SCRIPT