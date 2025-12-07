#include "Functions.h"

#include <GameObject.h>
#include "../Engine/Components/Light.h"
#include "../Engine/Components/MeshRenderer.h"
#include <Render.h>
#include <Engine.h>

#include "Grid.h"
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
	return CreateGameObject<T>(scene, geometry, nullptr);
}

template<typename T>
inline gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Texture* texture)
{
	return CreateGameObject<T>(scene, nullptr, texture);
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
inline T* GetCell(gce::Vector3f32 pos, Grid* grid)
{
	/*gce::Vector2i32 index = GetCellInPos(pos, grid->GetSizeTabCell());
	return grid->GetAllCells()[index.x][index.y];*/
}

template<typename T>
inline Node<T>* GetNode(gce::Vector3f32 pos, Grid* grid)
{
	gce::Vector2i32  index = GetCellInPos(pos, grid->GetSizeTabCell());
	std::vector<Node<T>*>* allNodes = grid->GetAllNodes();
	return GetNodeInTab(index.x, index.y, grid->GetAllCells()[0].size(), allNodes);
}

template<typename T>
inline Node<T>* GetNodeInTab(int row, int col, int length_col, std::vector<Node<T>*>* allNodes)
{
	return (*allNodes)[row * length_col + col];
}

template<typename T>
inline T* GetNearestCell(gce::Vector3f32 pos, std::vector<std::vector<T*>> allCells)
{
	/*T* nearest = nullptr;
	float smallestSquaredDist = INT_MAX;

	for (auto& row : allCells)
	{
		for (auto cell : row)
		{
			float dx = abs(cell->GetPosition().x - pos.x);
			float dy = abs(cell->GetPosition().z - pos.z);

			float squaredDist = dx * dx + dy * dy;

			if (squaredDist < smallestSquaredDist)
			{
				nearest = cell;

				smallestSquaredDist = squaredDist;
			}
		}
	}

	return nearest;*/
	return nullptr;
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
