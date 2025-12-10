#pragma once
#include "Entity.hpp"
#include "PistolMagazine.hpp"
#include "Player.hpp"
#include "Ball.hpp"

DECLARE_SCRIPT(ScriptWeapons, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    float mShootSpeed;

    int mTypeBullet;

    ScriptPlayer* mPlayer;

public:
    ScriptEntity* mEntity;
    ScriptPistolMagazine* mMagazine;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); mMagazine = m_pOwner->AddScript<ScriptPistolMagazine>(); mMagazine->Initia(); }
    virtual void Start() { mEntity->Start(); mMagazine->Start(); }
    virtual void Update() 
    {
        mEntity->SetWorldPosition(mPlayer->GetWorldPosition());
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    static void ShootBall(ScriptWeapons* weapons)
    {
        ScriptEntity* myParentEntity = weapons->mEntity;
        CreateBallInFront<ScriptBall>(100.f, DEFAULT_BALL_DAMAGE, gce::SHAPES.CUBE, myParentEntity);
    }

    template<typename T>
    static void CreateBallInFront(float speed, int damage, gce::Geometry* geometry, ScriptEntity* entityGiveInformation)
    {
        gce::Quaternion rot = entityGiveInformation->GetWorldRotate();
        T* ball = T::CreateBall(entityGiveInformation->GetWorldPosition() + entityGiveInformation->GetWorldForward(), entityGiveInformation->GetWorldForward(), speed, damage, *entityGiveInformation->GetScene(), geometry);
        ball->mShootable->mObject->mEntity->SetWorldRotate(gce::Vector3f32(rot.GetX(), rot.GetY(), rot.GetZ()));
    }

    void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
    ScriptPlayer* GetPlayer() { return mPlayer; }

END_SCRIPT