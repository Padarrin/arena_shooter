#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
		gce::GameObject* mGamePlayer;
		gce::Window* mWindow;

		gce::Vector3f32 mVelocity;
		float mJump;

		bool mIsJumping;

	public:
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); mVelocity = gce::Vector3f32(0.f, 0.f, 0.f); mJump = 6.f; mCharacter->SetMaxLife(100); mCharacter->SetDamage(5); }
		virtual void Start() { mCharacter->Start(); mWindow = gce::GameManager::GetWindow(); mIsJumping = true; gce::HideMouseCursor(); }

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			InputMove(deltaTime);

			TurnCamera();

			if (mCharacter->GetLife() <= 0)
				m_pOwner->Destroy();
		}

		virtual void Destroy() {}

		virtual void CollisionEnter(gce::GameObject* other) 
		{ 
			mCharacter->CollisionEnter(other);

			if (other->GetName() == "Floor")
				ColliderFloor();

			if (other->GetName() == "EnemyBall")
				ColliderBall(other);

			if (other->GetName() == "PlayerBall")
				other->Destroy();
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

			WorldTranslate(direction * mCharacter->GetSpeed() * deltaTime);

			if (gce::GetKeyDown(gce::Keyboard::Key::SPACE))
			{
				Jump(mJump, deltaTime);
			}

			if(gce::GetButtonDown( gce::Mouse::Button::LEFT))
				mCharacter->CreateBallInFrontPlayer<ScriptBall>("PlayerBall", 100.f, gce::SHAPES.CUBE, mCharacter->mEntity, mObjectCamera);
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

		void Jump(float strength, float deltaTime)
		{
			if (mIsJumping == false)
			{
				mVelocity.y = strength;
				mGamePlayer->GetComponent<gce::PhysicComponent>()->SetVelocity(mVelocity);
				WorldTranslate({ 0.f, mVelocity.y * deltaTime, 0.f });
				mIsJumping = true;
			}
		}

		void ColliderFloor()
		{
			//Regarde si il est dans les airs pour qu'il puisse saute
			mVelocity.y = 0.f;
			mGamePlayer->GetComponent<gce::PhysicComponent>()->SetVelocity(mVelocity);
			mIsJumping = false;
		}
		void ColliderBall(gce::GameObject* other)
		{
			mCharacter->Damage(5);
			other->Destroy();
		}

		void SetCamera(gce::GameObject& cameraObject) { mObjectCamera = &cameraObject; }
		gce::GameObject* GetCamera() { return mObjectCamera; }

		void SetPlayer(gce::GameObject& gamePlayer) { mGamePlayer = &gamePlayer; }

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

		void SetJump(float jump) { mJump = jump; }
		float GetJump() { return mJump; }

		void SetWorldVelocity(gce::Vector3f32 velocity) { mVelocity = velocity; }
		gce::Vector3f32 GetWorldVelocity() { return mVelocity; }
		void AddVelocity(gce::Vector3f32 velocity) { mVelocity += velocity; }
		void ResetVelocity() { mVelocity = gce::Vector3f32(0.f, 0.f, 0.f); }

		void SetIsJumping(bool isJumping) { mIsJumping = isJumping; }
		bool GetIsJumping() { return mIsJumping; }

END_SCRIPT