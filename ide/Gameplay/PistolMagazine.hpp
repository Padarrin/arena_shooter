#pragma once
#include <GameObject.h>
#include "Functions.h"

DECLARE_SCRIPT(ScriptPistolMagazine, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    bool isFull;
    bool isReloading;

    int mMaxBullets;
    int mCurrentBullets;


public:

    virtual void Initia() { mCurrentBullets = mMaxBullets; isFull = true; }
    virtual void Start() {}
    virtual void Update() 
    {
        if (mCurrentBullets == 0)
        {
            isFull = false;
        }
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void SetMaxBullets(int max)
    {
        mMaxBullets = max;
    }
    int GetMaxBullets()
    {
        return mMaxBullets;
    }

    int GetCurrentBullets()
    {
        return mCurrentBullets;
    }
    void SetCurrentBullets(int diff)
    {
        mCurrentBullets += diff;
    }

END_SCRIPT