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
    virtual void Update() 
    {
        float deltatime = gce::GameManager::DeltaTime();
        
        mWeapons->Update();

        InputShoot(deltatime);
        
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void Reload()
    {
        // faut reload mdrrrrrrrrr
        mWeapons->mPMagazine->SetCurrentBullets(mWeapons->mPMagazine->GetMaxBullets());
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

    void InputShoot(float deltatime)
    {
        float horizontalInput = gce::GetKey(gce::Keyboard::Key::D) - gce::GetKey(gce::Keyboard::Key::Q);
        float verticalInput = gce::GetKey(gce::Keyboard::Key::Z) - gce::GetKey(gce::Keyboard::Key::S);

        gce::Vector3f32 direction = m_pOwner->transform.GetWorldRight() * horizontalInput + m_pOwner->transform.GetWorldForward() * verticalInput;

        mWeapons->mEntity->SetWorldPosition(mWeapons->mEntity->GetWorldPosition() + direction * mShootSpeed * deltatime);
    }

    END_SCRIPT