#pragma once
#include "../Engine/GameManager.h"
#include "Character.hpp"
#include "SubMachineGun.hpp"
#include "Menu.hpp"

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
		gce::GameObject* mMenu;

		float mJump;
		float mYaw;
		float mPitch;

		bool mIsJumping;
		bool mIsCursorLocked;

		ScriptWeapons* mCurrentWeapon;
		std::vector<ScriptWeapons*> mAllWeapons;

	public:
		
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); mJump = 6.f; mCharacter->SetMaxLife(10000); mCharacter->SetDamage(5); mYaw = 0.f; mPitch = 0.f; mIsCursorLocked = true; mCurrentWeapon = nullptr; mObjectCamera = nullptr; mAllWeapons = std::vector<ScriptWeapons*>(); mMenu = nullptr; }
		virtual void Start() 
		{ 
			mWindow = gce::GameManager::GetWindow(); 
			mIsJumping = true;

			if (mCurrentWeapon != nullptr)
			{
				gce::Vector3f32 posPlayer = GetWorldPosition();
				mCurrentWeapon->mEntity->SetWorldPosition(gce::Vector3f32(posPlayer.x + 2.f, posPlayer.y + 0.5f, posPlayer.z + 3.f));
			}
		}

		virtual void Update()
		{ 
			//std::cout << "xP : " << GetWorldPosition().x << std::endl;
			//std::cout << "zP : " << GetWorldPosition().z << std::endl;
			float deltaTime = gce::GameManager::GameDeltaTime();

			if (deltaTime > 0.f)
			{
				if (mCurrentWeapon != nullptr)
				{
					gce::HideMouseCursor();
					InputMove(deltaTime);
					InputShoot(deltaTime);
					TurnCamera();
				}

				mCharacter->Damage(1);
				if (mCharacter->GetLife() <= 0)
				{
					mMenu->GetScript<ScriptMenu>()->ShowMenu(LOSE_MENU);
					mCharacter->mEntity->DestroyEntity();
				}
				

			}
			else
			{
				gce::ShowMouseCursor();
			}
			
				
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
			gce::WindowParam param = gce::GameManager::GetWindowParam();
			gce::Vector2i32 centerSizeWindow = gce::Vector2i32((int)(param.width * 0.5f), (int)(param.height * 0.5f));

			if (gce::GetKeyDown(gce::Keyboard::LSHIFT)) {
				mIsCursorLocked = !mIsCursorLocked;
				gce::ShowMouseCursor();
			}

			if (!mIsCursorLocked)
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
		void SetMenu(gce::GameObject* menuObject) { mMenu = menuObject; }
		gce::GameObject* GetMenu() { return mMenu; }

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