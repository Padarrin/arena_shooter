#pragma once
#include <GameObject.h>
#include "Functions.h"
#include "Time.h"

DECLARE_SCRIPT(ScriptPistolMagazine, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    bool mIsNotEmpty;
    bool mIsReloading;

    Time mShootTime;
    Time mReloadTime;

    int mMaxBullets;
    int mCurrentBullets;


public:

    virtual void Initia() { mMaxBullets = 1; mCurrentBullets = mMaxBullets; mIsNotEmpty = true; mShootTime = Time(1.f); mReloadTime = Time(1.f); }
    virtual void Start() {}
    virtual void Update() 
    {
        IsEmpty();

        float deltatime = gce::GameManager::GameDeltaTime();
        mShootTime.Update(deltatime);
        mReloadTime.Update(deltatime);

        if (mReloadTime.GetIsFinishNow())
        {
            PutMaxCurrentBullets();
            mIsNotEmpty = true;
        }
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    bool CanShoot()
    {
        if (mIsNotEmpty == true && mShootTime.IsFinish())
        {
            mCurrentBullets--;
            mShootTime.Reset();
            return true;
        }
        return false;
    }

    void CanReload()
    {
        if (mIsNotEmpty == false && mReloadTime.IsFinish())
        {
            mReloadTime.Reset();
        }
    }

    bool IsEmpty()
    {
        if (mCurrentBullets < 1)
        {
            mIsNotEmpty = false;
            return true;
        }
        return false;
    }

    void SetShootTime(float shootTime) { mShootTime = shootTime; }
    float GetShootCurrenteTime() { return mShootTime.GetCurrenteTime(); }
    Time* GetShootTime() { return &mShootTime; }

    void SetReloadTime(float reloadTime) { mReloadTime = reloadTime; }
    float GetReloadCurrenteTime() { return mReloadTime.GetCurrenteTime(); }
    Time* GetReloadTime() { return &mReloadTime; }

    void SetMaxBullets(int max) { mMaxBullets = max; }
    int GetMaxBullets() { return mMaxBullets; }

    int GetCurrentBullets() { return mCurrentBullets; }
    void PutMaxCurrentBullets() { mCurrentBullets = mMaxBullets; }
    void SetCurrentBullets(int diff) { mCurrentBullets += diff; }

END_SCRIPT