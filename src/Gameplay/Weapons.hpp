#pragma once
#include "Entity.hpp"
#include "PistolMagazine.hpp"
//#include "Player.hpp"
#include "Ball.hpp"


DECLARE_SCRIPT(ScriptWeapons, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    float mShootSpeed;

    int mTypeBullet;

public:
    ScriptEntity* mEntity;
    ScriptPistolMagazine* mMagazine;

    virtual void Initia() { mEntity = m_pOwner->AddScript<ScriptEntity>(); mEntity->Initia(); mMagazine = m_pOwner->AddScript<ScriptPistolMagazine>(); mMagazine->Initia(); mEntity->SetLocalPosition(gce::Vector3f32(0.f, 0.f, 0.f)); }
    virtual void Start() { mEntity->Start(); mMagazine->Start(); }
    virtual void Update() {}
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    template<typename T>
    static void ShootBall(cstr name, ScriptWeapons* weapons, float speed, int damage)
    {
        ScriptEntity* myParentEntity = weapons->mEntity;
        CreateBallInFront<T>(name, speed, damage, gce::SHAPES.CUBE, myParentEntity);
    }

    template<typename T>
    static void CreateBallInFront(cstr name, float speed, int damage, gce::Geometry* geometry, ScriptEntity* entityGiveInformation)
    {
        gce::Quaternion rot = entityGiveInformation->GetWorldRotate();
        T* ball = T::CreateBall(name, entityGiveInformation->GetWorldPosition() + entityGiveInformation->GetWorldForward(), entityGiveInformation->GetWorldForward(), speed, damage, *entityGiveInformation->GetScene(), geometry);
        ball->mShootable->mObject->mEntity->SetWorldRotate(gce::Vector3f32(rot.GetX(), rot.GetY(), rot.GetZ()));
    }

    template<typename T>
    T* GetChildWeapon() { return mEntity->GetGameObject()->GetScript<T>(); }


END_SCRIPT