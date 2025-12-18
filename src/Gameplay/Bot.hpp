#pragma once
//#include "../Testing/TestGame.hpp"
#include "Agent.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Time.h"

DECLARE_SCRIPT(ScriptBot, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    Time mTimeCreate;
    ScriptPlayer* mPlayer;
public:
    ScriptAgent* mAgent;

    virtual void Initia() { mAgent = m_pOwner->AddScript<ScriptAgent>(); mAgent->Initia(); mTimeCreate = Time(1.f); }
    virtual void Start() {}
    virtual void Update()
    {
        float deltaTime = gce::GameManager::GameDeltaTime();
        if (deltaTime > 0.f)
        {
			mTimeCreate.Update(deltaTime);
			if (mTimeCreate.IsFinish())
			{
			    mTimeCreate.Reset();
			    gce::Vector3f32 posNail = gce::Vector3f32(5.f, 0.f, 5.f);
			    CreateNail(*mAgent->mCharacter->mEntity->GetScene(), mPlayer, mAgent->GetPathFinding()->GetGrid(), posNail, RES_PATH"res/Gameplay/Obj/clou.obj");
			}
        }
    }
    virtual void Destroy() {}

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

	static void CreateNail(gce::Scene& scene,/*gce::GameObject& enemyObject,*/ ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos, const std::string_view path)
	{
		//Life = 20 a 200, Damage = 1 a 5
		Geometry* geo = GeometryFactory::LoadGeometry(path);
		gce::GameObject& enemyObject = CreateGameObject<ScriptEnemy>(scene, geo, gce::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		enemyObject.SetName("Enemy");

		SetNail(&enemyObject, player, grid, pos);

	}

	static void SetNail(gce::GameObject* enemyObject, ScriptPlayer* player, ScriptGrid* grid, gce::Vector3f32 pos)
	{
		//Life = 20 a 200, Damage = 1 a 5
		enemyObject->AddComponent<gce::BoxCollider>()->SetActive(true);
		enemyObject->AddComponent<gce::PhysicComponent>()->SetActive(false);

		ScriptEnemy* enemy = nullptr;
		if (enemyObject->HasScript<ScriptEnemy>())
		{
			enemy = enemyObject->GetScript<ScriptEnemy>();
		}
		else
		{
			enemy = enemyObject->AddScript<ScriptEnemy>();
		}
		enemy->SetPlayer(player);
		enemy->SetMaxLife(20);
		enemy->SetDamage(2);
		enemy->mAgent->mCharacter->SetSpeed(5.f);
		enemy->mAgent->GetPathFinding()->SetGrid(grid);
		enemy->SetCellTarget(grid->GetNearestCell(player->GetWorldPosition()));
		enemy->mAgent->SetOffsetOfGrid(gce::Vector3f32(pos.x, enemy->mAgent->mCharacter->mEntity->GetGameObject()->transform.GetWorldScale().y * 0.5f, pos.z));
	}

    void SetPlayer(ScriptPlayer* player) { mPlayer = player; }
    ScriptPlayer* GetPlayer() { return mPlayer; }

    END_SCRIPT