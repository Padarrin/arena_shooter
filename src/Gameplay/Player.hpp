#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		gce::Vector3f32 mDirection;

		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

	public:
		ScriptCharacter*  mCharacter;

		virtual void Start() 
		{ 
			mCharacter = m_pOwner->AddScript<ScriptCharacter>();
			mCharacter->Start();
			mWindow = nullptr;
			mDirection = { 5,5,5 };
		}

		virtual void Update()
		{ 
			float deltaTime = gce::GameManager::DeltaTime();

			if (mWindow == nullptr) { mWindow = gce::GameManager::GetWindow(); }
			else
			{
				TurnCamera();
			}

			InputMove(deltaTime);
			
		}

		virtual void Destroy() {}

		virtual void CollisionEnter() {}
		virtual void CollisionStay() {}
		virtual void CollisionExit() {}
		
		void InputMove(float deltaTime)
		{
			if (gce::GetKey(gce::Keyboard::Key::Z))
			{
				float mction = mDirection.z* deltaTime;
				WorldTranslate({ 0, 0, mDirection.z * deltaTime });
			}
			else if (gce::GetKey(gce::Keyboard::Key::S))
			{
				WorldTranslate({ 0, 0, -mDirection.z * deltaTime });
			}

			if (gce::GetKey(gce::Keyboard::Key::D))
			{
				WorldTranslate({ mDirection.x * deltaTime, 0, 0 });
			}
			else if (gce::GetKey(gce::Keyboard::Key::Q))
			{
				WorldTranslate({ -mDirection.x * deltaTime, 0, 0 });
			}
		}

		void TurnCamera()
		{
			if (mObjectCamera == nullptr)
				return;

			uint32 width = mWindow->GetWidth();
			uint32 height = mWindow->GetHeight();

			float degree = 360 / ((gce::Sqrt(width * width + height * height) * 100));
			mObjectCamera->transform.SetWorldRotation({ (float)gce::GetMousePosition().y * degree, (float)gce::GetMousePosition().x * degree, 0.f });
		}

		void SetCamera(gce::GameObject& cameraObject) { mObjectCamera = &cameraObject; }

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

END_SCRIPT