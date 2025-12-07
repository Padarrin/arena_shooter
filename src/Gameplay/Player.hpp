#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

		gce::Vector3f32 velocity = { 0, 0, 0 };
		float gravity = 9.81f;

	public:
		ScriptCharacter* mCharacter;

		virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); }
		virtual void Start() { mCharacter->Start(); mWindow = gce::GameManager::GetWindow(); }

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			InputMove(deltaTime);

			TurnCamera();
		}

		virtual void Destroy() {}

		virtual void CollisionEnter() { std::cout << "d"; }
		virtual void CollisionStay() {}
		virtual void CollisionExit() {}
		
		void InputMove(float deltaTime)
		{
			float horizontalInput = gce::GetKey(gce::Keyboard::Key::D) - gce::GetKey(gce::Keyboard::Key::Q);
			float verticalInput = gce::GetKey(gce::Keyboard::Key::Z) - gce::GetKey(gce::Keyboard::Key::S);

			gce::Vector3f32 direction = m_pOwner->transform.GetWorldRight() * horizontalInput + m_pOwner->transform.GetWorldForward() * verticalInput;

			SetWorldPosition(GetWorldPosition() + direction * mCharacter->GetSpeed() * deltaTime);
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

		void Gravity(float deltaTime)
		{
			//Enleve de la velocite
			velocity.y -= gravity * deltaTime;

			//Fait redescendre le joueur
			mCharacter->mEntity->SetWorldPosition({ GetWorldPosition().x,GetWorldPosition().y + velocity.y * deltaTime,GetWorldPosition().z });

			//if (CollisionEnter(chunk->GetCurrentChunk(this)))
			//{
			//	//Regarde si il est dans les airs pour qu'il puisse sauter
			//	if (pPlayer->GetPosition().y <= -0.75f)
			//	{
			//		pPlayer->SetPosition({ pPlayer->GetPosition().x, -0.75f ,pPlayer->GetPosition().z });
			//		velocity.y = 0.f;
			//		isJumping = false;
			//	}
			//	else
			//	{
			//		isJumping = true;
			//	}
			//}
			//else
			//{
			//	pPlayer->SetPosition({ pPlayer->GetPosition().x, pPlayer->GetPosition().y ,pPlayer->GetPosition().z });
			//}

			//if (pPlayer->GetPosition().y <= -5)
			//{
			//	Respawn();
			//	chunk->ResetChunk();
			//}
		}

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }

		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }

		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

END_SCRIPT