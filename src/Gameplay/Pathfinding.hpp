#pragma once
#include "Queue.hpp"
#include "Compare.h"

template<typename T>
class Node;

class Grid;

class ScriptAgent;


template<typename T>
class PathFinding
{
protected:
	bool mReadFinish;
	Queue_<T, ComparePath<T>> mPath;
public:
	PathFinding() { Start(); }

	void Start() { SetReadFinish(true); }

	void Find(Node<T>* startNode, Node<T>* endNode, Grid* grid, ScriptAgent* owner) { PathFinding<T>::FindPath(startNode, endNode, grid, GetPath(), owner); }

	void SetPaths(Queue_<T, ComparePath<T>> path);
	Queue_<T, ComparePath<T>>* GetPaths();

	~PathFinding();



protected:
	static void FindPath(Node<T>* startNode, Node<T>* endNode, Grid* grid, Queue<Node<T>>* allFormerPaths, ScriptAgent* owner);
	//static void CreatePath(bool isfinish, Node<T>* startNode, Node<T>* endNode, std::vector<Node<T>*>* allFormerPaths);
	static void ResetNodes(Grid* grid);
};

#include "PathFinding.inl"