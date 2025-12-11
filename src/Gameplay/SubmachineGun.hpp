#pragma once
#include "Weapons.hpp"

DECLARE_SCRIPT(ScriptSubMachineGun, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:

public:
    ScriptWeapons* mWeapons;

    virtual void Initia() { mWeapons = m_pOwner->AddScript<ScriptWeapons>(); mWeapons->Initia(); mWeapons->mMagazine->SetShootTime(0.5f); mWeapons->mMagazine->SetReloadTime(2.5f); }
    virtual void Start() {}
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void Action()
    {
        if (ShootScriptBall(100.f, DEFAULT_BALL_DAMAGE) == false)
        {
            if (ReloadPistolMagazine() == false)
            {
                //rien ou autre action
            }
        }
    }

    bool ShootScriptBall(int speed, int damage)
    {
        if (GetPistolMagazine()->IsEmpty() == false)
        {
            //pas vide
            bool isExecute = GetPistolMagazine()->CanShoot();
            //si une ball a été utiliser
            if (isExecute)
            {
                //tirer une ball
                ScriptWeapons::ShootBall<ScriptBall>("PlayerBall", mWeapons, speed, damage);
                return true;
            }
        }
        return false;
    }

    bool ReloadPistolMagazine()
    {
        if (GetPistolMagazine()->IsEmpty() == true)
        {
            GetPistolMagazine()->CanReload();
            return true;
        }
        return false;
    }

    ScriptPistolMagazine* GetPistolMagazine()
    {
        return mWeapons->mMagazine;
    }

    END_SCRIPT