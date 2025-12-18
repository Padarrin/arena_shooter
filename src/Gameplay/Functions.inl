#include "Functions.h"

#include <GameObject.h>
#include "../Engine/Components/Light.h"
#include "../Engine/Components/MeshRenderer.h"
#include <Render.h>
#include <Engine.h>

#include "Grid.hpp"
#include "Node.h"

template<typename A>
inline void AddVector2OnVector1(std::vector<A>* vector1, const std::vector<A>& vector2)
{
	int lenghtVector2 = vector2.size();
	for (int i = 0; i < lenghtVector2; i++)
	{
		vector1->push_back(vector2[i]);
	}
}

template<typename A>
inline void AddReveseVector2OnVector1(std::vector<A>* vector1, const std::vector<A>& vector2)
{
	int lenghtVector2 = vector2.size() - 1;
	for (int i = lenghtVector2; i > -1; i--)
	{
		vector1->push_back(vector2[i]);
	}
}

template<typename A>
inline std::vector<A*>* EraseTab(std::vector<A*>* all)
{
	int lenghtAll = all->size() - 1;
	for (int i = lenghtAll; i > -1; i--)
	{
		delete (*all)[i];
	}
	return all;
}

template<typename A>
inline std::vector<std::vector<A*>>* EraseTab(std::vector<std::vector<A*>>* all)
{
	int lenghtAllI = all->size() - 1;
	int lenghtAllJ = all[0].size() - 1;
	for (int i = lenghtAllI; i > -1; i--)
	{
		for (int j = lenghtAllJ; j > -1; i--)
		{
			delete (*all)[i][j];
		}
		all[0].clear();
	}
	all->clear();
	return all;
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene)
{
	return CreateGameObject<T>(scene, nullptr, nullptr);
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry)
{
	gce::GameObject& object = gce::GameObject::Create(scene);
	T* ob = object.AddScript<T>();
	ob->T::Initia();

	if (geometry != nullptr)
	{
		static gce::D12PipelineObject defaultPso(gce::SHADERS.VERTEX, gce::SHADERS.PIXEL, gce::SHADERS.HULL, gce::SHADERS.DOMAIN_, gce::SHADERS.ROOT_SIGNATURE);

		gce::MeshRenderer& meshRenderer = *object.AddComponent<gce::MeshRenderer>();
		meshRenderer.pGeometry = geometry;
		meshRenderer.pPso = &defaultPso;
	}
	gce::Light* light = object.AddComponent<gce::Light>();

	return object;
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color)
{
	return CreateGameObject<T>(scene, geometry, nullptr, color);
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Texture* texture)
{
	return CreateGameObject<T>(scene, nullptr, texture, DEFAULTCOLOR);
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture)
{
	gce::GameObject& object = gce::GameObject::Create(scene);
	T* ob = object.AddScript<T>();
	ob->T::Initia();

	if (geometry != nullptr)
	{
		static gce::D12PipelineObject defaultPso(gce::SHADERS.VERTEX, gce::SHADERS.PIXEL, gce::SHADERS.HULL, gce::SHADERS.DOMAIN_, gce::SHADERS.ROOT_SIGNATURE);

		gce::MeshRenderer& meshRenderer = *object.AddComponent<gce::MeshRenderer>();
		meshRenderer.pGeometry = geometry;
		meshRenderer.pPso = &defaultPso;

		if (texture != nullptr)
		{
			meshRenderer.pMaterial->albedoTextureID = texture->GetTextureID();
			meshRenderer.pMaterial->useTextureAlbedo = 1;
		}
	}
	gce::Light* light = object.AddComponent<gce::Light>();

	return object;
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color)
{
	gce::GameObject& object = gce::GameObject::Create(scene);
	T* ob = object.AddScript<T>();
	ob->T::Initia();

	AddMeshRenderer(object, geometry, texture);
	gce::Light* light = object.AddComponent<gce::Light>();
	light->color = color;

	return object;
}

inline void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry)
{
	AddMeshRenderer(object, geometry, nullptr);
}

inline void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry, gce::Texture* texture)
{
	if (geometry != nullptr)
	{
		static gce::D12PipelineObject defaultPso(gce::SHADERS.VERTEX, gce::SHADERS.PIXEL, gce::SHADERS.HULL, gce::SHADERS.DOMAIN_, gce::SHADERS.ROOT_SIGNATURE);

		gce::MeshRenderer& meshRenderer = *object.AddComponent<gce::MeshRenderer>();
		meshRenderer.pGeometry = geometry;
		meshRenderer.pPso = &defaultPso;

		if (texture != nullptr)
		{
			meshRenderer.pMaterial->albedoTextureID = texture->GetTextureID();
			meshRenderer.pMaterial->useTextureAlbedo = 1;
			meshRenderer.pMaterial->subsurface = 0.2f;
		}
	}
}

template<typename T>
inline T* GetEntityNearest(gce::Vector3f32 pos, float minDis)
{
	/*std::list<Entity*> allEntities = GameManager::Get()->GetEntities();

	gce::Vector3f32 posNearest = gce::Vector3f32(minDis, minDis, minDis);
	T* entityNearest = nullptr;

	for (Entity* e : allEntities)
	{
		if (T* c = dynamic_cast<T*>(e))
		{
			gce::Vector3f32 posC = c->GetPosition();
			if (abs(pos.x - posC.x) <= posNearest.x && abs(pos.y - posC.y) <= posNearest.y && abs(pos.z - posC.z) <= posNearest.z)
			{
				posNearest = posC;
				entityNearest = c;
			}
		}
	}

	return entityNearest;*/
	return nullptr;
}
