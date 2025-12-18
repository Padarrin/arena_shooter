#pragma once
#include "Weapons.hpp"

DECLARE_SCRIPT(ScriptAngleGringer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
    ScriptWeapons* mWeapons;

    virtual void Initia() { mWeapons = m_pOwner->AddScript<ScriptWeapons>(); mWeapons->Initia(); mWeapons->mMagazine->SetShootTime(0.1f); mWeapons->mMagazine->SetReloadTime(0.5f); }
    virtual void Start() {}
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter(gce::GameObject* other) {}
    virtual void CollisionStay(gce::GameObject* other) {}
    virtual void CollisionExit(gce::GameObject* other) {}

    void Action(ScriptCharacter* other)
    {
        if (GetPistolMagazine()->IsEmpty() == true)
        {
            GetPistolMagazine()->CanReload();
        }
        else
        {
            bool isExecute = GetPistolMagazine()->CanShoot();
            //si une ball a été utiliser
            if (isExecute)
            {
                //attaque
                other->Damage(5);
            }
            
        }
    }

    ScriptPistolMagazine* GetPistolMagazine()
    {
        return mWeapons->mMagazine;
    }


END_SCRIPT