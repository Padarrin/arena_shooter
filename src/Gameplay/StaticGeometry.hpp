#pragma once
#include "Entity.hpp"

DECLARE_SCRIPT(ScriptStaticGeometry, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    bool mIsFix;
    bool mIsObtacle;
    ScriptGrid* mGrid;

    bool mUpdateInacessibleCell;
public:
    ScriptEntity* mEntity;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); SetAll(nullptr, true, true);}
    virtual void Start() 
    {
        if (mIsObtacle && mGrid != nullptr)
        {
            SetInacessibleCell();
        }
    }
    virtual void Update() 
    {
        if (mUpdateInacessibleCell)
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
        mGrid->SetAllInacessibleInRectWithPos(gce::Vector2f32(pos.x, pos.y), gce::Vector2f32(scale.x, scale.z), mIsFix);
    }

    void SetAll(ScriptGrid* grid, bool isFix, bool isObtacle) { mGrid = grid; mIsFix = isFix; mIsObtacle = isObtacle; RecalculeUpdateInacessibleCell(); }

    void SetGrid(ScriptGrid* grid) { mGrid = grid; RecalculeUpdateInacessibleCell(); }
    ScriptGrid* GetGrid() { return mGrid; }

    void SetIsFix(bool isFix) { mIsFix = isFix; RecalculeUpdateInacessibleCell(); }
    bool GetIsFix() { return mIsFix; }

    void SetIsObtacle(bool isObtacle) { mIsObtacle = isObtacle; RecalculeUpdateInacessibleCell(); }
    bool GetIsObtacle() { return mIsObtacle; }

    void RecalculeUpdateInacessibleCell() { mUpdateInacessibleCell = mIsObtacle && !mIsFix && mGrid != nullptr; }

    END_SCRIPT

