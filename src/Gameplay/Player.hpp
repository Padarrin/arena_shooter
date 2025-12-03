#include "Character.hpp"

DECLARE_SCRIPT(ScriptPlayer, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		int mX = 5;
		int mY = 5;
		int mZ = 5;

	public:
		ScriptCharacter*  mCharacter;

		void Start() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); }
		void Update() {}
		void Destroy() {}

		void CollisionEnter() {}
		void CollisionStay() {}
		void CollisionExit() {}

		void InputMove()
		{
			if (GetKeyDown(Keyboard::Z))
				mCharacter->Move({ 0, 0, mZ });
			else if (GetKeyDown(Keyboard::S))
				mCharacter->Move({ 0, 0, -mZ });

			if (GetKeyDown(Keyboard::D))
				mCharacter->Move({ mX, 0, 0 });
			else if (GetKeyDown(Keyboard::Q))
				mCharacter->Move({ -mX, 0, 0 });
		}

END_SCRIPT