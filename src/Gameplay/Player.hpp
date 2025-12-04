#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		float mSpeed;

		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

		float32 mDeltaTime;

		uint32 mWidth;
		uint32 mHeight;

		float mHorizontalInput;
		float mVerticalInput;

	public:
		ScriptCharacter*  mCharacter;

		void Start() 
		{
			mCharacter = m_pOwner->AddScript<ScriptCharacter>();
			mCharacter->Start();
			mCharacter->SetSpeed(9);

			mSpeed = mCharacter->GetSpeed();

			mWindow = gce::GameManager::GetWindow();
			mWidth = mWindow->GetWidth();
			mHeight = mWindow->GetHeight();
		}

		void Update() 
		{ 
			mDeltaTime = gce::GameManager::DeltaTime();

			float degree = 360 / ((gce::Sqrt(mWidth * mWidth + mHeight * mHeight) * 100));

			InputMove(degree);
			TurnCamera(degree);
		}

		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}
		
		void InputMove(float degree)
		{
			mHorizontalInput = gce::GetKey(gce::Keyboard::Key::D) - gce::GetKey(gce::Keyboard::Key::Q);
			mVerticalInput = gce::GetKey(gce::Keyboard::Key::Z) - gce::GetKey(gce::Keyboard::Key::S);

			gce::Vector3f32 direction = m_pOwner->transform.GetWorldRight() * mHorizontalInput + m_pOwner->transform.GetWorldForward() * mVerticalInput;

			mCharacter->mEntity->SetWorldPosition(GetWorldPosition() + direction * mSpeed * mDeltaTime);
		}

		void TurnCamera(float degree)
		{
			if (mObjectCamera == nullptr)
				return;
			
			std::cout << (float)gce::GetMousePosition().y << "; " << degree << "; " << (float)gce::GetMousePosition().y * degree << std::endl;
			mObjectCamera->transform.SetLocalRotation({ gce::Clamp((float)gce::GetMousePosition().y * degree, 0,1), 0.f, 0.f });
			m_pOwner->transform.SetWorldRotation({ 0.f,(float)gce::GetMousePosition().x * degree ,0.f });
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