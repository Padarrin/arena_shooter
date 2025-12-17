#pragma once
#include <vector>
#include <math.h>
#include "GameObject.h"

#define RACINE std::sqrt(2)
#define DEFAULTCOLOR gce::Vector4(1.f, 1.f, 1.f, 1.f)

class Grid;

class Entity;
class Agent;

template<typename T>
class Node;

template<typename A>
void AddVector2OnVector1(std::vector<A>* vector1, const std::vector<A>& vector2);

template<typename A>
void AddReveseVector2OnVector1(std::vector<A>* vector1, const std::vector<A>& vector2);

template<typename A>
std::vector<A*>* EraseTab(std::vector<A*>* all);

template<typename A>
std::vector<std::vector<A*>>* EraseTab(std::vector<std::vector<A*>>* all);

template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Vector4 color);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Texture* texture);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture, gce::Vector4 color);

void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry);
void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry, gce::Texture* texture);

bool Normalize(gce::Vector3f32& vector)
{
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if (magnitude != 0)
    {
        vector.x /= magnitude;
        vector.y /= magnitude;
        vector.z /= magnitude;
        return true;
    }

    return false;
}

float GetDistance(gce::Vector3f32 pos1, gce::Vector3f32 pos2)
{
    int x = pos2.x - pos1.x;
    int y = pos2.y - pos1.y;
    int z = pos2.z - pos1.z;

    return std::sqrt(x * x + y * y + z * z);
}

//template<typename T>
//T* GetCell(gce::Vector3f32 pos, Grid* grid);

//template<typename T>
//Node<T>* GetNode(gce::Vector3f32 pos, Grid* grid);

//template<typename T>
//Node<T>* GetNodeInTab(int row, int col, int length_col, std::vector<Node<T>*>* allNodes);

Entity* GetNearestEntity(gce::Vector3f32 pos);

Entity* GetNearestAgent(gce::Vector3f32 pos);

//template<typename T>
//T* GetNearestCell(gce::Vector3f32 pos, std::vector<std::vector<T*>> allCells);

void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry);

void AddMeshRenderer(gce::GameObject& object, gce::Geometry* geometry, gce::Texture* texture);

template<typename T>
T* GetEntityNearest(gce::Vector3f32 pos, float minDis);

float DisManhattan(gce::Vector3f32 currentPos, gce::Vector3f32 endPos, int sizeCell)
{
    return (abs(currentPos.x - endPos.x) + abs(currentPos.y - endPos.y)) / sizeCell;
}

//gce::Vector2f32 GetCellInPos(gce::Vector3f32 pos, int sizeCell);


#include "Functions.inl"





