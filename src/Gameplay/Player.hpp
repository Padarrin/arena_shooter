#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		gce::Vector3f32 mPosition;/////////////////////////////////////////

		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

		float32 mDeltaTime;

		uint32 mWidth;
		uint32 mHeight;

		float degree;

	public:
		ScriptCharacter*  mCharacter;

		void Start() 
		{ 
			mCharacter = m_pOwner->AddScript<ScriptCharacter>();
			mWindow = gce::GameManager::GetWindow();
			mWidth = 0;
			mHeight = 0;
			degree = 0;
			mPosition = { 5,5,5 };/////////////////////////////////////////
		}

		void Update() 
		{ 
			mDeltaTime = gce::GameManager::DeltaTime();

			if (mWindow != nullptr)
			{
				mWidth = mWindow->GetWidth();///////////////////////////////////
				mHeight = mWindow->GetHeight();/////////////////////////////////

				degree = 360 / ((gce::Sqrt(mWidth * mWidth + mHeight * mHeight)*100));//////////////////////////////
			}

			InputMove();
			TurnCamera();
		}

		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}
		
		void InputMove()
		{
			if (gce::GetKey(gce::Keyboard::Key::Z))
				WorldTranslate({ 0, 0, mPosition.z * mDeltaTime });
			else if (gce::GetKey(gce::Keyboard::Key::S))
				WorldTranslate({ 0, 0, -mPosition.z * mDeltaTime });

			if (gce::GetKey(gce::Keyboard::Key::D))
				WorldTranslate({ mPosition.x * mDeltaTime, 0, 0 });
			else if (gce::GetKey(gce::Keyboard::Key::Q))
				WorldTranslate({ -mPosition.x * mDeltaTime, 0, 0 });
		}

		void TurnCamera()
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