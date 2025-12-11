#pragma once
#include "../Engine/GameManager.h"
#include "Character.hpp"
#include "SubMachineGun.hpp"

enum WEAPON_ORDER
{
	ANGLEGRINGER,
	SUBMACHINEGUN,
	BAZOOKA,

	count,
};

#define PI  3.14159265359f

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::Window* mWindow;

		float mJump;
		float mYaw;
		float mPitch;

		bool mIsJumping;
		bool isWindowInitialised; 
		bool isCursorLocked;

		ScriptWeapons* mCurrentWeapon;

		std::vector<ScriptWeapons*> mAllWeapons;

	public:
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); mJump = 6.f; mCharacter->SetMaxLife(100); mCharacter->SetDamage(5); mYaw = 0.f; mPitch = 0.f; isWindowInitialised = false; isCursorLocked = true; }
		virtual void Start() 
		{ 
			mWindow = gce::GameManager::GetWindow(); 
			mIsJumping = true;
		}

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			gce::HideMouseCursor();

			InputMove(deltaTime);
			InputShoot(deltaTime);
			TurnCamera();

			if (mCharacter->GetLife() <= 0)
				mCharacter->mEntity->DestroyEntity();
		}

		virtual void Destroy() {}

		virtual void CollisionEnter(gce::GameObject* other) 
		{ 
			if (other->GetName() == "Floor")
				ColliderFloor();
		}
		virtual void CollisionStay(gce::GameObject* other) {}
		virtual void CollisionExit(gce::GameObject* other) {}
		
		void InputMove(float deltaTime)
		{
			float horizontalInput = gce::GetKey(gce::Keyboard::Key::D) - gce::GetKey(gce::Keyboard::Key::Q);
			float verticalInput = gce::GetKey(gce::Keyboard::Key::Z) - gce::GetKey(gce::Keyboard::Key::S);

			gce::Vector3f32 direction = m_pOwner->transform.GetWorldRight() * horizontalInput + m_pOwner->transform.GetWorldForward() * verticalInput;

			//SetWorldPosition(GetWorldPosition() + direction * mCharacter->GetSpeed() * deltaTime);
			WorldTranslate(direction * mCharacter->GetSpeed() * deltaTime);

			if (gce::GetKeyDown(gce::Keyboard::Key::SPACE))
			{
				Jump(mJump, deltaTime);
			}

			if(gce::GetButtonDown( gce::Mouse::Button::LEFT))
				mCurrentWeapon->CreateBallInFront<ScriptBall>("PlayerBall", 50.f, DEFAULT_BALL_DAMAGE, gce::SHAPES.CUBE, mCharacter->mEntity);
		}

		void InputShoot(float deltaTime)
		{
			bool actionOnWeapon = gce::GetButton(gce::Mouse::LEFT);
			if (actionOnWeapon)
			{
				if (mCurrentWeapon != nullptr)
				{
					ScriptSubMachineGun* weapon = mCurrentWeapon->GetChildWeapon<ScriptSubMachineGun>();
					weapon->Action();
				}
			}
		}

		void TurnCamera()
		{
			const float sensitivity = 0.001f;

			const int centerHeight = (int)(gce::GameManager::GetWindowParam().height * 0.5f);
			const int centerWidth = (int)(gce::GameManager::GetWindowParam().width * 0.5f);

			const float degToRad = PI / 180.0f;

			// limites en radians
			const float pitchMin = -89.0f * degToRad;
			const float pitchMax = 89.0f * degToRad;

			if (gce::GetKeyDown(gce::Keyboard::LSHIFT)) {
				isCursorLocked = !isCursorLocked;
				gce::ShowMouseCursor();
			}

			if (isWindowInitialised == false)
			{
				gce::HideMouseCursor();
				gce::SetMousePosition(gce::Vector2i32(centerWidth, centerHeight));
				isWindowInitialised = true;
			}

			if (!isCursorLocked)
				return;

			gce::HideMouseCursor();

			gce::Vector2i32 currentMousePos = gce::GetMousePosition();

			gce::Vector2i32 delta;
			delta.x = currentMousePos.x - centerWidth;
			delta.y = currentMousePos.y - centerHeight;

			// Rotation
			mYaw += delta.x * sensitivity;
			mPitch += delta.y * sensitivity;

			mPitch = gce::Clamp(mPitch, pitchMin, pitchMax);

			m_pOwner->transform.SetWorldRotation(gce::Vector3f32(mPitch, mYaw, 0.f));

			m_pOwner->GetChildren()[0]->transform.SetLocalRotation(gce::Vector3f32(mPitch, 0.f, 0.f));

			gce::SetMousePosition(gce::Vector2i32(centerWidth, centerHeight));

		}

		void Jump(float strength, float deltaTime)
		{
			if (mIsJumping == false)
			{
				gce::PhysicComponent* physique = m_pOwner->GetComponent<gce::PhysicComponent>();
				gce::Vector3f32 velocity = physique->GetVelocity();
				velocity.y = strength;
				physique->SetVelocity(velocity);
				mIsJumping = true;
			}
		}

		void ColliderFloor()
		{
			//Regarde si il est dans les airs pour qu'il puisse saute
			gce::PhysicComponent* physique = m_pOwner->GetComponent<gce::PhysicComponent>();
			gce::Vector3f32 velocity = physique->GetVelocity();
			velocity.y = 0.f;
			physique->SetVelocity(velocity);
			mIsJumping = false;
		}

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

		void SetJump(float jump) { mJump = jump; }
		float GetJump() { return mJump; }

		void SetIsJumping(bool isJumping) { mIsJumping = isJumping; }
		bool GetIsJumping() { return mIsJumping; }

		void SetCurrentWeapon(WEAPON_ORDER tag) { mCurrentWeapon = mAllWeapons[tag]; }
		ScriptWeapons* GetCurrentWeapon() { return mCurrentWeapon; }

		void AddWeapon(ScriptWeapons* currentWeapon) { mAllWeapons.push_back(currentWeapon); }
		std::vector<ScriptWeapons*>* GetAllWeapons() { return &mAllWeapons; }

END_SCRIPT