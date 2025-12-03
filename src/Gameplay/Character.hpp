#include "Entity.hpp"

DECLARE_SCRIPT(ScriptCharacter, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

	private:
		int mLife = 0;
		float mSpeed = 0.f;

	public:
		ScriptEntity* mEntity;

		virtual void Start() { mEntity = m_pOwner->AddScript<ScriptEntity>();}
		virtual void Update() {}
		virtual void Destroy() {}

		virtual void CollisionEnter() {}
		virtual void CollisionStay() {}
		virtual void CollisionExit() {}

		//void GoToPosition

		void SetLife(int life) { mLife = life; }
		void SetSpeed(float speed) { mSpeed = speed; }

		int GetLife() { return mLife; }
		float GetSpeed() { return mSpeed; }

END_SCRIPT