#pragma once
#include "Entity.h"

class Object : ScriptEntity
{
	gce::Vector3f32 mPos = { 0.f,0.f,0.f };

	virtual void Start();
	virtual void Update();
	virtual void Destroy();

};

