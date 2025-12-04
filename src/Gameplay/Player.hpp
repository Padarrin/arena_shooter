#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		gce::Vector3f32 mDirection;

		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

		float32 mDeltaTime;

		uint32 mWidth;
		uint32 mHeight;

	public:
		ScriptCharacter*  mCharacter;

		void Start() 
		{ 
			mCharacter = m_pOwner->AddScript<ScriptCharacter>();
			mWindow = gce::GameManager::GetWindow();
			mWidth = mWindow->GetWidth();
			mHeight = mWindow->GetHeight();

			mDirection = { 5,5,5 };
		}

		void Update() 
		{ 
			mDeltaTime = gce::GameManager::DeltaTime();

			float degree = 360 / ((gce::Sqrt(mWidth * mWidth + mHeight * mHeight) * 100));

			InputMove();
			TurnCamera(degree);
		}

		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}
		
		void InputMove()
		{
			if (gce::GetKey(gce::Keyboard::Key::Z))
				WorldTranslate({ 0, 0, mDirection.z * mDeltaTime });
			else if (gce::GetKey(gce::Keyboard::Key::S))
				WorldTranslate({ 0, 0, -mDirection.z * mDeltaTime });

			if (gce::GetKey(gce::Keyboard::Key::D))
				WorldTranslate({ mDirection.x * mDeltaTime, 0, 0 });
			else if (gce::GetKey(gce::Keyboard::Key::Q))
				WorldTranslate({ -mDirection.x * mDeltaTime, 0, 0 });
		}

		void TurnCamera(float degree)
		{
			if (mObjectCamera == nullptr)
				return;
			mObjectCamera->transform.SetWorldRotation({ (float)gce::GetMousePosition().y * degree, (float)gce::GetMousePosition().x * degree, 0.f });
		}

		void SetCamera(gce::GameObject& cameraObject)
		{
			mObjectCamera = &cameraObject;
		}

		void SetWorldPosition(gce::Vector3f32 position)
		{
			mCharacter->mEntity->SetWorldPosition(position);
		}
		
		gce::Vector3f32 GetWorldPosition()
		{
			return mCharacter->mEntity->GetWorldPosition();
		}

		void WorldTranslate(gce::Vector3f32 position)
		{
			mCharacter->mEntity->WorldTranslate(position);
		}

END_SCRIPT