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
#define SENSITIVITY_CAMERA 0.001f

#define DEGREE_TO_RADIAN PI / 180.0f
#define PITCH 89.0f * DEGREE_TO_RADIAN

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
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
			mYaw = 0.f; mPitch = 0.f;
		}

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			gce::HideMouseCursor();

			if (deltaTime > 0.f)
			{
				InputMove(deltaTime);
				InputShoot(deltaTime);
				TurnCamera();
			}

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

			WorldTranslate(direction * mCharacter->GetSpeed() * deltaTime);

			if (gce::GetKeyDown(gce::Keyboard::Key::SPACE))
			{
				Jump(mJump, deltaTime);
			}
			//mObjectCamera->transform.SetWorldPosition(GetWorldPosition());
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
			/*if (mObjectCamera == nullptr)
				return;

			uint32 width = mWindow->GetWidth();
			uint32 height = mWindow->GetHeight();
			float degree = 360.f / ((gce::Sqrt(width * width + height * height) * 100.f));

			mObjectCamera->transform.SetLocalRotation(gce::Vector3f32((float)gce::GetMousePosition().y * degree, 0.f, 0.f));
			m_pOwner->transform.SetWorldRotation(gce::Vector3f32(0.f, (float)gce::GetMousePosition().x * degree, 0.f));
			*/
			gce::WindowParam param = gce::GameManager::GetWindowParam();
			gce::Vector2i32 centerSizeWindow = gce::Vector2i32((int)(param.height * 0.5f), (int)(param.width * 0.5f));

			if (gce::GetKeyDown(gce::Keyboard::LSHIFT)) {
				isCursorLocked = !isCursorLocked;
				gce::ShowMouseCursor();
			}

			if (isWindowInitialised == false)
			{
				//gce::HideMouseCursor();
				gce::SetMousePosition(centerSizeWindow);
				isWindowInitialised = true;
			}

			if (!isCursorLocked)
				return;

			gce::HideMouseCursor();

			gce::Vector2i32 delta = gce::GetMousePosition() - centerSizeWindow;

			// Rotation
			mYaw += delta.x * SENSITIVITY_CAMERA;
			mPitch += delta.y * SENSITIVITY_CAMERA;

			mPitch = gce::Clamp(mPitch, -PITCH, PITCH);
			m_pOwner->transform.SetWorldRotation(gce::Vector3f32(mPitch, mYaw, 0.f));
			mObjectCamera->transform.SetLocalRotation(gce::Vector3f32(mPitch, 0.f, 0.f));
			gce::SetMousePosition(centerSizeWindow);
			
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

		void SetCamera(gce::GameObject* cameraObject) { mObjectCamera = cameraObject; }

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