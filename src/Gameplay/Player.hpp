#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

		gce::Vector3f32 mVelocity;
		float mGravity;
		float mJump;

		bool mIsJumping;

	public:
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); mVelocity = gce::Vector3f32(0.f, 0.f, 0.f); mGravity = 9.81f; mJump = 6.f; }
		virtual void Start() { mCharacter->Start(); mWindow = gce::GameManager::GetWindow(); mIsJumping = true; }

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			InputMove(deltaTime);
			Gravity(deltaTime);

			TurnCamera();


			std::cout << GetWorldPosition().x << "; " << GetWorldPosition().y << "; " << GetWorldPosition().z << std::endl;
		}

		virtual void Destroy() {}

		virtual void CollisionEnter(gce::GameObject* other) 
		{ 
			mCharacter->CollisionEnter(other);
			//Regarde si il est dans les airs pour qu'il puisse saute 
			WorldTranslate({ 0.f, -mVelocity.y , 0.f });
			mVelocity.y = 0.f;
			mIsJumping = false;
		}
		virtual void CollisionStay(GameObject* other) 
		{ 
			mCharacter->CollisionStay(other);
		}
		virtual void CollisionExit(GameObject* other) 
		{ 
			mCharacter->CollisionExit(other);
		}
		
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
		}

		void TurnCamera()
		{
			if (mObjectCamera == nullptr)
				return;

			uint32 width = mWindow->GetWidth();
			uint32 height = mWindow->GetHeight();
			float degree = 360.f / ((gce::Sqrt(width * width + height * height) * 100.f));

			mObjectCamera->transform.SetLocalRotation({ (float)gce::GetMousePosition().y * degree, 0.f, 0.f });
			m_pOwner->transform.SetWorldRotation({ 0.f,(float)gce::GetMousePosition().x * degree ,0.f });
		}

		void SetCamera(gce::GameObject& cameraObject) { mObjectCamera = &cameraObject; }

		void Jump(float strength, float deltaTime)
		{
			if (mIsJumping == false)
			{
				mVelocity.y = strength;
				mIsJumping = true;
			}
		}

		void Gravity(float deltaTime)
		{
			//Enleve de la velocite
			mVelocity.y -= mGravity * deltaTime;

			//Fait redescendre le joueur
			//mCharacter->mEntity->SetWorldPosition({ GetWorldPosition().x, GetWorldPosition().y + , GetWorldPosition().z });
			WorldTranslate(gce::Vector3f32(0.f, mVelocity.y * deltaTime, 0.f));
		}

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

		void SetJump(float jump) { mJump = jump; }
		float GetJump() { return mJump; }

		void SetGravity(float gravity, gce::GameObject& gamePlayer) { mGravity = gravity; /*gamePlayer.GetComponent<gce::PhysicComponent>()->SetGravityScale(0.981f);*/ }
		float GetGravity() { return mGravity; }

		void SetWorldVelocity(gce::Vector3f32 velocity) { mVelocity = velocity; }
		gce::Vector3f32 GetWorldVelocity() { return mVelocity; }
		void AddVelocity(gce::Vector3f32 velocity) { mVelocity + velocity; }
		void ResetVelocity() { mVelocity = gce::Vector3f32(0.f, 0.f, 0.f); }

		void SetIsJumping(bool isJumping) { mIsJumping = isJumping; }
		bool GetIsJumping() { return mIsJumping; }

END_SCRIPT