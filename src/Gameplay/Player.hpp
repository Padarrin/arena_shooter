#include "../Engine/GameManager.h"
#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		float mX = 5;
		float mY = 5;
		float mZ = 5;

		float32 mDeltaTime;

	public:
		ScriptCharacter*  mCharacter;

		void Start() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); }
		void Update() { InputMove(); }
		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}
		
		void InputMove()
		{
			mDeltaTime = gce::GameManager::DeltaTime();

			if (gce::GetKey(gce::Keyboard::Key::Z))
				mCharacter->mEntity->WorldTranslate({ 0, 0, mZ * mDeltaTime });
			else if (gce::GetKey(gce::Keyboard::Key::S))
				mCharacter->mEntity->WorldTranslate({ 0, 0, -mZ * mDeltaTime });

			if (gce::GetKey(gce::Keyboard::Key::D))
				mCharacter->mEntity->WorldTranslate({ mX * mDeltaTime, 0, 0 });
			else if (gce::GetKey(gce::Keyboard::Key::Q))
				mCharacter->mEntity->WorldTranslate({ -mX * mDeltaTime, 0, 0 });
		}


END_SCRIPT