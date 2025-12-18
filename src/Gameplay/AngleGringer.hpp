#pragma once
#include "Weapons.hpp"

DECLARE_SCRIPT(ScriptAngleGringer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
    ScriptWeapons* mWeapons;

    virtual void Initia() { mWeapons = m_pOwner->AddScript<ScriptWeapons>(); mWeapons->Initia(); }
    virtual void Start() {}
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter(gce::GameObject* other) 
    {
        if (other->GetName() == "Enemy")
            Action(other);
    }
    virtual void CollisionStay(gce::GameObject* other) {}
    virtual void CollisionExit(gce::GameObject* other) {}

    void Action(gce::GameObject* other)
    {
        other->GetScript<ScriptCharacter>()->Damage(5);
    }

END_SCRIPT