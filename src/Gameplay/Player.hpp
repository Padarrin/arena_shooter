#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;
		float mJump;

		bool mIsJumping;

	public:
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); mJump = 6.f; mCharacter->SetMaxLife(100); mCharacter->SetDamage(5); }
		virtual void Start() 
		{ 
			mWindow = gce::GameManager::GetWindow(); 
			mIsJumping = true; 
		}

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			gce::HideMouseCursor();
			//gce::SetMousePosition(gce::Vector2i32(1768 * 0.5f,992 * 0.5f));

			InputMove(deltaTime);
			TurnCamera();

			if (mCharacter->GetLife() <= 0)
				m_pOwner->Destroy();
		}

		virtual void Destroy() {}

		virtual void CollisionEnter(gce::GameObject* other) 
		{ 
			if (other->GetName() == "Floor")
			{
				ColliderFloor();

			if (other->GetName() == "EnemyBall")
				ColliderBall(other);

			if (other->GetName() == "PlayerBall")
				other->Destroy();
		}
			//if (other->GetName() == "Ball")
			//{
			//	ColliderBall(other);
			//}
			
		virtual void CollisionStay(GameObject* other) {}
		virtual void CollisionExit(GameObject* other) {}
		
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
				mCharacter->CreateBallInFront<ScriptBall>("PlayerBall", 100.f, gce::SHAPES.CUBE, mCharacter->mEntity);
		}

		void TurnCamera()
		{
			if (mObjectCamera == nullptr)
				return;

			uint32 width = mWindow->GetWidth();
			uint32 height = mWindow->GetHeight();
			float degree = 360.f / ((gce::Sqrt(width * width + height * height) * 100.f));
			std::cout << (float)gce::GetMousePosition().y * degree << std::endl;
			mObjectCamera->transform.SetLocalRotation({ (float)gce::GetMousePosition().y * degree, 0.f, 0.f });
			m_pOwner->transform.SetWorldRotation({ gce::Clamp((float)gce::GetMousePosition().y * degree,-0.5f,0.5f) ,(float)gce::GetMousePosition().x * degree ,0.f });
			
			//gce::SetMousePosition(gce::Vector2i32(width * 0.5f, height * 0.5f));
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

		void ColliderBall(gce::GameObject* other)
		{
			
		}

		void SetCamera(gce::GameObject& cameraObject) { mObjectCamera = &cameraObject; }
		gce::GameObject* GetCamera() { return mObjectCamera; }

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

		void SetJump(float jump) { mJump = jump; }
		float GetJump() { return mJump; }

		void SetIsJumping(bool isJumping) { mIsJumping = isJumping; }
		bool GetIsJumping() { return mIsJumping; }

END_SCRIPT