#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	protected:
		gce::GameObject* mObjectCamera;
		gce::Window* mWindow;

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

		virtual void CollisionEnter() {}
		virtual void CollisionStay() {}
		virtual void CollisionExit() {}
		
		void InputMove(float deltaTime)
		{
			float verticalInput = gce::GetLeftTrigger();

			gce::Vector3f32 direction = m_pOwner->transform.GetWorldForward() * verticalInput;

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

		void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
		gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
		void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

END_SCRIPT