#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		gce::Vector3f32 mPosition = { 5,5,5 };

		gce::GameObject* mObjectCamera;
		gce::Window* mWindow = nullptr;

		float32 mDeltaTime;

		uint32 mWidth = 0;
		uint32 mHeight = 0;

		float degree = 0;

	public:
		ScriptCharacter*  mCharacter;

		void Start() 
		{ 
			mCharacter = m_pOwner->AddScript<ScriptCharacter>();
			mWindow = gce::GameManager::GetWindow();
		}
		void Update() 
		{ 
			mDeltaTime = gce::GameManager::DeltaTime();

			if (mWindow != nullptr)
			{
				mWidth = mWindow->GetWidth();
				mHeight = mWindow->GetHeight();

				degree = 360 / ((gce::Sqrt(mWidth * mWidth + mHeight * mHeight)*100));
			}

			InputMove();
			Camera();
		}

		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}
		
		void InputMove()
		{
			if (gce::GetKey(gce::Keyboard::Key::Z))
				mCharacter->mEntity->WorldTranslate({ 0, 0, mPosition.z * mDeltaTime });
			else if (gce::GetKey(gce::Keyboard::Key::S))
				mCharacter->mEntity->WorldTranslate({ 0, 0, -mPosition.z * mDeltaTime });

			if (gce::GetKey(gce::Keyboard::Key::D))
				mCharacter->mEntity->WorldTranslate({ mPosition.x * mDeltaTime, 0, 0 });
			else if (gce::GetKey(gce::Keyboard::Key::Q))
				mCharacter->mEntity->WorldTranslate({ -mPosition.x * mDeltaTime, 0, 0 });
		}
		
		void Camera()
		{
			if (mObjectCamera == nullptr)
				return;
			std::cout << (float)gce::GetMousePosition().y * degree << std::endl;
			mObjectCamera->transform.SetWorldRotation({ gce::Clamp((float)gce::GetMousePosition().y * degree, -180,180), (float)gce::GetMousePosition().x * degree, 0.f });
		}

		void SetCamera(gce::GameObject& cameraObject)
		{
			mObjectCamera = &cameraObject;
		}

END_SCRIPT