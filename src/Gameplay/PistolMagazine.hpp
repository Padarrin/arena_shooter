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

    virtual void Initia() { mCurrentBullets = mMaxBullets; mIsNotEmpty = true; mShootTime = Time(1.f); mReloadTime = Time(1.f); }
    virtual void Start() {}
    virtual void Update() 
    {
        IsEmpty();
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void Action()
    {
        if (mShootTime.IsFinish())
        {
            if (Shoot() == true)
            {
                return;
            }
        }

        if(mIsNotEmpty == false && mReloadTime.IsFinish())
        {
            Reload();
        }
    }

    bool Shoot()
    {
        if (mIsNotEmpty == true)
        {
            mCurrentBullets--;
            mShootTime.Reset();
            return true;
        }
        return false;
    }

    void Reload()
    {
        SetCurrentBullets(GetMaxBullets());
        mIsNotEmpty = true;
        mReloadTime.Reset();
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
    void SetCurrentBullets(int diff) { mCurrentBullets += diff; }

END_SCRIPT