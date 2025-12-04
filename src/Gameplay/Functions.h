#pragma once
#include <vector>
#include <math.h>

#define RACINE std::sqrt(2)

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
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Texture* texture);
template<typename T>
gce::GameObject& CreateGameObject(gce::Scene& scene, gce::Geometry* geometry, gce::Texture* texture);

bool Normalize(gce::Vector3f32& vector);

float GetDistance(gce::Vector3f32 pos1, gce::Vector3f32 pos2);

template<typename T>
T* GetCell(gce::Vector3f32 pos, Grid* grid);

template<typename T>
Node<T>* GetNode(gce::Vector3f32 pos, Grid* grid);

template<typename T>
Node<T>* GetNodeInTab(int row, int col, int length_col, std::vector<Node<T>*>* allNodes);

Entity* GetNearestEntity(gce::Vector3f32 pos);

Entity* GetNearestAgent(gce::Vector3f32 pos);

template<typename T>
T* GetNearestCell(gce::Vector3f32 pos, std::vector<std::vector<T*>> allCells);

template<typename T>
T* GetEntityNearest(gce::Vector3f32 pos, float minDis);

float DisManhattan(gce::Vector3f32 currentPos, gce::Vector3f32 endPos, int sizeCell);

gce::Vector2f32 GetCellInPos(gce::Vector3f32 pos, int sizeCell);


#include "Functions.inl"





