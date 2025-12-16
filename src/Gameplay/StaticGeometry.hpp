#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptStaticGeometry, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    bool mIsFix;
    ScriptGrid* mGrid;
public:
    ScriptEntity* mEntity;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); SetIsFix(true); }
    virtual void Start() 
    { 
        if (mIsFix && mGrid != nullptr)
        {
            SetInacessibleCell();
        }
    }
    virtual void Update() 
    {
        if (!mIsFix && mGrid != nullptr)
        {
            SetInacessibleCell();
        }
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    void SetInacessibleCell()
    {
        gce::Vector3f32 pos = mEntity->GetWorldPosition();
        gce::Vector3f32 scale = mEntity->GetWorldScale();
        mGrid->SetAllInacessibleInRect(gce::Vector2f32(pos.x, pos.y), gce::Vector2f32(scale.x, scale.z), mIsFix);
    }

    void SetGrid(ScriptGrid* grid) { mGrid = grid; }
    ScriptGrid* GetGrid() { return mGrid; }

    void SetIsFix(bool isFix) { mIsFix = isFix; }
    bool GetIsFix() { return mIsFix; }

    END_SCRIPT

